/* _cygwin_S_IEXEC.cc: stat helper stuff

   Copyright 2001 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#if 0
#include "windows.h"
#include <sys/cygwin.h>
#include "perprocess.h"
#endif
#include <sys/stat.h>
#include <sys/unistd.h>

const unsigned _cygwin_S_IEXEC = S_IEXEC;
const unsigned _cygwin_S_IXUSR = S_IXUSR;
const unsigned _cygwin_S_IXGRP = S_IXGRP;
const unsigned _cygwin_S_IXOTH = S_IXOTH;
const unsigned _cygwin_X_OK = X_OK;

extern int __declspec (dllimport) _check_for_executable;
struct _cygwin_bob__
{
  _cygwin_bob__ () {_check_for_executable = 1;}
} _cygwin_dummy_bob__;
