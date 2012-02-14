/* cygheap.cc: Cygwin heap manager.

   Copyright 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009,
   2010, 2011, 2012 Red Hat, Inc.

   This file is part of Cygwin.

   This software is a copyrighted work licensed under the terms of the
   Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
   details. */

#include "winsup.h"
#include <assert.h>
#include <stdlib.h>
#include "cygerrno.h"
#include "security.h"
#include "path.h"
#include "tty.h"
#include "fhandler.h"
#include "dtable.h"
#include "cygheap.h"
#include "child_info.h"
#include "heap.h"
#include "sigproc.h"
#include "pinfo.h"
#include "registry.h"
#include "ntdll.h"
#include <unistd.h>
#include <wchar.h>

static mini_cygheap NO_COPY cygheap_dummy =
{
  {__utf8_mbtowc, __utf8_wctomb}
};

init_cygheap NO_COPY *cygheap = (init_cygheap *) &cygheap_dummy;
void NO_COPY *cygheap_max;

extern "C" char  _cygheap_end[];

static NO_COPY muto cygheap_protect;

struct cygheap_entry
{
  int type;
  struct cygheap_entry *next;
  char data[0];
};

#define NBUCKETS (sizeof (cygheap->buckets) / sizeof (cygheap->buckets[0]))
#define N0 ((_cmalloc_entry *) NULL)
#define to_cmalloc(s) ((_cmalloc_entry *) (((char *) (s)) - (unsigned) (N0->data)))

#define CFMAP_OPTIONS (SEC_RESERVE | PAGE_READWRITE)
#define MVMAP_OPTIONS (FILE_MAP_WRITE)

extern "C" {
static void __stdcall _cfree (void *) __attribute__((regparm(1)));
static void *__stdcall _csbrk (int);
}

/* Called by fork or spawn to reallocate cygwin heap */
void __stdcall
cygheap_fixup_in_child (bool execed)
{
  cygheap_max = cygheap = (init_cygheap *) _cygheap_start;
  _csbrk ((char *) child_proc_info->cygheap_max - (char *) cygheap);
  child_copy (child_proc_info->parent, false, "cygheap", cygheap, cygheap_max, NULL);
  cygheap_init ();
  debug_fixup_after_fork_exec ();
  if (execed)
    {
      cygheap->hooks.next = NULL;
      cygheap->user_heap.base = NULL;		/* We can allocate the heap anywhere */
    }
  /* Walk the allocated memory chain looking for orphaned memory from
     previous execs or forks */
  for (_cmalloc_entry *rvc = cygheap->chain; rvc; rvc = rvc->prev)
    {
      cygheap_entry *ce = (cygheap_entry *) rvc->data;
      if (!rvc->ptr || rvc->b >= NBUCKETS || ce->type <= HEAP_1_START)
	continue;
      else if (ce->type > HEAP_2_MAX)
	_cfree (ce);		/* Marked for freeing in any child */
      else if (!execed)
	continue;
      else if (ce->type > HEAP_1_MAX)
	_cfree (ce);		/* Marked for freeing in execed child */
      else
	ce->type += HEAP_1_MAX;	/* Mark for freeing after next exec */
    }
}

void
init_cygheap::close_ctty ()
{
  debug_printf ("closing cygheap->ctty %p", cygheap->ctty);
  cygheap->ctty->close_with_arch ();
  cygheap->ctty = NULL;
}

#define nextpage(x) ((char *) (((DWORD) ((char *) x + granmask)) & ~granmask))
#define allocsize(x) ((DWORD) nextpage (x))
#ifdef DEBUGGING
#define somekinda_printf debug_printf
#else
#define somekinda_printf malloc_printf
#endif

static void *__stdcall
_csbrk (int sbs)
{
  void *prebrk = cygheap_max;
  size_t granmask = wincap.allocation_granularity () - 1;
  char *newbase = nextpage (prebrk);
  cygheap_max = (char *) cygheap_max + sbs;
  if (!sbs || (newbase >= cygheap_max) || (cygheap_max <= _cygheap_end))
    /* nothing to do */;
  else
    {
      if (prebrk <= _cygheap_end)
	newbase = _cygheap_end;

      DWORD adjsbs = allocsize ((char *) cygheap_max - newbase);
      if (adjsbs && !VirtualAlloc (newbase, adjsbs, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE))
	{
	  MEMORY_BASIC_INFORMATION m;
	  if (!VirtualQuery (newbase, &m, sizeof m))
	    system_printf ("couldn't get memory info, %E");
	  somekinda_printf ("Couldn't reserve/commit %d bytes of space for cygwin's heap, %E",
			    adjsbs);
	  somekinda_printf ("AllocationBase %p, BaseAddress %p, RegionSize %p, State %p\n",
			    m.AllocationBase, m.BaseAddress, m.RegionSize, m.State);
	  __seterrno ();
	  cygheap_max = (char *) cygheap_max - sbs;
	  return NULL;
	}
    }

  return prebrk;
}

