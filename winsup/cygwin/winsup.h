/* winsup.h: main Cygwin header file.

   Copyright 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004,
   2005 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifdef DEBUGIT
#define spf(a, b, c) small_printf (a, b, c)
#else
#define spf(a, b, c) do {} while (0)
#endif

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#define __INSIDE_CYGWIN__

#define strlen __builtin_strlen
#define strcmp __builtin_strcmp
#define strcpy __builtin_strcpy
#define memcpy __builtin_memcpy
#define memcmp __builtin_memcmp
#ifdef HAVE_BUILTIN_MEMSET
# define memset __builtin_memset
#endif

#define NO_COPY __attribute__((nocommon)) __attribute__((section(".data_cygwin_nocopy")))
#define NO_COPY_INIT __attribute__((section(".data_cygwin_nocopy")))

#define EXPORT_ALIAS(sym,symalias) extern "C" __typeof (sym) symalias __attribute__ ((alias(#sym)));

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ >= 199900L
#define NEW_MACRO_VARARGS
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include <sys/types.h>
#include <sys/strace.h>

/* Declarations for functions used in C and C++ code. */
#ifdef __cplusplus
extern "C" {
#endif
extern __uid32_t getuid32 (void);
extern __uid32_t geteuid32 (void);
extern int seteuid32 (__uid32_t);
extern __gid32_t getegid32 (void);
extern struct passwd *getpwuid32 (__uid32_t);
extern struct passwd *getpwnam (const char *);
extern struct __sFILE64 *fopen64 (const char *, const char *);
extern struct hostent *cygwin_gethostbyname (const char *name);
extern unsigned long cygwin_inet_addr (const char *cp);

#ifdef __cplusplus
}
#endif

/* Note that MAX_PATH is defined in the windows headers */
/* There is also PATH_MAX and MAXPATHLEN.
   PATH_MAX is from Posix and does *not* include the trailing NUL.
   MAXPATHLEN is from Unix.

   Thou shalt use CYG_MAX_PATH throughout.  It avoids the NUL vs no-NUL
   issue and is neither of the Unixy ones [so we can punt on which
   one is the right one to use].

   Windows ANSI calls are limited to MAX_PATH in length. Cygwin calls that
   thunk through to Windows Wide calls are limited to 32K. We define
   CYG_MAX_PATH as a convenient, not to short, not too long 'happy medium'.

   */

#define CYG_MAX_PATH (MAX_PATH)

#ifdef __cplusplus

extern const char case_folded_lower[];
#define cyg_tolower(c) (case_folded_lower[(unsigned char)(c)])
extern const char case_folded_upper[];
#define cyg_toupper(c) (case_folded_upper[(unsigned char)(c)])

#ifndef MALLOC_DEBUG
#define cfree newlib_cfree_dont_use
#endif

#define WIN32_LEAN_AND_MEAN 1
#define _WINGDI_H
#define _WINUSER_H
#define _WINNLS_H
#define _WINVER_H
#define _WINNETWK_H
#define _WINSVC_H
#include <windows.h>
#include <wincrypt.h>
#include <lmcons.h>
#undef _WINGDI_H
#undef _WINUSER_H
#undef _WINNLS_H
#undef _WINVER_H
#undef _WINNETWK_H
#undef _WINSVC_H

#include "wincap.h"

/* The one function we use from winuser.h most of the time */
extern "C" DWORD WINAPI GetLastError (void);

enum codepage_type {ansi_cp, oem_cp};
extern codepage_type current_codepage;

UINT get_cp ();

int __stdcall sys_wcstombs(char *, const WCHAR *, int)
  __attribute__ ((regparm(3)));

int __stdcall sys_mbstowcs(WCHAR *, const char *, int)
  __attribute__ ((regparm(3)));

/* Used to check if Cygwin DLL is dynamically loaded. */
extern int dynamically_loaded;

extern int cygserver_running;

#define _MT_SAFE	// DELTEME someday

#define TITLESIZE 1024

#include "debug.h"

/* Events/mutexes */
extern HANDLE tty_mutex;

/**************************** Convenience ******************************/

/* Used to define status flag accessor methods */
#define IMPLEMENT_STATUS_FLAG(type,flag) \
  void flag (type val) { status.flag = (val); } \
  type flag () const { return (type) status.flag; }

/* Used when treating / and \ as equivalent. */
#define isdirsep(ch) \
    ({ \
	char __c = (ch); \
	((__c) == '/' || (__c) == '\\'); \
    })

