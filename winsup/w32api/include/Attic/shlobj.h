#ifndef _SHLOBJ_H
#define _SHLOBJ_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ole2.h>
#include <shlguid.h>
#include <shellapi.h>
#pragma pack(push,1)
#include <commctrl.h>

#define BIF_RETURNONLYFSDIRS 1
#define BIF_DONTGOBELOWDOMAIN 2
#define BIF_STATUSTEXT 4
#define BIF_RETURNFSANCESTORS 8
#define BIF_EDITBOX 16
#define BIF_VALIDATE 32
#define BIF_NEWDIALOGSTYLE 64
#define BIF_BROWSEINCLUDEURLS 128
#define BIF_USENEWUI ( BIF_EDITBOX | BIF_NEWDIALOGSTYLE )
#define BIF_BROWSEFORCOMPUTER 0x1000
#define BIF_BROWSEFORPRINTER 0x2000
#define BIF_BROWSEINCLUDEFILES 0x4000
#define BIF_SHAREABLE 0x8000
#define BFFM_INITIALIZED 1
#define BFFM_SELCHANGED 2
#define BFFM_SETSTATUSTEXT (WM_USER + 100)
#define BFFM_ENABLEOK (WM_USER + 101)
#define BFFM_SETSELECTION (WM_USER + 102)
#define DVASPECT_SHORTNAME 2
#define SHARD_PIDL	1
#define SHARD_PATH	2
#define SHCNE_RENAMEITEM	1
#define SHCNE_CREATE	2
#define SHCNE_DELETE	4
#define SHCNE_MKDIR	8
#define SHCNE_RMDIR	16
#define SHCNE_MEDIAINSERTED	32
#define SHCNE_MEDIAREMOVED	64
#define SHCNE_DRIVEREMOVED	128
#define SHCNE_DRIVEADD	256
#define SHCNE_NETSHARE	512
#define SHCNE_NETUNSHARE	1024
#define SHCNE_ATTRIBUTES	2048
#define SHCNE_UPDATEDIR	4096
#define SHCNE_UPDATEITEM	8192
#define SHCNE_SERVERDISCONNECT	16384
#define SHCNE_UPDATEIMAGE	32768
#define SHCNE_DRIVEADDGUI	65536
#define SHCNE_RENAMEFOLDER	0x20000
#define SHCNE_FREESPACE	0x40000
#define SHCNE_ASSOCCHANGED	0x8000000
#define SHCNE_DISKEVENTS	0x2381F
#define SHCNE_GLOBALEVENTS	0xC0581E0
#define SHCNE_ALLEVENTS	0x7FFFFFFF
#define SHCNE_INTERRUPT	0x80000000
#define SHCNF_IDLIST	0
#define SHCNF_PATH	1
#define SHCNF_PRINTER	2
#define SHCNF_DWORD	3
#define SHCNF_TYPE	0xFF
#define SHCNF_FLUSH	0x1000
#define SHCNF_FLUSHNOWAIT	0x2000
#define SFGAO_CANCOPY	DROPEFFECT_COPY
#define SFGAO_CANMOVE	DROPEFFECT_MOVE
#define SFGAO_CANLINK	DROPEFFECT_LINK
#define SFGAO_CANRENAME	0x00000010L
#define SFGAO_CANDELETE	0x00000020L
#define SFGAO_HASPROPSHEET	0x00000040L
#define SFGAO_DROPTARGET	0x00000100L
#define SFGAO_CAPABILITYMASK	0x00000177L
#define SFGAO_LINK	0x00010000L
#define SFGAO_SHARE	0x00020000L
#define SFGAO_READONLY	0x00040000L
#define SFGAO_GHOSTED	0x00080000L
#define SFGAO_DISPLAYATTRMASK	0x000F0000L
#define SFGAO_FILESYSANCESTOR	0x10000000L
#define SFGAO_FOLDER	0x20000000L
#define SFGAO_FILESYSTEM	0x40000000L
#define SFGAO_HASSUBFOLDER	0x80000000L
#define SFGAO_CONTENTSMASK	0x80000000L
#define SFGAO_VALIDATE	0x01000000L
#define SFGAO_REMOVABLE	0x02000000L
#define STRRET_WSTR	0
#define STRRET_OFFSET	1
#define STRRET_CSTR	2
#define SHGDFIL_FINDDATA	1
#define SHGDFIL_NETRESOURCE	2
#define SHGDFIL_DESCRIPTIONID	3
#define SHDID_ROOT_REGITEM	1
#define SHDID_FS_FILE	2
#define SHDID_FS_DIRECTORY	3
#define SHDID_FS_OTHER	4
#define SHDID_COMPUTER_DRIVE35	5
#define SHDID_COMPUTER_DRIVE525	6
#define SHDID_COMPUTER_REMOVABLE	7
#define SHDID_COMPUTER_FIXED	8
#define SHDID_COMPUTER_NETDRIVE	9
#define SHDID_COMPUTER_CDROM	10
#define SHDID_COMPUTER_RAMDISK	11
#define SHDID_COMPUTER_OTHER	12
#define SHDID_NET_DOMAIN	13
#define SHDID_NET_SERVER	14
#define SHDID_NET_SHARE	15
#define SHDID_NET_RESTOFNET	16
#define SHDID_NET_OTHER	17
#ifndef REGSTR_PATH_EXPLORER
#define REGSTR_PATH_EXPLORER	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer")
#endif
#define REGSTR_PATH_SPECIAL_FOLDERS	REGSTR_PATH_EXPLORER TEXT("\\Shell Folders")
#define CSIDL_DESKTOP	0
#define CSIDL_INTERNET  1
#define CSIDL_PROGRAMS	2
#define CSIDL_CONTROLS	3
#define CSIDL_PRINTERS	4
#define CSIDL_PERSONAL	5
#define CSIDL_FAVORITES	6
#define CSIDL_STARTUP	7
#define CSIDL_RECENT	8
#define CSIDL_SENDTO	9
#define CSIDL_BITBUCKET	10
#define CSIDL_STARTMENU	11
#define CSIDL_DESKTOPDIRECTORY	16
#define CSIDL_DRIVES	17
#define CSIDL_NETWORK	18
#define CSIDL_NETHOOD	19
#define CSIDL_FONTS	20
#define CSIDL_TEMPLATES	21
#define CSIDL_COMMON_STARTMENU	22
#define CSIDL_COMMON_PROGRAMS	23
#define CSIDL_COMMON_STARTUP	24
#define CSIDL_COMMON_DESKTOPDIRECTORY	25
#define CSIDL_APPDATA   26
#define CSIDL_PRINTHOOD 27
#define CSIDL_ALTSTARTUP    29
#define CSIDL_COMMON_ALTSTARTUP	30
#define CSIDL_COMMON_FAVORITES	31
#define CSIDL_INTERNET_CACHE   32
#define CSIDL_COOKIES	33
#define CSIDL_HISTORY	34
#define CFSTR_SHELLIDLIST	TEXT("Shell IDList Array")
#define CFSTR_SHELLIDLISTOFFSET	TEXT("Shell Object Offsets")
#define CFSTR_NETRESOURCES	TEXT("Net Resource")
#define CFSTR_FILEDESCRIPTOR	TEXT("FileGroupDescriptor")
#define CFSTR_FILECONTENTS	TEXT("FileContents")
#define CFSTR_FILENAME	TEXT("FileName")
#define CFSTR_PRINTERGROUP	TEXT("PrinterFriendlyName")
#define CFSTR_FILENAMEMAP	TEXT("FileNameMap")
#define CFSTR_INDRAGLOOP	TEXT("InShellDragLoop")
#define CFSTR_PASTESUCCEEDED	TEXT("Paste Succeeded")
#define CFSTR_PERFORMEDDROPEFFECT	TEXT("Performed DropEffect")
#define CFSTR_PREFERREDDROPEFFECT	TEXT("Preferred DropEffect")
#define CFSTR_SHELLURL	TEXT("UniformResourceLocator")
#define CMF_NORMAL	0
#define CMF_DEFAULTONLY	1
#define CMF_VERBSONLY	2
#define CMF_EXPLORE	4
#define CMF_RESERVED	0xffff0000
#define GCS_VERBA        0
#define GCS_HELPTEXTA    1
#define GCS_VALIDATEA    2
#define GCS_VERBW        4
#define GCS_HELPTEXTW    5
#define GCS_VALIDATEW    6
#define GCS_UNICODE      4
#ifdef UNICODE
#define GCS_VERB        GCS_VERBW
#define GCS_HELPTEXT    GCS_HELPTEXTW
#define GCS_VALIDATE    GCS_VALIDATEW
#else
#define GCS_VERB        GCS_VERBA
#define GCS_HELPTEXT    GCS_HELPTEXTA
#define GCS_VALIDATE    GCS_VALIDATEA
#endif
#define CMDSTR_NEWFOLDER	TEXT("NewFolder")
#define CMDSTR_VIEWLIST		TEXT("ViewList")
#define CMDSTR_VIEWDETAILS	TEXT("ViewDetails")
#define CMIC_MASK_HOTKEY	SEE_MASK_HOTKEY
#define CMIC_MASK_ICON	SEE_MASK_ICON
#define CMIC_MASK_FLAG_NO_UI	SEE_MASK_FLAG_NO_UI
#define CMIC_MASK_MODAL	0x80000000
#define CMIC_VALID_SEE_FLAGS	SEE_VALID_CMIC_FLAGS
#define GIL_OPENICON	1
#define GIL_FORSHELL	2
#define GIL_SIMULATEDOC	1
#define GIL_PERINSTANCE	2
#define GIL_PERCLASS	4
#define GIL_NOTFILENAME	8
#define GIL_DONTCACHE	16
#define FVSIF_RECT	1
#define FVSIF_PINNED	2
#define FVSIF_NEWFAILED 0x8000000
#define FVSIF_NEWFILE	0x80000000
#define FVSIF_CANVIEWIT 0x40000000
#define CDBOSC_SETFOCUS	0
#define CDBOSC_KILLFOCUS	1
#define CDBOSC_SELCHANGE	2
#define CDBOSC_RENAME	3
#define FCIDM_SHVIEWFIRST	0
#define FCIDM_SHVIEWLAST	0x7fff
#define FCIDM_BROWSERFIRST	0xa000
#define FCIDM_BROWSERLAST	0xbf00
#define FCIDM_GLOBALFIRST	0x8000
#define FCIDM_GLOBALLAST	0x9fff
#define FCIDM_MENU_FILE	FCIDM_GLOBALFIRST
#define FCIDM_MENU_EDIT	(FCIDM_GLOBALFIRST+0x0040)
#define FCIDM_MENU_VIEW	(FCIDM_GLOBALFIRST+0x0080)
#define FCIDM_MENU_VIEW_SEP_OPTIONS	(FCIDM_GLOBALFIRST+0x0081)
#define FCIDM_MENU_TOOLS	(FCIDM_GLOBALFIRST+0x00c0)
#define FCIDM_MENU_TOOLS_SEP_GOTO	(FCIDM_GLOBALFIRST+0x00c1)
#define FCIDM_MENU_HELP	(FCIDM_GLOBALFIRST+0x0100)
#define FCIDM_MENU_FIND	(FCIDM_GLOBALFIRST+0x0140)
#define FCIDM_MENU_EXPLORE	(FCIDM_GLOBALFIRST+0x0150)
#define FCIDM_MENU_FAVORITES	(FCIDM_GLOBALFIRST+0x0170) 
#define FCIDM_TOOLBAR	FCIDM_BROWSERFIRST
#define FCIDM_STATUS	(FCIDM_BROWSERFIRST+1)
#define SBSP_DEFBROWSER	0
#define SBSP_SAMEBROWSER	1
#define SBSP_NEWBROWSER	2
#define SBSP_DEFMODE	0
#define SBSP_OPENMODE	16
#define SBSP_EXPLOREMODE	32
#define SBSP_ABSOLUTE	0
#define SBSP_RELATIVE	0x1000
#define SBSP_PARENT	0x2000
#define SBSP_INITIATEDBYHLINKFRAME	0x80000000
#define SBSP_REDIRECT	0x40000000
#define FCW_STATUS	1
#define FCW_TOOLBAR	2
#define FCW_TREE	3
#define FCT_MERGE	1
#define FCT_CONFIGABLE	2
#define FCT_ADDTOEND	4
#define SVSI_DESELECT	0
#define SVSI_SELECT	1
#define SVSI_EDIT	3
#define SVSI_DESELECTOTHERS	4
#define SVSI_ENSUREVISIBLE	8
#define SVSI_FOCUSED	16
#define SVGIO_BACKGROUND	0
#define SVGIO_SELECTION	1
#define SVGIO_ALLVIEW	2
#define SV2GV_CURRENTVIEW ((UINT)-1)
#define SV2GV_DEFAULTVIEW ((UINT)-2)

