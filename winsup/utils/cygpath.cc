/* cygpath.cc -- convert pathnames between Windows and Unix format
   Copyright 1998, 1999, 2000, 2001, 2002 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#define NOCOMATTRIBUTE

#include <shlobj.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <getopt.h>
#include <windows.h>
#include <io.h>
#include <sys/fcntl.h>
#include <sys/cygwin.h>
#include <ctype.h>

static const char version[] = "$Revision$";

static char *prog_name;
static char *file_arg;
static char *close_arg;
static int path_flag, unix_flag, windows_flag, absolute_flag;
static int shortname_flag, longname_flag;
static int ignore_flag, allusers_flag, output_flag;

static struct option long_options[] = {
  {(char *) "help", no_argument, NULL, 'h'},
  {(char *) "absolute", no_argument, NULL, 'a'},
  {(char *) "option", no_argument, NULL, 'o'},
  {(char *) "path", no_argument, NULL, 'p'},
  {(char *) "close", required_argument, (int *) &close_arg, 'c'},
  {(char *) "unix", no_argument, NULL, 'u'},
  {(char *) "file", required_argument, (int *) &file_arg, 'f'},
  {(char *) "version", no_argument, NULL, 'v'},
  {(char *) "windows", no_argument, NULL, 'w'},
  {(char *) "short-name", no_argument, NULL, 's'},
  {(char *) "long-name", no_argument, NULL, 'l'},
  {(char *) "windir", no_argument, NULL, 'W'},
  {(char *) "sysdir", no_argument, NULL, 'S'},
  {(char *) "ignore", no_argument, NULL, 'i'},
  {(char *) "allusers", no_argument, NULL, 'A'},
  {(char *) "desktop", no_argument, NULL, 'D'},
  {(char *) "smprograms", no_argument, NULL, 'P'},
  {(char *) "homeroot", no_argument, NULL, 'H'},
  {0, no_argument, 0, 0}
};

static void
usage (FILE * stream, int status)
{
  if (!ignore_flag || !status)
    fprintf (stream, "\
Usage: %s (-u|--unix)|(-w|--windows) [options] filename\n\n\
  -u|--unix		print Unix form of filename\n\
  -w|--windows		print Windows form of filename\n\n\
Other options:\n\
  -a|--absolute		output absolute path\n\
  -c|--close handle	close handle (for use in captured process)\n\
  -f|--file file	read file for input path information\n\
  -i|--ignore		ignore missing argument\n\
  -l|--long-name	print Windows long form of filename (with -w only)\n\
  -p|--path		filename argument is a path\n\
  -s|--short-name	print Windows short form of filename (with -w only)\n\
  -A|--allusers		use `All Users' instead of current user for -D, -P\n\
  -D|--desktop		output `Desktop' directory and exit\n\
  -H|--homeroot		output `Profiles' directory (home root) and exit\n\
  -P|--smprograms	output Start Menu `Programs' directory and exit\n\
  -S|--sysdir		output system directory and exit\n\
  -W|--windir		output `Windows' directory and exit\n\n\
Informative output:\n\
  -h|--help             print this help, then exit\n\
  -v|--version		output version information and exit\n", prog_name);
  exit (ignore_flag ? 0 : status);
}

static char *
get_short_paths (char *path)
{
  char *sbuf;
  char *sptr;
  char *next;
  char *ptr = path;
  char *end = strrchr (path, 0);
  DWORD acc = 0;
  DWORD len;

  while (ptr != NULL)
    {
      next = ptr;
      ptr = strchr (ptr, ';');
      if (ptr)
	*ptr++ = 0;
      len = GetShortPathName (next, NULL, 0);
      if (len == 0 && GetLastError () == ERROR_INVALID_PARAMETER)
	{
	  fprintf (stderr, "%s: cannot create short name of %s\n", prog_name,
		   next);
	  exit (2);
	}
      acc += len + 1;
    }
  sptr = sbuf = (char *) malloc (acc + 1);
  if (sbuf == NULL)
    {
      fprintf (stderr, "%s: out of memory\n", prog_name);
      exit (1);
    }
  ptr = path;
  for (;;)
    {
      len = GetShortPathName (ptr, sptr, acc);
      if (len == 0 && GetLastError () == ERROR_INVALID_PARAMETER)
	{
	  fprintf (stderr, "%s: cannot create short name of %s\n", prog_name,
		   ptr);
	  exit (2);
	}

      ptr = strrchr (ptr, 0);
      sptr = strrchr (sptr, 0);
      if (ptr == end)
	break;
      *sptr = ';';
      ++ptr, ++sptr;
      acc -= len + 1;
    }
  return sbuf;
}

static char *
get_short_name (const char *filename)
{
  char *sbuf, buf[MAX_PATH];
  DWORD len = GetShortPathName (filename, buf, MAX_PATH);
  if (len == 0 && GetLastError () == ERROR_INVALID_PARAMETER)
    {
      fprintf (stderr, "%s: cannot create short name of %s\n", prog_name,
	       filename);
      exit (2);
    }
  sbuf = (char *) malloc (++len);
  if (sbuf == NULL)
    {
      fprintf (stderr, "%s: out of memory\n", prog_name);
      exit (1);
    }
  return strcpy (sbuf, buf);
}

static DWORD
get_long_path_name_w32impl (LPCSTR src, LPSTR sbuf, DWORD)
{
  char buf1[MAX_PATH], buf2[MAX_PATH], *ptr;
  const char *pelem, *next;
  WIN32_FIND_DATA w32_fd;
  int len;
  
  strcpy (buf1, src);
  *buf2 = 0;
  pelem = src;
  ptr = buf2;
  while (pelem)
    {
      next = pelem;
      if (*next == '\\')
	{
	  strcat (ptr++, "\\");
	  pelem++;
	  if (!*pelem)
	    break;
	  continue;
	}
      pelem = strchr (next, '\\');
      len = pelem ? (pelem++ - next) : strlen (next);
      strncpy (ptr, next, len);
      ptr[len] = 0;
      if (next[1] != ':' && strcmp(next, ".") && strcmp(next, ".."))
	{
	  if (FindFirstFile (buf2, &w32_fd) != INVALID_HANDLE_VALUE)
	    strcpy (ptr, w32_fd.cFileName);
	}
      ptr += strlen (ptr);
      if (pelem)
	{
	  *ptr++ = '\\';
	  *ptr = 0;
	}
    }
  if (sbuf)
    strcpy (sbuf, buf2);
  SetLastError (0);
  return strlen (buf2) + (sbuf ? 0 : 1);
}

static char *
get_long_paths (char *path)
{
  char *sbuf;
  char *sptr;
  char *next;
  char *ptr = path;
  char *end = strrchr (path, 0);
  DWORD acc = 0;
  DWORD len;

  HINSTANCE hinst;
  DWORD (*GetLongPathNameAPtr) (LPCSTR, LPSTR, DWORD) = 0;
  hinst = LoadLibrary ("kernel32");
  if (hinst)
    GetLongPathNameAPtr = (DWORD (*) (LPCSTR, LPSTR, DWORD))
      GetProcAddress (hinst, "GetLongPathNameA");
  /* subsequent calls of kernel function with NULL cause SegFault in W2K!! */
  if (1 || !GetLongPathNameAPtr)
    GetLongPathNameAPtr = get_long_path_name_w32impl;

  while (ptr != NULL)
    {
      next = ptr;
      ptr = strchr (ptr, ';');
      if (ptr)
	*ptr++ = 0;
      len = (*GetLongPathNameAPtr) (next, NULL, 0);
      if (len == 0 && GetLastError () == ERROR_INVALID_PARAMETER)
	{
	  fprintf (stderr, "%s: cannot create long name of %s\n", prog_name,
		   next);
	  exit (2);
	}
      acc += len + 1;
    }
  sptr = sbuf = (char *) malloc (acc + 1);
  if (sbuf == NULL)
    {
      fprintf (stderr, "%s: out of memory\n", prog_name);
      exit (1);
    }
  ptr = path;
  for (;;)
    {
      len = (*GetLongPathNameAPtr) (ptr, sptr, acc);
      if (len == 0 && GetLastError () == ERROR_INVALID_PARAMETER)
	{
	  fprintf (stderr, "%s: cannot create long name of %s\n", prog_name,
		   ptr);
	  exit (2);
	}

      ptr = strrchr (ptr, 0);
      sptr = strrchr (sptr, 0);
      if (ptr == end)
	break;
      *ptr = *sptr = ';';
      ++ptr, ++sptr;
      acc -= len + 1;
    }
  return sbuf;
}