/* Convert a signal to a signal mask */
#define SIGTOMASK(sig)	(1 << ((sig) - signal_shift_subtract))
extern unsigned int signal_shift_subtract;

#ifdef NEW_MACRO_VARARGS
# define api_fatal(...) __api_fatal (__VA_ARGS__)
#else
# define api_fatal(fmt, args...) __api_fatal ("%P: *** " fmt,## args)
#endif

#undef issep
#define issep(ch) (strchr (" \t\n\r", (ch)) != NULL)

#define isabspath(p) \
  (isdirsep (*(p)) || (isalpha (*(p)) && (p)[1] == ':' && (!(p)[2] || isdirsep ((p)[2]))))

/******************** Initialization/Termination **********************/

class per_process;
/* cygwin .dll initialization */
void dll_crt0 (per_process *) __asm__ ("_dll_crt0__FP11per_process");
extern "C" void __stdcall _dll_crt0 ();

/* dynamically loaded dll initialization */
extern "C" int dll_dllcrt0 (HMODULE, per_process *);

/* dynamically loaded dll initialization for non-cygwin apps */
extern "C" int dll_noncygwin_dllcrt0 (HMODULE, per_process *);

/* exit the program */

enum exit_states
  {
    ES_NOT_EXITING = 0,
    ES_EVENTS_TERMINATE,
    ES_THREADTERM,
    ES_SIGNAL,
    ES_CLOSEALL,
    ES_SIGPROCTERMINATE,
    ES_TITLE,
    ES_HUP_PGRP,
    ES_HUP_SID,
    ES_TTY_TERMINATE,
    ES_FINAL
  };

extern exit_states exit_state;
void __stdcall do_exit (int) __attribute__ ((regparm (1), noreturn));

/* UID/GID */
void uinfo_init (void);

#define ILLEGAL_UID16 ((__uid16_t)-1)
#define ILLEGAL_UID ((__uid32_t)-1)
#define ILLEGAL_GID16 ((__gid16_t)-1)
#define ILLEGAL_GID ((__gid32_t)-1)
#define ILLEGAL_SEEK ((_off64_t)-1)

#define uid16touid32(u16)  ((u16)==ILLEGAL_UID16?ILLEGAL_UID:(__uid32_t)(u16))
#define gid16togid32(g16)  ((g16)==ILLEGAL_GID16?ILLEGAL_GID:(__gid32_t)(g16))

/* Convert LARGE_INTEGER into long long */
#define get_ll(pl)  (((long long) (pl).HighPart << 32) | (pl).LowPart)

/* various events */
void events_init (void);
void events_terminate (void);

void __stdcall close_all_files ();

/* Globals that handle initialization of winsock in a child process. */
extern HANDLE wsock32_handle;
extern HANDLE ws2_32_handle;

/* Globals that handle initialization of netapi in a child process. */
extern HANDLE netapi32_handle;

/* debug_on_trap support. see exceptions.cc:try_to_debug() */
extern "C" void error_start_init (const char*);
extern "C" int try_to_debug (bool waitloop = 1);

void set_file_api_mode (codepage_type);

extern bool cygwin_finished_initializing;

/**************************** Miscellaneous ******************************/

void __stdcall set_std_handle (int);
int __stdcall stat_dev (DWORD, int, unsigned long, struct __stat64 *);

__ino64_t __stdcall hash_path_name (__ino64_t hash, const char *name) __attribute__ ((regparm(2)));
void __stdcall nofinalslash (const char *src, char *dst) __attribute__ ((regparm(2)));
extern "C" char *__stdcall rootdir (const char *full_path, char *root_path) __attribute__ ((regparm(2)));

/* String manipulation */
extern "C" char *__stdcall strccpy (char *s1, const char **s2, char c);
extern "C" int __stdcall strcasematch (const char *s1, const char *s2) __attribute__ ((regparm(2)));
extern "C" int __stdcall strncasematch (const char *s1, const char *s2, size_t n) __attribute__ ((regparm(3)));
extern "C" char *__stdcall strcasestr (const char *searchee, const char *lookfor) __attribute__ ((regparm(2)));

/* Time related */
void __stdcall totimeval (struct timeval *, FILETIME *, int, int);
long __stdcall to_time_t (FILETIME *);
void __stdcall to_timestruc_t (FILETIME *, timestruc_t *);
void __stdcall time_as_timestruc_t (timestruc_t *);
void __stdcall timeval_to_filetime (const struct timeval *, FILETIME *);