typedef struct _IDA {
	UINT cidl;
	UINT aoffset[1];
} CIDA,*LPIDA;
typedef struct _SHITEMID {
	USHORT	cb;
	BYTE	abID[1];
} SHITEMID, * LPSHITEMID;
typedef const SHITEMID *LPCSHITEMID;
typedef struct _ITEMIDLIST {
	SHITEMID mkid;
} ITEMIDLIST,*LPITEMIDLIST;
typedef const ITEMIDLIST *LPCITEMIDLIST;
typedef int (CALLBACK* BFFCALLBACK)(HWND,UINT,LPARAM,LPARAM);
typedef struct _browseinfoA {
	HWND	hwndOwner;
	LPCITEMIDLIST	pidlRoot;
	LPSTR	pszDisplayName;
	LPCSTR	lpszTitle;
	UINT	ulFlags;
	BFFCALLBACK	lpfn;
	LPARAM	lParam;
	int	iImage;
} BROWSEINFOA,*PBROWSEINFOA,*LPBROWSEINFOA;
typedef struct _browseinfoW {
	HWND	hwndOwner;
	LPCITEMIDLIST	pidlRoot;
	LPWSTR	pszDisplayName;
	LPCWSTR	lpszTitle;
	UINT	ulFlags;
	BFFCALLBACK	lpfn;
	LPARAM	lParam;
	int	iImage;
} BROWSEINFOW,*PBROWSEINFOW,*LPBROWSEINFOW;
typedef struct _CMInvokeCommandInfo {
	DWORD cbSize;
	DWORD fMask;
	HWND hwnd;
	LPCSTR lpVerb;
	LPCSTR lpParameters;
	LPCSTR lpDirectory;
	int nShow;
	DWORD dwHotKey;
	HANDLE hIcon;
} CMINVOKECOMMANDINFO,*LPCMINVOKECOMMANDINFO;
typedef struct _DROPFILES {
	DWORD pFiles;
	POINT pt;
	BOOL fNC;
	BOOL fWide;
} DROPFILES,*LPDROPFILES;
typedef enum tagSHGDN {
	SHGDN_NORMAL=0,
	SHGDN_INFOLDER,
	SHGDN_FORPARSING=0x8000
} SHGNO;
typedef enum tagSHCONTF {
	SHCONTF_FOLDERS=32,
	SHCONTF_NONFOLDERS=64,
	SHCONTF_INCLUDEHIDDEN=128
} SHCONTF;
typedef struct _STRRET {
	UINT uType;
	_ANONYMOUS_UNION union {
		LPWSTR pOleStr;
		UINT uOffset;
		char cStr[MAX_PATH];
	} DUMMYUNIONNAME;
} STRRET,*LPSTRRET;
typedef enum {
	FD_CLSID=1,FD_SIZEPOINT=2,FD_ATTRIBUTES=4,FD_CREATETIME=8,FD_ACCESSTIME=16,
	FD_WRITESTIME=32,FD_FILESIZE=64,FD_LINKUI=0x8000
} FD_FLAGS;
typedef struct _FILEDESCRIPTOR {
	DWORD dwFlags;
	CLSID clsid;
	SIZEL sizel;
	POINTL pointl;
	DWORD dwFileAttributes;
	FILETIME ftCreationTime;
	FILETIME ftLastAccessTime;
	FILETIME ftLastWriteTime;
	DWORD nFileSizeHigh;
	DWORD nFileSizeLow;
	CHAR cFileName[MAX_PATH];
} FILEDESCRIPTOR,*LPFILEDESCRIPTOR;
typedef struct _FILEGROUPDESCRIPTOR {
	UINT cItems;
	FILEDESCRIPTOR fgd[1];
} FILEGROUPDESCRIPTOR,*LPFILEGROUPDESCRIPTOR;
typedef enum {
	SLR_NO_UI=1,
	SLR_ANY_MATCH=2,
	SLR_UPDATE=4,
	SLR_NOUPDATE=8,
	SLR_NOSEARCH=16,
	SLR_NOTRACK=32,
	SLR_NOLINKINFO=64,
	SLR_INVOKE_MSI=128
} SLR_FLAGS;
typedef enum {
	SLGP_SHORTPATH=1,
	SLGP_UNCPRIORITY
} SLGP_FLAGS;
typedef PBYTE LPVIEWSETTINGS;
typedef enum {
	FWF_AUTOARRANGE=1,FWF_ABBREVIATEDNAMES=2,FWF_SNAPTOGRID=4,FWF_OWNERDATA=8,
	FWF_BESTFITWINDOW=16,FWF_DESKTOP=32,FWF_SINGLESEL=64,FWF_NOSUBFOLDERS=128,
	FWF_TRANSPARENT=256,FWF_NOCLIENTEDGE=512,FWF_NOSCROLL=0x400,FWF_ALIGNLEFT=0x800,
	FWF_SINGLECLICKACTIVATE=0x8000
} FOLDERFLAGS;
typedef enum {
	FVM_ICON=1,
	FVM_SMALLICON,
	FVM_LIST,
	FVM_DETAILS
} FOLDERVIEWMODE;
typedef struct {
	UINT ViewMode;
	UINT fFlags;
} FOLDERSETTINGS,*LPFOLDERSETTINGS;
typedef const FOLDERSETTINGS *LPCFOLDERSETTINGS;
typedef struct {
    DWORD cbSize;
	HWND hwndOwner;
	int iShow;
	DWORD dwFlags;
	RECT rect;
	LPUNKNOWN punkRel;
	OLECHAR strNewFile[MAX_PATH];
} FVSHOWINFO,*LPFVSHOWINFO;
typedef struct _NRESARRAY {
	UINT cItems;
	NETRESOURCE nr[1];
} NRESARRAY, *LPNRESARRAY;
enum { SBSC_HIDE,SBSC_SHOW,SBSC_TOGGLE,SBSC_QUERY };
enum {
	SBCMDID_ENABLESHOWTREE,SBCMDID_SHOWCONTROL,SBCMDID_CANCELNAVIGATION,
	SBCMDID_MAYSAVECHANGES,SBCMDID_SETHLINKFRAME,SBCMDID_ENABLESTOP,SBCMDID_OPTIONS
};
typedef enum {
	SVUIA_DEACTIVATE,SVUIA_ACTIVATE_NOFOCUS,SVUIA_ACTIVATE_FOCUS,
	SVUIA_INPLACEACTIVATE
} SVUIA_STATUS;