static char *
get_long_name (const char *filename)
{
  char *sbuf, buf[MAX_PATH];
  DWORD len;
  HINSTANCE hinst;
  DWORD (*GetLongPathNameAPtr) (LPCSTR, LPSTR, DWORD) = 0;
  hinst = LoadLibrary ("kernel32");
  if (hinst)
    GetLongPathNameAPtr = (DWORD (*) (LPCSTR, LPSTR, DWORD))
      GetProcAddress (hinst, "GetLongPathNameA");
  if (!GetLongPathNameAPtr)
    GetLongPathNameAPtr = get_long_path_name_w32impl;
  
  len = (*GetLongPathNameAPtr) (filename, buf, MAX_PATH);
  if (len == 0 && GetLastError () == ERROR_INVALID_PARAMETER)
    {
      fprintf (stderr, "%s: cannot create long name of %s\n", prog_name,
	       filename);
      exit (2);
    }
  sbuf = (char *) malloc (++len);
  if (sbuf == NULL)
    {
      fprintf (stderr, "%s: out of memory\n", prog_name);
      exit (1);
    }
  return strcpy (sbuf, buf);
}

static void
dowin (char option)
{
  char *buf, buf1[MAX_PATH], buf2[MAX_PATH];
  DWORD len = MAX_PATH;
  WIN32_FIND_DATA w32_fd;
  LPITEMIDLIST id;
  HINSTANCE hinst;
  BOOL (*GetProfilesDirectoryAPtr) (LPSTR, LPDWORD) = 0;
      
  buf = buf1;
  switch (option)
    {
    case 'D':
      SHGetSpecialFolderLocation (NULL, allusers_flag ? 
	CSIDL_COMMON_DESKTOPDIRECTORY : CSIDL_DESKTOPDIRECTORY, &id);
      SHGetPathFromIDList (id, buf);
      /* This if clause is a Fix for Win95 without any "All Users" */
      if (strlen (buf) == 0)
	{
	  SHGetSpecialFolderLocation (NULL, CSIDL_DESKTOPDIRECTORY, &id);
	  SHGetPathFromIDList (id, buf);
	}
      break;

    case 'P':
      SHGetSpecialFolderLocation (NULL, allusers_flag ? 
	CSIDL_COMMON_PROGRAMS : CSIDL_PROGRAMS, &id);
      SHGetPathFromIDList (id, buf);
      /* This if clause is a Fix for Win95 without any "All Users" */
      if (strlen (buf) == 0)
	{
	  SHGetSpecialFolderLocation (NULL, CSIDL_PROGRAMS, &id);
	  SHGetPathFromIDList (id, buf);
	}
      break;

    case 'H':
      hinst = LoadLibrary ("userenv");
      if (hinst)
	GetProfilesDirectoryAPtr = (BOOL (*) (LPSTR, LPDWORD))
	  GetProcAddress (hinst, "GetProfilesDirectoryA");
      if (GetProfilesDirectoryAPtr)
        (*GetProfilesDirectoryAPtr) (buf, &len);
      else
	{
	  GetWindowsDirectory (buf, MAX_PATH);
	  strcat (buf, "\\Profiles");
	}
      break;

    case 'S':
      GetSystemDirectory (buf, MAX_PATH);
      FindFirstFile (buf, &w32_fd);
      strcpy (strrchr (buf, '\\') + 1, w32_fd.cFileName);
      break;

    case 'W':
      GetWindowsDirectory (buf, MAX_PATH);
      break;

    default:
      usage (stderr, 1);
    }

  if (!windows_flag)
    {
      cygwin_conv_to_posix_path (buf, buf2);
      buf = buf2;
    }
  else
    {
      if (shortname_flag)
        buf = get_short_name (buf);
    }
  printf ("%s\n", buf);
  exit (0);
}

