#ifndef _WINABLE_H
#define _WINABLE_H
#if __GNUC__ >=3
#pragma GCC system_header
#endif

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#if (_WIN32_WINNT < 0x0403)
#define INPUT_MOUSE 0
#define INPUT_KEYBOARD 1
#define INPUT_HARDWARE 2
#endif /* (_WIN32_WINNT < 0x04030) */
#if (WINVER < 0x0500)
#define CHILDID_SELF 0
#define OBJID_WINDOW 0x00000000
#define OBJID_SYSMENU 0xFFFFFFFF
#define OBJID_TITLEBAR 0xFFFFFFFE
#define OBJID_MENU 0xFFFFFFFD
#define OBJID_CLIENT 0xFFFFFFFC
#define OBJID_VSCROLL 0xFFFFFFFB
#define OBJID_HSCROLL 0xFFFFFFFA
#define OBJID_SIZEGRIP 0xFFFFFFF9
#define OBJID_CARET 0xFFFFFFF8
#define OBJID_CURSOR 0xFFFFFFF7
#define OBJID_ALERT 0xFFFFFFF6
#define OBJID_SOUND 0xFFFFFFF5
#define GUI_CARETBLINKING 0x00000001
#define GUI_INMOVESIZE 0x00000002
#define GUI_INMENUMODE 0x00000004
#define GUI_SYSTEMMENUMODE 0x00000008
#define GUI_POPUPMENUMODE 0x00000010
typedef struct tagGUITHREADINFO {
	DWORD cbSize;
	DWORD flags;
	HWND hwndActive;
	HWND hwndFocus;
	HWND hwndCapture;
	HWND hwndMenuOwner;
	HWND hwndMoveSize;
	HWND hwndCaret;
	RECT rcCaret;
} GUITHREADINFO,*PGUITHREADINFO;
#endif /* (WINVER < 0x0500) */

#ifdef __cplusplus
}
#endif
#endif /* _WINABLE_H */