DECLARE_ENUMERATOR_(IEnumIDList,LPITEMIDLIST);
typedef IEnumIDList *LPENUMIDLIST;

#undef INTERFACE
#define INTERFACE IContextMenu
DECLARE_INTERFACE_(IContextMenu,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(QueryContextMenu)(THIS_ HMENU,UINT,UINT,UINT,UINT) PURE;
	STDMETHOD(InvokeCommand)(THIS_ LPCMINVOKECOMMANDINFO) PURE;
	STDMETHOD(GetCommandString)(THIS_ UINT,UINT,PUINT,LPSTR,UINT) PURE;
};
typedef IContextMenu *LPCONTEXTMENU;

#undef INTERFACE
#define INTERFACE IContextMenu2
DECLARE_INTERFACE_(IContextMenu2,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(QueryContextMenu)(THIS_ HMENU,UINT,UINT,UINT,UINT) PURE;
	STDMETHOD(HandleMenuMsg)(THIS_ UINT,WPARAM,LPARAM) PURE;
	STDMETHOD(InvokeCommand)(THIS_ LPCMINVOKECOMMANDINFO) PURE;
    STDMETHOD(GetCommandString)(THIS_ UINT,UINT,PUINT,LPSTR,UINT) PURE;
};
typedef IContextMenu2 *LPCONTEXTMENU2;