static void
doit (char *filename)
{
  char *buf;
  size_t len;
  int retval;
  int (*conv_func) (const char *, char *);

  if (path_flag)
    {
      if (cygwin_posix_path_list_p (filename) ? unix_flag : windows_flag)
	{
	  /* The path is already in the right format.  */
	  puts (filename);
	  exit (0);
	}
    }

  if (!path_flag)
    {
      len = strlen (filename) + 100;
      if (len == 100)
	{
	  if (!ignore_flag)
	    {
	      fprintf (stderr, "%s: can't convert empty path\n", prog_name);
	      exit (1);
	    }
	  else
	    exit (0);
	}
    }
  else
    {
      if (unix_flag)
	len = cygwin_win32_to_posix_path_list_buf_size (filename);
      else
	len = cygwin_posix_to_win32_path_list_buf_size (filename);
    }

  if (len < PATH_MAX)
    len = PATH_MAX;

  buf = (char *) malloc (len);
  if (buf == NULL)
    {
      fprintf (stderr, "%s: out of memory\n", prog_name);
      exit (1);
    }

  if (path_flag)
    {
      if (unix_flag)
	cygwin_win32_to_posix_path_list (filename, buf);
      else
	{
	  cygwin_posix_to_win32_path_list (filename, buf);
	  if (shortname_flag)
	    buf = get_short_paths (buf);
	  if (longname_flag)
	    buf = get_long_paths (buf);
	}
    }
  else
    {
      if (unix_flag)
	conv_func = (absolute_flag ? cygwin_conv_to_full_posix_path :
		     cygwin_conv_to_posix_path);
      else
	conv_func = (absolute_flag ? cygwin_conv_to_full_win32_path :
		     cygwin_conv_to_win32_path);
      retval = conv_func (filename, buf);
      if (retval < 0)
	{
	  fprintf (stderr, "%s: error converting \"%s\"\n",
		   prog_name, filename);
	  exit (1);
	}
      if (!unix_flag)
	{
	if (shortname_flag)
	  buf = get_short_name (buf);
	if (longname_flag)
	  buf = get_long_name (buf);
	}
    }

  puts (buf);
}

