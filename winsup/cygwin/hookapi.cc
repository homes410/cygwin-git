/* hookapi.cc

   Copyright 2005, 2006, 2007, 2008, 2011, 2012 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#include "winsup.h"
#include <stdlib.h>
#include <sys/param.h>
#include "ntdll.h"
#include "cygerrno.h"
#include "security.h"
#include "path.h"
#include "fhandler.h"
#include "dtable.h"
#include "cygheap.h"

#define rva(coerce, base, addr) (coerce) ((char *) (base) + (addr))
#define rvacyg(coerce, addr) rva (coerce, cygwin_hmodule, addr)

struct function_hook
{
  const char *name;	// Function name, e.g. "DirectDrawCreateEx".
  const void *hookfn;	// Address of your function.
  void *origfn;		// Stored by HookAPICalls, the address of the original function.
};

/* Given an HMODULE, returns a pointer to the PE header */
static PIMAGE_NT_HEADERS
PEHeaderFromHModule (HMODULE hModule)
{
  PIMAGE_NT_HEADERS pNTHeader;

  if (PIMAGE_DOS_HEADER(hModule) ->e_magic != IMAGE_DOS_SIGNATURE)
    pNTHeader = NULL;
  else
    {
      pNTHeader = PIMAGE_NT_HEADERS (PBYTE (hModule)
				     + PIMAGE_DOS_HEADER (hModule) ->e_lfanew);
      if (pNTHeader->Signature != IMAGE_NT_SIGNATURE)
	pNTHeader = NULL;
    }

  return pNTHeader;
}

static long
rvadelta (PIMAGE_NT_HEADERS pnt, DWORD import_rva, DWORD &max_size)
{
  PIMAGE_SECTION_HEADER section = (PIMAGE_SECTION_HEADER) (pnt + 1);
  for (int i = 0; i < pnt->FileHeader.NumberOfSections; i++)
    if (section[i].VirtualAddress <= import_rva
	&& (section[i].VirtualAddress + section[i].Misc.VirtualSize) > import_rva)
    // if (ascii_strncasematch ((char *) section[i].Name, ".idata", IMAGE_SIZEOF_SHORT_NAME))
      {
	max_size = section[i].SizeOfRawData
		   - (import_rva - section[i].VirtualAddress);
	return section[i].VirtualAddress - section[i].PointerToRawData;
      }
  return -1;
}

static void *
putmem (PIMAGE_THUNK_DATA pi, const void *hookfn)
{
  DWORD ofl;
  if (!VirtualProtect (pi, sizeof (PVOID), PAGE_READWRITE, &ofl) )
    return NULL;

  void *origfn = (void *) pi->u1.Function;
  pi->u1.Function = (DWORD) hookfn;

  VirtualProtect (pi, sizeof (PVOID), ofl, &ofl);
  return origfn;
}

/* Builds stubs for and redirects the IAT for one DLL (pImportDesc) */

static bool
RedirectIAT (function_hook& fh, PIMAGE_IMPORT_DESCRIPTOR pImportDesc,
	     HMODULE hm)
{
  // If no import names table, we can't redirect this, so bail
  if (pImportDesc->OriginalFirstThunk == 0)
      return false;

  /* import address table */
  PIMAGE_THUNK_DATA pt = rva (PIMAGE_THUNK_DATA, hm, pImportDesc->FirstThunk);
  /* import names table */
  PIMAGE_THUNK_DATA pn = rva (PIMAGE_THUNK_DATA, hm, pImportDesc->OriginalFirstThunk);

  /* Scan through the IAT, completing the stubs and redirecting the IAT
     entries to point to the stubs. */
  for (PIMAGE_THUNK_DATA pi = pt; pn->u1.Ordinal; pi++, pn++)
    {
      if (IMAGE_SNAP_BY_ORDINAL (pn->u1.Ordinal) )
	continue;

      /* import by name */
      PIMAGE_IMPORT_BY_NAME pimp = rva (PIMAGE_IMPORT_BY_NAME, hm, pn->u1.AddressOfData);

      if (strcmp (fh.name, (char *) pimp->Name) == 0)
	{
	  fh.origfn = putmem (pi, fh.hookfn);
	  if (!fh.origfn)
	    return false;
	  hook_chain *hc;
	  for (hc = &cygheap->hooks; hc->next; hc = hc->next)
	    continue;
	  hc->next = (hook_chain *) cmalloc_abort (HEAP_1_HOOK, sizeof (hook_chain));
	  hc->next->loc = (void **) pi;
	  hc->next->func = fh.hookfn;
	  hc->next->next = NULL;
	  break;
      }
  }

  return true;
}