#undef INTERFACE
#define INTERFACE IShellExtInit
DECLARE_INTERFACE_(IShellExtInit, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(Initialize)(THIS_ LPCITEMIDLIST,LPDATAOBJECT,HKEY) PURE;
};
typedef IShellExtInit *LPSHELLEXTINIT;

#undef INTERFACE
#define INTERFACE IShellPropSheetExt
DECLARE_INTERFACE_(IShellPropSheetExt, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
    STDMETHOD(AddPages)(THIS_ LPFNADDPROPSHEETPAGE,LPARAM) PURE;
    STDMETHOD(ReplacePage)(THIS_ UINT,LPFNADDPROPSHEETPAGE,LPARAM) PURE;
};
typedef IShellPropSheetExt *LPSHELLPROPSHEETEXT;

#undef INTERFACE
#define INTERFACE IExtractIcon
DECLARE_INTERFACE_(IExtractIcon, IUnknown)  /* exic */
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
    STDMETHOD(GetIconLocation)(THIS_ UINT,LPSTR,UINT,int*,PUINT) PURE;
	STDMETHOD(Extract)(THIS_ LPCSTR,UINT,HICON*,HICON*,UINT) PURE;
};
typedef IExtractIcon *LPEXTRACTICON;

#undef INTERFACE
#define INTERFACE IShellLinkA
DECLARE_INTERFACE_(IShellLinkA, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetPath)(THIS_ LPSTR,int,WIN32_FIND_DATAA*,DWORD) PURE;
	STDMETHOD(GetIDList)(THIS_ LPITEMIDLIST*) PURE;
	STDMETHOD(SetIDList)(THIS_ LPCITEMIDLIST) PURE;
	STDMETHOD(GetDescription)(THIS_ LPSTR,int) PURE;
	STDMETHOD(SetDescription)(THIS_ LPCSTR) PURE;
	STDMETHOD(GetWorkingDirectory)(THIS_ LPSTR,int) PURE;
	STDMETHOD(SetWorkingDirectory)(THIS_ LPCSTR) PURE;
	STDMETHOD(GetArguments)(THIS_ LPSTR,int) PURE;
	STDMETHOD(SetArguments)(THIS_ LPCSTR) PURE;
	STDMETHOD(GetHotkey)(THIS_ PWORD) PURE;
	STDMETHOD(SetHotkey)(THIS_ WORD) PURE;
	STDMETHOD(GetShowCmd)(THIS_ int*) PURE;
	STDMETHOD(SetShowCmd)(THIS_ int) PURE;
	STDMETHOD(GetIconLocation)(THIS_ LPSTR,int,int*) PURE;
	STDMETHOD(SetIconLocation)(THIS_ LPCSTR,int) PURE;
	STDMETHOD(SetRelativePath)(THIS_ LPCSTR ,DWORD) PURE;
	STDMETHOD(Resolve)(THIS_ HWND,DWORD) PURE;
	STDMETHOD(SetPath)(THIS_ LPCSTR) PURE;
};
#undef INTERFACE
#define INTERFACE IShellLinkW
DECLARE_INTERFACE_(IShellLinkW, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetPath)(THIS_ LPSTR,int,WIN32_FIND_DATAW*,DWORD) PURE;
	STDMETHOD(GetIDList)(THIS_ LPITEMIDLIST*) PURE;
	STDMETHOD(SetIDList)(THIS_ LPCITEMIDLIST) PURE;
	STDMETHOD(GetDescription)(THIS_ LPWSTR,int) PURE;
	STDMETHOD(SetDescription)(THIS_ LPCWSTR) PURE;
	STDMETHOD(GetWorkingDirectory)(THIS_ LPWSTR,int) PURE;
	STDMETHOD(SetWorkingDirectory)(THIS_ LPCWSTR) PURE;
	STDMETHOD(GetArguments)(THIS_ LPWSTR,int) PURE;
	STDMETHOD(SetArguments)(THIS_ LPCWSTR) PURE;
	STDMETHOD(GetHotkey)(THIS_ PWORD) PURE;
	STDMETHOD(SetHotkey)(THIS_ WORD) PURE;
	STDMETHOD(GetShowCmd)(THIS_ int*) PURE;
	STDMETHOD(SetShowCmd)(THIS_ int) PURE;
	STDMETHOD(GetIconLocation)(THIS_ LPWSTR,int,int*) PURE;
	STDMETHOD(SetIconLocation)(THIS_ LPCWSTR,int) PURE;
	STDMETHOD(SetRelativePath)(THIS_ LPCWSTR ,DWORD) PURE;
	STDMETHOD(Resolve)(THIS_ HWND,DWORD) PURE;
	STDMETHOD(SetPath)(THIS_ LPCWSTR) PURE;
};