/* Use absolute path of cygwin1.dll to derive the Win32 dir which
   is our installation_root.  Note that we can't handle Cygwin installation
   root dirs of more than 4K path length.  I assume that's ok...

   This function also generates the installation_key value.  It's a 64 bit
   hash value based on the path of the Cygwin DLL itself.  It's subsequently
   used when generating shared object names.  Thus, different Cygwin
   installations generate different object names and so are isolated from
   each other.

   Having this information, the installation key together with the
   installation root path is written to the registry.  The idea is that
   cygcheck can print the paths into which the Cygwin DLL has been
   installed for debugging purposes.

   Last but not least, the new cygwin properties datastrcuture is checked
   for the "disabled_key" value, which is used to determine whether the
   installation key is actually added to all object names or not.  This is
   used as a last resort for debugging purposes, usually.  However, there
   could be another good reason to re-enable object name collisions between
   multiple Cygwin DLLs, which we're just not aware of right now.  Cygcheck
   can be used to change the value in an existing Cygwin DLL binary. */
void
init_cygheap::init_installation_root ()
{
  if (!GetModuleFileNameW (cygwin_hmodule, installation_root, PATH_MAX))
    api_fatal ("Can't initialize Cygwin installation root dir.\n"
	       "GetModuleFileNameW(%p, %p, %u), %E",
	       cygwin_hmodule, installation_root, PATH_MAX);
  PWCHAR p = installation_root;
  if (wcsncmp (p, L"\\\\?\\", 4))	/* No long path prefix. */
    {
      if (!wcsncasecmp (p, L"\\\\", 2))	/* UNC */
	{
	  p = wcpcpy (p, L"\\??\\UN");
	  GetModuleFileNameW (cygwin_hmodule, p, PATH_MAX - 6);
	  *p = L'C';
	}
      else
	{
	  p = wcpcpy (p, L"\\??\\");
	  GetModuleFileNameW (cygwin_hmodule, p, PATH_MAX - 4);
	}
    }
  installation_root[1] = L'?';

  RtlInitEmptyUnicodeString (&installation_key, installation_key_buf,
			     sizeof installation_key_buf);
  RtlInt64ToHexUnicodeString (hash_path_name (0, installation_root),
			      &installation_key, FALSE);

  PWCHAR w = wcsrchr (installation_root, L'\\');
  if (w)
    {
      *w = L'\0';
      w = wcsrchr (installation_root, L'\\');
    }
  if (!w)
    api_fatal ("Can't initialize Cygwin installation root dir.\n"
	       "Invalid DLL path");
  *w = L'\0';

  for (int i = 1; i >= 0; --i)
    {
      reg_key r (i, KEY_WRITE, _WIDE (CYGWIN_INFO_INSTALLATIONS_NAME),
		 NULL);
      if (NT_SUCCESS (r.set_string (installation_key_buf,
				    installation_root)))
	break;
    }

  if (cygwin_props.disable_key)
    {
      installation_key.Length = 0;
      installation_key.Buffer[0] = L'\0';
    }
}

void __stdcall
cygheap_init ()
{
  cygheap_protect.init ("cygheap_protect");
  if (cygheap == &cygheap_dummy)
    {
      cygheap = (init_cygheap *) memset (_cygheap_start, 0,
					 sizeof (*cygheap));
      cygheap_max = cygheap;
      _csbrk (sizeof (*cygheap));
      /* Default locale settings. */
      cygheap->locale.mbtowc = __utf8_mbtowc;
      cygheap->locale.wctomb = __utf8_wctomb;
      strcpy (cygheap->locale.charset, "UTF-8");
      /* Set umask to a sane default. */
      cygheap->umask = 022;
      cygheap->rlim_core = RLIM_INFINITY;
    }
  if (!cygheap->fdtab)
    cygheap->fdtab.init ();
  if (!cygheap->sigs)
    sigalloc ();
}