void __stdcall set_console_title (char *);
void init_console_handler ();
void init_global_security ();

int __stdcall check_null_str (const char *name) __attribute__ ((regparm(1)));
int __stdcall check_null_empty_str (const char *name) __attribute__ ((regparm(1)));
int __stdcall check_null_empty_str_errno (const char *name) __attribute__ ((regparm(1)));
int __stdcall check_null_str_errno (const char *name) __attribute__ ((regparm(1)));
int __stdcall __check_null_invalid_struct (void *s, unsigned sz) __attribute__ ((regparm(2)));
int __stdcall __check_null_invalid_struct_errno (void *s, unsigned sz) __attribute__ ((regparm(2)));
int __stdcall __check_invalid_read_ptr (const void *s, unsigned sz) __attribute__ ((regparm(2)));
int __stdcall __check_invalid_read_ptr_errno (const void *s, unsigned sz) __attribute__ ((regparm(2)));
int __stdcall check_invalid_virtual_addr (const void *s, unsigned sz) __attribute__ ((regparm(2)));

#define check_null_invalid_struct(s) \
  __check_null_invalid_struct ((s), sizeof (*(s)))
#define check_null_invalid_struct_errno(s) \
  __check_null_invalid_struct_errno ((s), sizeof (*(s)))
#define check_invalid_read_struct_errno(s) \
  __check_invalid_read_ptr_errno ((s), sizeof (*(s)))

struct iovec;
ssize_t check_iovec_for_read (const struct iovec *, int) __attribute__ ((regparm(2)));
ssize_t check_iovec_for_write (const struct iovec *, int) __attribute__ ((regparm(2)));

#define set_winsock_errno() __set_winsock_errno (__FUNCTION__, __LINE__)
void __set_winsock_errno (const char *fn, int ln) __attribute__ ((regparm(2)));

extern bool wsock_started;

/* Printf type functions */
extern "C" void __api_fatal (const char *, ...) __attribute__ ((noreturn));
extern "C" int __small_sprintf (char *dst, const char *fmt, ...) /*__attribute__ ((regparm (2)))*/;
extern "C" int __small_vsprintf (char *dst, const char *fmt, va_list ap) /*__attribute__ ((regparm (3)))*/;
extern void multiple_cygwin_problem (const char *, unsigned, unsigned);

extern "C" void vklog (int priority, const char *message, va_list ap);
extern "C" void klog (int priority, const char *message, ...);
int child_copy (HANDLE, DWORD, const char *, void *, void *);

int symlink_worker (const char *, const char *, bool, bool)
  __attribute__ ((regparm (3)));

class path_conv;

int fcntl_worker (int fd, int cmd, void *arg);

extern "C" int low_priority_sleep (DWORD) __attribute__ ((regparm (1)));
#define SLEEP_0_STAY_LOW INFINITE

size_t getshmlba (void);

int winprio_to_nice (DWORD) __attribute__ ((regparm (1)));
DWORD nice_to_winprio (int &) __attribute__ ((regparm (1)));

/**************************** Exports ******************************/

extern "C" {
int cygwin_select (int , fd_set *, fd_set *, fd_set *,
		   struct timeval *to);
int cygwin_gethostname (char *__name, size_t __len);

extern DWORD binmode;
extern char _data_start__, _data_end__, _bss_start__, _bss_end__;
extern void (*__CTOR_LIST__) (void);
extern void (*__DTOR_LIST__) (void);
extern SYSTEM_INFO system_info;
};

/*************************** Unsorted ******************************/

#define WM_ASYNCIO	0x8000		// WM_APP


#define STD_RBITS (S_IRUSR | S_IRGRP | S_IROTH)
#define STD_WBITS (S_IWUSR)
#define STD_XBITS (S_IXUSR | S_IXGRP | S_IXOTH)
#define NO_W ~(S_IWUSR | S_IWGRP | S_IWOTH)
#define NO_R ~(S_IRUSR | S_IRGRP | S_IROTH)
#define NO_X ~(S_IXUSR | S_IXGRP | S_IXOTH)

/* The title on program start. */
extern char *old_title;
extern bool display_title;

extern HANDLE hMainThread;
extern HANDLE hMainProc;
extern HANDLE hProcToken;
extern HANDLE hProcImpToken;

extern bool cygwin_testing;

extern char almost_null[];

#define winsock2_active (wsadata.wVersion >= 512)
extern struct WSAData wsadata;

#endif /* defined __cplusplus */