#undef INTERFACE
#define INTERFACE IShellFolder
DECLARE_INTERFACE_(IShellFolder, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(ParseDisplayName)(THIS_ HWND,LPBC,LPOLESTR,PULONG,LPITEMIDLIST*,PULONG) PURE;
	STDMETHOD(EnumObjects)(THIS_ HWND,DWORD,LPENUMIDLIST*) PURE;
	STDMETHOD(BindToObject)(THIS_ LPCITEMIDLIST,LPBC,REFIID,PVOID*) PURE;
	STDMETHOD(BindToStorage)(THIS_ LPCITEMIDLIST,LPBC,REFIID,PVOID*) PURE;
	STDMETHOD(CompareIDs)(THIS_ LPARAM,LPCITEMIDLIST,LPCITEMIDLIST) PURE;
	STDMETHOD(CreateViewObject)(THIS_ HWND,REFIID,PVOID*) PURE;
	STDMETHOD(GetAttributesOf)(THIS_ UINT,LPCITEMIDLIST*,PULONG) PURE;
	STDMETHOD(GetUIObjectOf)(THIS_ HWND,UINT,LPCITEMIDLIST*,REFIID,PUINT,PVOID*) PURE;
	STDMETHOD(GetDisplayNameOf)(THIS_ LPCITEMIDLIST,DWORD,LPSTRRET) PURE;
	STDMETHOD(SetNameOf)(THIS_ HWND,LPCITEMIDLIST,LPCOLESTR,DWORD,LPITEMIDLIST*) PURE;
};
typedef IShellFolder *LPSHELLFOLDER;