/* Copyright (C) 1997, 2000 DJ Delorie */

static void *__stdcall _cmalloc (unsigned size) __attribute__ ((regparm(1)));
static void *__stdcall _crealloc (void *ptr, unsigned size) __attribute__ ((regparm(2)));

static void *__stdcall __attribute__ ((regparm(1)))
_cmalloc (unsigned size)
{
  _cmalloc_entry *rvc;
  unsigned b, sz;

  /* Calculate "bit bucket" and size as a power of two. */
  for (b = 3, sz = 8; sz && sz < size; b++, sz <<= 1)
    continue;

  cygheap_protect.acquire ();
  if (cygheap->buckets[b])
    {
      rvc = (_cmalloc_entry *) cygheap->buckets[b];
      cygheap->buckets[b] = rvc->ptr;
      rvc->b = b;
    }
  else
    {
      rvc = (_cmalloc_entry *) _csbrk (sz + sizeof (_cmalloc_entry));
      if (!rvc)
	{
	  cygheap_protect.release ();
	  return NULL;
	}

      rvc->b = b;
      rvc->prev = cygheap->chain;
      cygheap->chain = rvc;
    }
  cygheap_protect.release ();
  return rvc->data;
}

static void __stdcall __attribute__ ((regparm(1)))
_cfree (void *ptr)
{
  cygheap_protect.acquire ();
  _cmalloc_entry *rvc = to_cmalloc (ptr);
  DWORD b = rvc->b;
  rvc->ptr = cygheap->buckets[b];
  cygheap->buckets[b] = (char *) rvc;
  cygheap_protect.release ();
}

static void *__stdcall __attribute__ ((regparm(2)))
_crealloc (void *ptr, unsigned size)
{
  void *newptr;
  if (ptr == NULL)
    newptr = _cmalloc (size);
  else
    {
      unsigned oldsize = 1 << to_cmalloc (ptr)->b;
      if (size <= oldsize)
	return ptr;
      newptr = _cmalloc (size);
      if (newptr)
	{
	  memcpy (newptr, ptr, oldsize);
	  _cfree (ptr);
	}
    }
  return newptr;
}

/* End Copyright (C) 1997 DJ Delorie */

#define sizeof_cygheap(n) ((n) + sizeof (cygheap_entry))

#define N ((cygheap_entry *) NULL)
#define tocygheap(s) ((cygheap_entry *) (((char *) (s)) - (int) (N->data)))

inline static void *
creturn (cygheap_types x, cygheap_entry * c, unsigned len, const char *fn = NULL)
{
  if (c)
    /* nothing to do */;
  else if (fn)
    api_fatal ("%s would have returned NULL", fn);
  else
    {
      set_errno (ENOMEM);
      return NULL;
    }
  c->type = x;
  char *cend = ((char *) c + sizeof (*c) + len);
  if (cygheap_max < cend)
    cygheap_max = cend;
  MALLOC_CHECK;
  return (void *) c->data;
}

inline static void *
cmalloc (cygheap_types x, DWORD n, const char *fn)
{
  cygheap_entry *c;
  MALLOC_CHECK;
  c = (cygheap_entry *) _cmalloc (sizeof_cygheap (n));
  return creturn (x, c, n, fn);
}

extern "C" void *
cmalloc (cygheap_types x, DWORD n)
{
  return cmalloc (x, n, NULL);
}

extern "C" void *
cmalloc_abort (cygheap_types x, DWORD n)
{
  return cmalloc (x, n, "cmalloc");
}

inline static void *
crealloc (void *s, DWORD n, const char *fn)
{
  MALLOC_CHECK;
  if (s == NULL)
    return cmalloc (HEAP_STR, n);	// kludge

  assert (!inheap (s));
  cygheap_entry *c = tocygheap (s);
  cygheap_types t = (cygheap_types) c->type;
  c = (cygheap_entry *) _crealloc (c, sizeof_cygheap (n));
  return creturn (t, c, n, fn);
}

extern "C" void *__stdcall  __attribute__ ((regparm(2)))
crealloc (void *s, DWORD n)
{
  return crealloc (s, n, NULL);
}

extern "C" void *__stdcall  __attribute__ ((regparm(2)))
crealloc_abort (void *s, DWORD n)
{
  return crealloc (s, n, "crealloc");
}