static void
get_export (function_hook& fh)
{
  PIMAGE_DOS_HEADER pdh = (PIMAGE_DOS_HEADER) cygwin_hmodule;
  if (pdh->e_magic != IMAGE_DOS_SIGNATURE)
    return;
  PIMAGE_NT_HEADERS pnt = (PIMAGE_NT_HEADERS) ((char *) pdh + pdh->e_lfanew);
  if (pnt->Signature != IMAGE_NT_SIGNATURE || pnt->FileHeader.SizeOfOptionalHeader == 0)
    return;
  PIMAGE_EXPORT_DIRECTORY pexp =
    rvacyg (PIMAGE_EXPORT_DIRECTORY,
	 pnt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
  if (!pexp)
    return;

  PDWORD pfuncs = rvacyg (PDWORD, pexp->AddressOfFunctions);
  PDWORD pnames = rvacyg (PDWORD, pexp->AddressOfNames);
  for (DWORD i = 0; i < pexp->NumberOfNames; i++)
    if (strcmp (fh.name, rvacyg (char *, pnames[i])) == 0)
      {
	fh.origfn = rvacyg (void *, pfuncs[i]);
	break;
      }
}

static const char *
makename (const char *name, char *&buf, int& i, int inc)
{
  i += inc;
  static const char *testers[] = {"NOTUSED", "64", "32"};
  if (i < 0 || i >= (int) (sizeof (testers) / sizeof (testers[0])))
    return NULL;
  if (i)
    {
      __small_sprintf (buf, "_%s%s", name, testers[i]);
      name = buf;
    }
  return name;
}

/* Find first missing dll in a given executable.
   FIXME: This is not foolproof since it doesn't look for dlls in the
   same directory as the given executable, like Windows.  Instead it
   searches for dlls in the context of the current executable.
   It also only finds direct dependencies, not indirect ones. */
const char *
find_first_notloaded_dll (path_conv& pc)
{
  const char *res = "?";
  HANDLE hc = NULL;
  HMODULE hm = NULL;
  OBJECT_ATTRIBUTES attr;
  IO_STATUS_BLOCK io;
  HANDLE h;
  NTSTATUS status;
  LARGE_INTEGER size;

  status = NtOpenFile (&h, SYNCHRONIZE | GENERIC_READ,
		       pc.get_object_attr (attr, sec_none_nih),
		       &io, FILE_SHARE_VALID_FLAGS,
		       FILE_SYNCHRONOUS_IO_NONALERT
		       | FILE_OPEN_FOR_BACKUP_INTENT
		       | FILE_NON_DIRECTORY_FILE);
  if (!NT_SUCCESS (status))
    goto out;
  /* Just as in hook_or_detect_cygwin below, we have to take big executables
     into account.  That means, we must not try to map the entire file, since
     there's no guarantee that the current process has enough VM in one block
     left for this mapping.  The offset computation below ignores very big
     executables for now.  In theory, since the import RVA table appears to
     be more or less at the end of the data section, independent of the used
     compiler, that shouldn't matter. */
  if (!GetFileSizeEx (h, &size))
    {
      NtClose (h);
      goto out;
    }
  if (size.QuadPart > wincap.allocation_granularity ())
    size.LowPart = wincap.allocation_granularity ();
  hc = CreateFileMapping (h, &sec_none_nih, PAGE_READONLY, 0, 0, NULL);
  NtClose (h);
  if (!hc)
    goto out;
  hm = (HMODULE) MapViewOfFile(hc, FILE_MAP_READ, 0, 0, size.LowPart);
  if (!hm)
    goto out;

  PIMAGE_NT_HEADERS pExeNTHdr;
  pExeNTHdr = PEHeaderFromHModule (hm);

  if (pExeNTHdr)
    {
      DWORD importRVA;
      DWORD importRVAMaxSize;
      importRVA = pExeNTHdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
      if (importRVA)
	{
	  long delta = rvadelta (pExeNTHdr, importRVA, importRVAMaxSize);
	  if (delta < 0)
	    goto out;
	  importRVA -= delta;

	  DWORD offset = 0;
	  HMODULE map = NULL;
	  if (importRVA + importRVAMaxSize > wincap.allocation_granularity ())
	    {
	      offset = rounddown (importRVA, wincap.allocation_granularity ());
	      DWORD size = importRVA - offset + importRVAMaxSize;
	      map = (HMODULE) MapViewOfFile (hc, FILE_MAP_READ, 0,
					     offset, size);
	      if (!map)
		goto out;
	    }

	  // Convert imports RVA to a usable pointer
	  PIMAGE_IMPORT_DESCRIPTOR pdfirst;
	  pdfirst = rva (PIMAGE_IMPORT_DESCRIPTOR, map ?: hm,
			 importRVA - offset);

	  // Iterate through each import descriptor, and redirect if appropriate
	  for (PIMAGE_IMPORT_DESCRIPTOR pd = pdfirst; pd->FirstThunk; pd++)
	    {
	      const char *lib = rva (PSTR, map ?: hm,
				     pd->Name - delta - offset);
	      if (!LoadLibraryEx (lib, NULL, DONT_RESOLVE_DLL_REFERENCES
					     | LOAD_LIBRARY_AS_DATAFILE))
		{
		  static char buf[MAX_PATH];
		  strlcpy (buf, lib, MAX_PATH);
		  res = buf;
		}
	    }
	  if (map)
	    UnmapViewOfFile (map);
	}
    }

out:
  if (hm)
    UnmapViewOfFile (hm);
  if (hc)
    CloseHandle (hc);

  return res;
}

// Top level routine to find the EXE's imports and redirect them
void *
hook_or_detect_cygwin (const char *name, const void *fn, WORD& subsys, HANDLE h)
{
  HMODULE hm = fn ? GetModuleHandle (NULL) : (HMODULE) name;
  PIMAGE_NT_HEADERS pExeNTHdr = PEHeaderFromHModule (hm);

  if (!pExeNTHdr)
    return NULL;

  /* FIXME: This code has to be made 64 bit capable. */
  if (pExeNTHdr->FileHeader.Machine != IMAGE_FILE_MACHINE_I386)
    return NULL;

  subsys =  pExeNTHdr->OptionalHeader.Subsystem;

  DWORD importRVA = pExeNTHdr->OptionalHeader.DataDirectory
		      [IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
  DWORD importRVASize = pExeNTHdr->OptionalHeader.DataDirectory
			[IMAGE_DIRECTORY_ENTRY_IMPORT].Size;
  if (!importRVA)
    return NULL;

  DWORD importRVAMaxSize;
  long delta = fn ? 0 : rvadelta (pExeNTHdr, importRVA, importRVAMaxSize);
  if (delta < 0)
    return NULL;
  importRVA -= delta;

  // Convert imports RVA to a usable pointer
  PIMAGE_IMPORT_DESCRIPTOR pdfirst;
  char *map = NULL;
  DWORD offset = 0;
  if (h && importRVA + importRVAMaxSize > wincap.allocation_granularity ())
    {
      /* If h is not NULL, the calling function only mapped at most the first
	 64K of the image.  The IAT is usually at the end of the image, so
	 what we do here is to map the IAT into our address space if it doesn't
	 reside in the first 64K anyway.  The offset must be a multiple of the
	 allocation granularity, though, so we have to map a bit more. */
      offset = rounddown (importRVA, wincap.allocation_granularity ());
      /* But that's not all, unfortunately.  Apparently there's a difference
	 between the importRVASize of applications built with gcc and those
	 built with Visual Studio.  When built with gcc, importRVASize contains
	 the size of the import RVA table plus the size of the referenced
	 string table with the DLL names.  When built with VS, it only contains
	 the size of the naked import RVA table.  The following code handles
	 the situation.  importRVAMaxSize contains the size of the remainder
	 of the section.  If the difference between importRVAMaxSize and
	 importRVASize is less than 64K, we just use importRVAMaxSize to
	 compute the size of the memory map.  Otherwise the executable may be
	 very big.  In that case we only map the import RVA table and ... */
      DWORD size = importRVA - offset
		   + ((importRVAMaxSize - importRVASize
		       <= wincap.allocation_granularity ())
		      ? importRVAMaxSize : importRVASize);
      map = (char *) MapViewOfFile (h, FILE_MAP_READ, 0, offset, size);
      if (!map)
	return NULL;
      pdfirst = rva (PIMAGE_IMPORT_DESCRIPTOR, map, importRVA - offset);
      /* ... carefully check the required size to fit the string table into
         the map as well.  Allow NAME_MAX bytes for the DLL name, but don't
	 go beyond the remainder of the section. */
      if (importRVAMaxSize - importRVASize > wincap.allocation_granularity ())
	{
	  DWORD newsize = size;
	  for (PIMAGE_IMPORT_DESCRIPTOR pd = pdfirst; pd->FirstThunk; pd++)
	    if (pd->Name - delta - offset + (NAME_MAX + 1) > newsize)
	      newsize = pd->Name - delta - offset + (NAME_MAX + 1);
	  if (newsize > size)
	    {
	      if (newsize > importRVA - offset + importRVAMaxSize)
		newsize = importRVA - offset + importRVAMaxSize;
	      UnmapViewOfFile (map);
	      map = (char *) MapViewOfFile (h, FILE_MAP_READ, 0, offset,
					    newsize);
	      if (!map)
		return NULL;
	      pdfirst = rva (PIMAGE_IMPORT_DESCRIPTOR, map, importRVA - offset);
	    }
	}
    }
  else
    pdfirst = rva (PIMAGE_IMPORT_DESCRIPTOR, hm, importRVA);

  function_hook fh;
  fh.origfn = NULL;
  fh.hookfn = fn;
  char *buf = NULL;
  if (fn)
    buf = (char *) alloca (strlen (name) + sizeof ("_64"));
  int i = 0;
  // Iterate through each import descriptor, and redirect if appropriate
  for (PIMAGE_IMPORT_DESCRIPTOR pd = pdfirst; pd->FirstThunk; pd++)
    {
      if (!ascii_strcasematch (rva (PSTR, map ?: (char *) hm,
				    pd->Name - delta - offset), "cygwin1.dll"))
	continue;
      if (!fn)
	{
	  if (map)
	    UnmapViewOfFile (map);
	  return (void *) "found it";	// just checking if executable used cygwin1.dll
	}
      i = -1;
      while (!fh.origfn && (fh.name = makename (name, buf, i, 1)))
	RedirectIAT (fh, pd, hm);
      if (fh.origfn)
	break;
    }

  if (map)
    UnmapViewOfFile (map);
  if (!fn)
    return NULL;

  while (!fh.origfn && (fh.name = makename (name, buf, i, -1)))
    get_export (fh);

  return fh.origfn;
}

void
ld_preload ()
{
  char *p = getenv ("LD_PRELOAD");
  if (!p)
    return;
  char *s = (char *) alloca (strlen (p) + 1);
  strcpy (s, p);
  char *here = NULL;
  for (p = strtok_r (s, ":\t\n", &here); p; p = strtok_r (NULL, ":\t\n", &here))
    {
      path_conv lib (p);
      WCHAR libname[lib.get_wide_win32_path_len () + 1];
      if (!LoadLibraryW (lib.get_wide_win32_path (libname)))
	{
	  __seterrno ();
	  api_fatal ("error while loading shared libraries: %s: "
		     "cannot open shared object file: %s", p,
		     strerror (get_errno ()));
	}
    }
}

void
fixup_hooks_after_fork ()
{
  for (hook_chain *hc = &cygheap->hooks; (hc = hc->next); )
    putmem ((PIMAGE_THUNK_DATA) hc->loc, hc->func);
}