#undef INTERFACE
#define INTERFACE ICopyHook
DECLARE_INTERFACE_(ICopyHook, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD_(UINT,CopyCallback)(THIS_ HWND,UINT,UINT,LPCSTR,DWORD,LPCSTR,DWORD) PURE;
};
typedef ICopyHook *LPCOPYHOOK;

#undef INTERFACE
#define INTERFACE IFileViewerSite
DECLARE_INTERFACE(IFileViewerSite)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(SetPinnedWindow)(THIS_ HWND) PURE;
	STDMETHOD(GetPinnedWindow)(THIS_ HWND*) PURE;
};
typedef IFileViewerSite *LPFILEVIEWERSITE;

#undef INTERFACE
#define INTERFACE IFileViewer
DECLARE_INTERFACE(IFileViewer)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(ShowInitialize)(THIS_ LPFILEVIEWERSITE) PURE;
	STDMETHOD(Show)(THIS_ LPFVSHOWINFO) PURE;
	STDMETHOD(PrintTo)(THIS_ LPSTR,BOOL) PURE;
};
typedef IFileViewer *LPFILEVIEWER;

#undef INTERFACE
#define INTERFACE ICommDlgBrowser
DECLARE_INTERFACE_(ICommDlgBrowser,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(OnDefaultCommand)(THIS) PURE;
	STDMETHOD(OnStateChange)(THIS_ ULONG) PURE;
	STDMETHOD(IncludeObject)(THIS_ LPCITEMIDLIST) PURE;
};
typedef ICommDlgBrowser *LPCOMMDLGBROWSER;