extern "C" void __stdcall __attribute__ ((regparm(1)))
cfree (void *s)
{
  assert (!inheap (s));
  _cfree (tocygheap (s));
  MALLOC_CHECK;
}

extern "C" void __stdcall __attribute__ ((regparm(2)))
cfree_and_set (char *&s, char *what)
{
  if (s && s != almost_null)
    cfree (s);
  s = what;
}

inline static void *
ccalloc (cygheap_types x, DWORD n, DWORD size, const char *fn)
{
  cygheap_entry *c;
  MALLOC_CHECK;
  n *= size;
  c = (cygheap_entry *) _cmalloc (sizeof_cygheap (n));
  if (c)
    memset (c->data, 0, n);
  return creturn (x, c, n, fn);
}

extern "C" void *__stdcall __attribute__ ((regparm(3)))
ccalloc (cygheap_types x, DWORD n, DWORD size)
{
  return ccalloc (x, n, size, NULL);
}

extern "C" void *__stdcall __attribute__ ((regparm(3)))
ccalloc_abort (cygheap_types x, DWORD n, DWORD size)
{
  return ccalloc (x, n, size, "ccalloc");
}

extern "C" PWCHAR __stdcall __attribute__ ((regparm(1)))
cwcsdup (const PWCHAR s)
{
  MALLOC_CHECK;
  PWCHAR p = (PWCHAR) cmalloc (HEAP_STR, (wcslen (s) + 1) * sizeof (WCHAR));
  if (!p)
    return NULL;
  wcpcpy (p, s);
  MALLOC_CHECK;
  return p;
}

extern "C" PWCHAR __stdcall __attribute__ ((regparm(1)))
cwcsdup1 (const PWCHAR s)
{
  MALLOC_CHECK;
  PWCHAR p = (PWCHAR) cmalloc (HEAP_1_STR, (wcslen (s) + 1) * sizeof (WCHAR));
  if (!p)
    return NULL;
  wcpcpy (p, s);
  MALLOC_CHECK;
  return p;
}

extern "C" char *__stdcall __attribute__ ((regparm(1)))
cstrdup (const char *s)
{
  MALLOC_CHECK;
  char *p = (char *) cmalloc (HEAP_STR, strlen (s) + 1);
  if (!p)
    return NULL;
  strcpy (p, s);
  MALLOC_CHECK;
  return p;
}

extern "C" char *__stdcall __attribute__ ((regparm(1)))
cstrdup1 (const char *s)
{
  MALLOC_CHECK;
  char *p = (char *) cmalloc (HEAP_1_STR, strlen (s) + 1);
  if (!p)
    return NULL;
  strcpy (p, s);
  MALLOC_CHECK;
  return p;
}

void
cygheap_root::set (const char *posix, const char *native, bool caseinsensitive)
{
  if (*posix == '/' && posix[1] == '\0')
    {
      if (m)
	{
	  cfree (m);
	  m = NULL;
	}
      return;
    }
  if (!m)
    m = (struct cygheap_root_mount_info *) ccalloc (HEAP_MOUNT, 1, sizeof (*m));
  strcpy (m->posix_path, posix);
  m->posix_pathlen = strlen (posix);
  if (m->posix_pathlen >= 1 && m->posix_path[m->posix_pathlen - 1] == '/')
    m->posix_path[--m->posix_pathlen] = '\0';

  strcpy (m->native_path, native);
  m->native_pathlen = strlen (native);
  if (m->native_pathlen >= 1 && m->native_path[m->native_pathlen - 1] == '\\')
    m->native_path[--m->native_pathlen] = '\0';
  m->caseinsensitive = caseinsensitive;
}

cygheap_user::~cygheap_user ()
{
}

void
cygheap_user::set_name (const char *new_name)
{
  bool allocated = !!pname;

  if (allocated)
    {
      /* Windows user names are case-insensitive.  Here we want the correct
	 username, though, even if it only differs by case. */
      if (!strcmp (new_name, pname))
	return;
      cfree (pname);
    }

  pname = cstrdup (new_name ? new_name : "");
  if (!allocated)
    return;		/* Initializing.  Don't bother with other stuff. */

  cfree_and_set (homedrive);
  cfree_and_set (homepath);
  cfree_and_set (plogsrv);
  cfree_and_set (pdomain);
  cfree_and_set (pwinname);
}