static void
print_version ()
{
  const char *v = strchr (version, ':');
  int len;
  if (!v)
    {
      v = "?";
      len = 1;
    }
  else
    {
      v += 2;
      len = strchr (v, ' ') - v;
    }
  printf ("\
cygpath (cygwin) %.*s\n\
Path Conversion Utility\n\
Copyright 1998, 1999, 2000, 2001, 2002 Red Hat, Inc.\n\
Compiled on %s", len, v, __DATE__);
}

int
main (int argc, char **argv)
{
  int c, o = 0;
  int options_from_file_flag;
  char *filename;

  prog_name = strrchr (argv[0], '/');
  if (prog_name == NULL)
    prog_name = strrchr (argv[0], '\\');
  if (prog_name == NULL)
    prog_name = argv[0];
  else
    prog_name++;

  path_flag = 0;
  unix_flag = 0;
  windows_flag = 0;
  shortname_flag = 0;
  longname_flag = 0;
  ignore_flag = 0;
  options_from_file_flag = 0;
  allusers_flag = 0;
  output_flag = 0;
  while ((c =
	  getopt_long (argc, argv, (char *) "hac:f:opslSuvwWiDPAH",
		       long_options, (int *) NULL)) != EOF)
    {
      switch (c)
	{
	case 'a':
	  absolute_flag = 1;
	  break;

	case 'c':
	  CloseHandle ((HANDLE) strtoul (optarg, NULL, 16));
	  break;

	case 'f':
	  file_arg = optarg;
	  break;

	case 'o':
	  options_from_file_flag = 1;
	  break;

	case 'p':
	  path_flag = 1;
	  break;

	case 'u':
	  if (unix_flag || windows_flag)
	    usage (stderr, 1);
	  unix_flag = 1;
	  break;

	case 'w':
	  if (unix_flag || windows_flag)
	    usage (stderr, 1);
	  windows_flag = 1;
	  break;

	case 'l':
	  if (unix_flag || shortname_flag)
	    usage (stderr, 1);
	  longname_flag = 1;
	  break;

	case 's':
	  if (unix_flag || longname_flag)
	    usage (stderr, 1);
	  shortname_flag = 1;
	  break;

	case 'A':
	  allusers_flag = 1;
	  break;

	case 'D':
	case 'H':
	case 'P':
	case 'S':
	case 'W':
	  if (output_flag)
	    usage (stderr, 1);
	  output_flag = 1;
	  o = c;
	  break;

	case 'i':
	  ignore_flag = 1;
	  break;

	case 'h':
	  usage (stdout, 0);
	  break;

	case 'v':
	  print_version ();
	  exit (0);

	default:
	  usage (stderr, 1);
	  break;
	}

    }

  if (options_from_file_flag && !file_arg)
    usage (stderr, 1);

  if (!output_flag && !unix_flag && !windows_flag && !options_from_file_flag)
    usage (stderr, 1);

  if (!file_arg)
    {
      if (output_flag)
	dowin (o);

      if (optind != argc - 1)
	usage (stderr, 1);

      filename = argv[optind];
      doit (filename);
    }
  else
    {
      FILE *fp;
      char buf[PATH_MAX * 2 + 1];

      if (argv[optind])
	usage (stderr, 1);

      if (strcmp (file_arg, "-") != 0)
	fp = fopen (file_arg, "rt");
      else
	{
	  fp = stdin;
	  setmode (0, O_TEXT);
	}
      if (fp == NULL)
	{
	  perror ("cygpath");
	  exit (1);
	}

      setbuf (stdout, NULL);
      while (fgets (buf, sizeof (buf), fp) != NULL)
	{
	  char *s = buf;
	  char *p = strchr (s, '\n');
	  if (p)
	    *p = '\0';
	  if (options_from_file_flag && *s == '-')
	    {
	      char c;
	      for (c = *++s; c && !isspace (c); c = *++s)
		switch (c)
		  {
		  case 'a':
		    absolute_flag = 1;
		    break;
		  case 'i':
		    ignore_flag = 1;
		    break;
		  case 's':
		    shortname_flag = 1;
		    longname_flag = 0;
		    break;
		  case 'l':
		    shortname_flag = 0;
		    longname_flag = 1;
		    break;
		  case 'w':
		    unix_flag = 0;
		    windows_flag = 1;
		    break;
		  case 'u':
		    windows_flag = 0;
		    unix_flag = 1;
		    break;
		  case 'p':
		    path_flag = 1;
		    break;
		  case 'D':
		  case 'H':
		  case 'P':
		  case 'S':
		  case 'W':
	  	    output_flag = 1;
		    o = c;
	  	    break;
		  }
	      if (*s)
		do
		  s++;
		while (*s && isspace (*s));
	    }
	  if (*s && !output_flag)
	    doit (s);
	  if (!*s && output_flag)
	    dowin (o);
	}
    }

  exit (0);
}