#undef INTERFACE
#define INTERFACE IPersistFolder
DECLARE_INTERFACE_(IPersistFolder,IPersist)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetClassID)(THIS_ CLSID) PURE;
	STDMETHOD(Initialize)(THIS_ LPCITEMIDLIST) PURE;
};
typedef IPersistFolder *LPPERSISTFOLDER;

typedef interface IShellBrowser *LPSHELLBROWSER;
typedef interface IShellView *LPSHELLVIEW;

#undef INTERFACE
#define INTERFACE IShellBrowser
DECLARE_INTERFACE_(IShellBrowser,IOleWindow)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetWindow)(THIS_ HWND*) PURE;
	STDMETHOD(ContextSensitiveHelp)(THIS_ BOOL) PURE;
	STDMETHOD(InsertMenusSB)(THIS_ HMENU,LPOLEMENUGROUPWIDTHS) PURE;
	STDMETHOD(SetMenuSB)(THIS_ HMENU,HOLEMENU,HWND) PURE;
	STDMETHOD(RemoveMenusSB)(THIS_ HMENU) PURE;
	STDMETHOD(SetStatusTextSB) (THIS_ LPCOLESTR) PURE;
	STDMETHOD(EnableModelessSB) (THIS_ BOOL	) PURE;
	STDMETHOD(TranslateAcceleratorSB) (THIS_ LPMSG,WORD) PURE;
	STDMETHOD(BrowseObject)(THIS_ LPCITEMIDLIST,UINT) PURE;
	STDMETHOD(GetViewStateStream)(THIS_ DWORD,LPSTREAM*) PURE;
	STDMETHOD(GetControlWindow)(THIS_ UINT,HWND*) PURE;
	STDMETHOD(SendControlMsg)(THIS_ UINT,UINT,WPARAM,LPARAM,LRESULT*) PURE;
	STDMETHOD(QueryActiveShellView)(THIS_ LPSHELLVIEW*) PURE;
	STDMETHOD(OnViewWindowActive)(THIS_ LPSHELLVIEW) PURE;
	STDMETHOD(SetToolbarItems)(THIS_ LPTBBUTTON,UINT,UINT) PURE;
};

#undef INTERFACE
#define INTERFACE IShellView
DECLARE_INTERFACE_(IShellView,IOleWindow)
{

	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetWindow)(THIS_ HWND*) PURE;
	STDMETHOD(ContextSensitiveHelp)(THIS_ BOOL) PURE;
	STDMETHOD(TranslateAccelerator) (THIS_ LPMSG) PURE;
#ifdef _FIX_ENABLEMODELESS_CONFLICT
	STDMETHOD(EnableModelessSV)(THIS_ BOOL) PURE;
#else
	STDMETHOD(EnableModeless)(THIS_ BOOL) PURE;
#endif
	STDMETHOD(UIActivate)(THIS_ UINT) PURE;
	STDMETHOD(Refresh) (THIS) PURE;
	STDMETHOD(CreateViewWindow)(THIS_ IShellView*,LPCFOLDERSETTINGS,LPSHELLBROWSER,RECT*,HWND*) PURE;
	STDMETHOD(DestroyViewWindow)(THIS) PURE;
	STDMETHOD(GetCurrentInfo)(THIS_ LPFOLDERSETTINGS) PURE;
	STDMETHOD(AddPropertySheetPages)(THIS_ DWORD,LPFNADDPROPSHEETPAGE,LPARAM) PURE;
	STDMETHOD(SaveViewState)(THIS) PURE;
	STDMETHOD(SelectItem)(THIS_ LPCITEMIDLIST,UINT) PURE;
	STDMETHOD(GetItemObject)(THIS_ UINT,REFIID,PVOID*) PURE;
};
typedef GUID SHELLVIEWID;
typedef struct _SV2CVW2_PARAMS {
	DWORD cbSize;
	IShellView *psvPrev;
	FOLDERSETTINGS const *pfs;
	IShellBrowser *psbOwner;
	RECT *prcView;
	SHELLVIEWID const *pvid;
	HWND hwndView;
} SV2CVW2_PARAMS,*LPSV2CVW2_PARAMS;
#undef INTERFACE
#define INTERFACE IShellView2
DECLARE_INTERFACE_(IShellView2,IShellView)
{

	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetWindow)(THIS_ HWND*) PURE;
	STDMETHOD(ContextSensitiveHelp)(THIS_ BOOL) PURE;
	STDMETHOD(TranslateAccelerator) (THIS_ LPMSG) PURE;
#ifdef _FIX_ENABLEMODELESS_CONFLICT
	STDMETHOD(EnableModelessSV)(THIS_ BOOL) PURE;
#else
	STDMETHOD(EnableModeless)(THIS_ BOOL) PURE;
#endif
	STDMETHOD(UIActivate)(THIS_ UINT) PURE;
	STDMETHOD(Refresh) (THIS) PURE;
	STDMETHOD(CreateViewWindow)(THIS_ IShellView*,LPCFOLDERSETTINGS,LPSHELLBROWSER,RECT*,HWND*) PURE;
	STDMETHOD(DestroyViewWindow)(THIS) PURE;
	STDMETHOD(GetCurrentInfo)(THIS_ LPFOLDERSETTINGS) PURE;
	STDMETHOD(AddPropertySheetPages)(THIS_ DWORD,LPFNADDPROPSHEETPAGE,LPARAM) PURE;
	STDMETHOD(SaveViewState)(THIS) PURE;
	STDMETHOD(SelectItem)(THIS_ LPCITEMIDLIST,UINT) PURE;
	STDMETHOD(GetItemObject)(THIS_ UINT,REFIID,PVOID*) PURE;
	STDMETHOD(GetView)(THIS_ SHELLVIEWID*,ULONG) PURE;
	STDMETHOD(CreateViewWindow2)(THIS_ LPSV2CVW2_PARAMS) PURE;
};

#undef INTERFACE
#define INTERFACE IShellExecuteHookA
DECLARE_INTERFACE_(IShellExecuteHookA,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(Execute)(THIS_ LPSHELLEXECUTEINFOA) PURE;
};
#undef INTERFACE
#define INTERFACE IShellExecuteHookW
DECLARE_INTERFACE_(IShellExecuteHookW,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(Execute)(THIS_ LPSHELLEXECUTEINFOW) PURE;
};

#undef INTERFACE
#define INTERFACE IShellIcon
DECLARE_INTERFACE_(IShellIcon,IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetIconOf)(THIS_ LPCITEMIDLIST,UINT,PINT) PURE;
};
typedef IShellIcon *LPSHELLICON;

void WINAPI SHAddToRecentDocs(UINT,PCVOID);
LPITEMIDLIST WINAPI SHBrowseForFolderA(PBROWSEINFOA);
LPITEMIDLIST WINAPI SHBrowseForFolderW(PBROWSEINFOW);
void WINAPI SHChangeNotify(LONG,UINT,PCVOID,PCVOID);
HRESULT WINAPI SHGetDataFromIDListA(LPSHELLFOLDER,LPCITEMIDLIST,int,PVOID,int);
HRESULT WINAPI SHGetDataFromIDListW(LPSHELLFOLDER,LPCITEMIDLIST,int,PVOID,int);
HRESULT WINAPI SHGetDesktopFolder(LPSHELLFOLDER*);
HRESULT WINAPI SHGetInstanceExplorer(LPUNKNOWN);
HRESULT WINAPI SHGetMalloc(LPMALLOC*);
BOOL WINAPI SHGetPathFromIDListA(LPCITEMIDLIST,LPSTR);
BOOL WINAPI SHGetPathFromIDListW(LPCITEMIDLIST,LPWSTR);
HRESULT WINAPI SHGetSpecialFolderLocation(HWND,int,LPITEMIDLIST*);
HRESULT WINAPI SHLoadInProc(REFCLSID);
/* FIXME/TODO: Only valid for _WIN32_IE >= 400? */
BOOL WINAPI SHGetSpecialFolderPathA(HWND,LPSTR,int,BOOL);
BOOL WINAPI SHGetSpecialFolderPathW(HWND,LPSTR,int,BOOL);

#ifdef UNICODE
typedef IShellExecuteHookW IShellExecuteHook;
typedef IShellLinkW IShellLink;
typedef BROWSEINFOW BROWSEINFO,*PBROWSEINFO,*LPBROWSEINFO;
#define SHBrowseForFolder SHBrowseForFolderW
#define SHGetDataFromIDList SHGetDataFromIDListW
#define SHGetPathFromIDList SHGetPathFromIDListW
/* FIXME/TODO: Only valid for _WIN32_IE >= 400? */
#define SHGetSpecialFolderPath SHGetSpecialFolderPathW
#else
typedef IShellExecuteHookA IShellExecuteHook;
typedef IShellLinkA IShellLink;
typedef BROWSEINFOA BROWSEINFO,*PBROWSEINFO,*LPBROWSEINFO;
#define SHBrowseForFolder SHBrowseForFolderA
#define SHGetDataFromIDList SHGetDataFromIDListA
#define SHGetPathFromIDList SHGetPathFromIDListA
/* FIXME/TODO: Only valid for _WIN32_IE >= 400? */
#define SHGetSpecialFolderPath SHGetSpecialFolderPathA
#endif

#pragma pack(pop)
#ifdef __cplusplus
}
#endif


#endif /* _SHLOBJ_H */
