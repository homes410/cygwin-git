#ifndef _OLEDLG_H
#define _OLEDLG_H
#ifdef __cplusplus
extern "C" {
#endif
#include <windows.h>
#include <shellapi.h>
#include <commdlg.h>
#include <ole2.h>
#include <string.h>
/* #include <tchar.h> */
#include <dlgs.h>
#include <prsht.h>
#define PS_MAXLINKTYPES 8
#define OLESTDDELIM _TEXT("\\")
#define SZOLEUI_MSG_HELP _TEXT("OLEUI_MSG_HELP")
#define SZOLEUI_MSG_ENDDIALOG _TEXT("OLEUI_MSG_ENDDIALOG")
#define SZOLEUI_MSG_BROWSE _TEXT("OLEUI_MSG_BROWSE")
#define SZOLEUI_MSG_CHANGEICON _TEXT("OLEUI_MSG_CHANGEICON")
#define SZOLEUI_MSG_CLOSEBUSYDIALOG _TEXT("OLEUI_MSG_CLOSEBUSYDIALOG")
#define SZOLEUI_MSG_CONVERT _TEXT("OLEUI_MSG_CONVERT")
#define SZOLEUI_MSG_CHANGESOURCE _TEXT("OLEUI_MSG_CHANGESOURCE")
#define SZOLEUI_MSG_ADDCONTROL _TEXT("OLEUI_MSG_ADDCONTROL")
#define SZOLEUI_MSG_BROWSE_OFN _TEXT("OLEUI_MSG_BROWSE_OFN")
#define PROP_HWND_CHGICONDLG _TEXT("HWND_CIDLG")
#define IDC_OLEUIHELP 99
#define IDC_IO_CREATENEW 2100
#define IDC_IO_CREATEFROMFILE 2101
#define IDC_IO_LINKFILE 2102
#define IDC_IO_OBJECTTYPELIST 2103
#define IDC_IO_DISPLAYASICON 2104
#define IDC_IO_CHANGEICON 2105
#define IDC_IO_FILE 2106
#define IDC_IO_FILEDISPLAY 2107
#define IDC_IO_RESULTIMAGE 2108
#define IDC_IO_RESULTTEXT 2109
#define IDC_IO_ICONDISPLAY 2110
#define IDC_IO_OBJECTTYPETEXT 2111 
#define IDC_IO_FILETEXT 2112 
#define IDC_IO_FILETYPE 2113
#define IDC_IO_INSERTCONTROL 2114
#define IDC_IO_ADDCONTROL 2115
#define IDC_IO_CONTROLTYPELIST 2116
#define IDC_PS_PASTE 500
#define IDC_PS_PASTELINK 501
#define IDC_PS_SOURCETEXT 502
#define IDC_PS_PASTELIST 503 
#define IDC_PS_PASTELINKLIST 504 
#define IDC_PS_DISPLAYLIST 505
#define IDC_PS_DISPLAYASICON 506
#define IDC_PS_ICONDISPLAY 507
#define IDC_PS_CHANGEICON 508
#define IDC_PS_RESULTIMAGE 509
#define IDC_PS_RESULTTEXT 510
#define IDC_CI_GROUP 120 
#define IDC_CI_CURRENT 121
#define IDC_CI_CURRENTICON 122
#define IDC_CI_DEFAULT 123
#define IDC_CI_DEFAULTICON 124
#define IDC_CI_FROMFILE 125
#define IDC_CI_FROMFILEEDIT 126
#define IDC_CI_ICONLIST 127
#define IDC_CI_LABEL 128 
#define IDC_CI_LABELEDIT 129
#define IDC_CI_BROWSE 130
#define IDC_CI_ICONDISPLAY 131
#define IDC_CV_OBJECTTYPE 150
#define IDC_CV_DISPLAYASICON 152
#define IDC_CV_CHANGEICON 153
#define IDC_CV_ACTIVATELIST 154
#define IDC_CV_CONVERTTO 155
#define IDC_CV_ACTIVATEAS 156
#define IDC_CV_RESULTTEXT 157
#define IDC_CV_CONVERTLIST 158
#define IDC_CV_ICONDISPLAY 165
#define IDC_EL_CHANGESOURCE 201
#define IDC_EL_AUTOMATIC 202
#define IDC_EL_CANCELLINK 209
#define IDC_EL_UPDATENOW 210
#define IDC_EL_OPENSOURCE 211
#define IDC_EL_MANUAL 212
#define IDC_EL_LINKSOURCE 216
#define IDC_EL_LINKTYPE 217
#define IDC_EL_LINKSLISTBOX 206
#define IDC_EL_COL1 220 
#define IDC_EL_COL2 221 
#define IDC_EL_COL3 222 
#define IDC_BZ_RETRY 600
#define IDC_BZ_ICON 601
#define IDC_BZ_MESSAGE1 602 
#define IDC_BZ_SWITCHTO 604
#define IDC_UL_METER 1029 
#define IDC_UL_STOP 1030 
#define IDC_UL_PERCENT 1031 
#define IDC_UL_PROGRESS 1032 
#define IDC_PU_LINKS 900 
#define IDC_PU_TEXT 901 
#define IDC_PU_CONVERT 902 
#define IDC_PU_ICON 908 
#define IDC_GP_OBJECTNAME 1009
#define IDC_GP_OBJECTTYPE 1010
#define IDC_GP_OBJECTSIZE 1011
#define IDC_GP_CONVERT 1013
#define IDC_GP_OBJECTICON 1014 
#define IDC_GP_OBJECTLOCATION 1022
#define IDC_VP_PERCENT 1000
#define IDC_VP_CHANGEICON 1001
#define IDC_VP_EDITABLE 1002
#define IDC_VP_ASICON 1003
#define IDC_VP_RELATIVE 1005
#define IDC_VP_SPIN 1006
#define IDC_VP_SCALETXT 1034
#define IDC_VP_ICONDISPLAY 1021
#define IDC_VP_RESULTIMAGE 1033
#define IDC_LP_OPENSOURCE 1006
#define IDC_LP_UPDATENOW 1007
#define IDC_LP_BREAKLINK 1008
#define IDC_LP_LINKSOURCE 1012
#define IDC_LP_CHANGESOURCE 1015
#define IDC_LP_AUTOMATIC 1016
#define IDC_LP_MANUAL 1017
#define IDC_LP_DATE 1018
#define IDC_LP_TIME 1019
#define IDD_INSERTOBJECT 1000
#define IDD_CHANGEICON 1001
#define IDD_CONVERT 1002
#define IDD_PASTESPECIAL 1003
#define IDD_EDITLINKS 1004
#define IDD_BUSY 1006
#define IDD_UPDATELINKS 1007
#define IDD_CHANGESOURCE 1009
#define IDD_INSERTFILEBROWSE 1010
#define IDD_CHANGEICONBROWSE 1011
#define IDD_CONVERTONLY 1012
#define IDD_CHANGESOURCE4 1013
#define IDD_GNRLPROPS 1100
#define IDD_VIEWPROPS 1101
#define IDD_LINKPROPS 1102
#define IDD_CANNOTUPDATELINK 1008
#define IDD_LINKSOURCEUNAVAILABLE 1020
#define IDD_SERVERNOTFOUND 1023
#define IDD_OUTOFMEMORY 1024
#define IDD_SERVERNOTREGW 1021
#define IDD_LINKTYPECHANGEDW 1022
#define IDD_SERVERNOTREGA 1025
#define IDD_LINKTYPECHANGEDA 1026
#define ID_BROWSE_CHANGEICON 1
#define ID_BROWSE_INSERTFILE 2
#define ID_BROWSE_ADDCONTROL 3
#define ID_BROWSE_CHANGESOURCE 4
#define OLEUI_FALSE 0
#define OLEUI_SUCCESS 1 
#define OLEUI_OK 1 
#define OLEUI_CANCEL 2 
#define OLEUI_ERR_STANDARDMIN 100
#define OLEUI_ERR_STRUCTURENULL 101 
#define OLEUI_ERR_STRUCTUREINVALID 102
#define OLEUI_ERR_CBSTRUCTINCORRECT 103
#define OLEUI_ERR_HWNDOWNERINVALID 104
#define OLEUI_ERR_LPSZCAPTIONINVALID 105
#define OLEUI_ERR_LPFNHOOKINVALID 106
#define OLEUI_ERR_HINSTANCEINVALID 107
#define OLEUI_ERR_LPSZTEMPLATEINVALID 108
#define OLEUI_ERR_HRESOURCEINVALID 109
#define OLEUI_ERR_FINDTEMPLATEFAILURE 110 
#define OLEUI_ERR_LOADTEMPLATEFAILURE 111
#define OLEUI_ERR_DIALOGFAILURE 112
#define OLEUI_ERR_LOCALMEMALLOC 113
#define OLEUI_ERR_GLOBALMEMALLOC 114
#define OLEUI_ERR_LOADSTRING 115
#define OLEUI_ERR_OLEMEMALLOC 116
#define OLEUI_ERR_STANDARDMAX 116 
#define OPF_OBJECTISLINK 1
#define OPF_NOFILLDEFAULT 2
#define OPF_SHOWHELP 4
#define OPF_DISABLECONVERT 8
#define OLEUI_OPERR_SUBPROPNULL OLEUI_ERR_STANDARDMAX
#define OLEUI_OPERR_SUBPROPINVALID (OLEUI_ERR_STANDARDMAX+1)
#define OLEUI_OPERR_PROPSHEETNULL (OLEUI_ERR_STANDARDMAX+2)
#define OLEUI_OPERR_PROPSHEETINVALID (OLEUI_ERR_STANDARDMAX+3)
#define OLEUI_OPERR_SUPPROP (OLEUI_ERR_STANDARDMAX+4)
#define OLEUI_OPERR_PROPSINVALID (OLEUI_ERR_STANDARDMAX+5)
#define OLEUI_OPERR_PAGESINCORRECT (OLEUI_ERR_STANDARDMAX+6)
#define OLEUI_OPERR_INVALIDPAGES (OLEUI_ERR_STANDARDMAX+7)
#define OLEUI_OPERR_NOTSUPPORTED (OLEUI_ERR_STANDARDMAX+8)
#define OLEUI_OPERR_DLGPROCNOTNULL (OLEUI_ERR_STANDARDMAX+9)
#define OLEUI_OPERR_LPARAMNOTZERO (OLEUI_ERR_STANDARDMAX+10)
#define OLEUI_GPERR_STRINGINVALID (OLEUI_ERR_STANDARDMAX+11)
#define OLEUI_GPERR_CLASSIDINVALID (OLEUI_ERR_STANDARDMAX+12)
#define OLEUI_GPERR_LPCLSIDEXCLUDEINVALID (OLEUI_ERR_STANDARDMAX+13)
#define OLEUI_GPERR_CBFORMATINVALID (OLEUI_ERR_STANDARDMAX+14)
#define OLEUI_VPERR_METAPICTINVALID (OLEUI_ERR_STANDARDMAX+15)
#define OLEUI_VPERR_DVASPECTINVALID (OLEUI_ERR_STANDARDMAX+16)
#define OLEUI_LPERR_LINKCNTRNULL (OLEUI_ERR_STANDARDMAX+17)
#define OLEUI_LPERR_LINKCNTRINVALID (OLEUI_ERR_STANDARDMAX+18)
#define OLEUI_OPERR_PROPERTYSHEET (OLEUI_ERR_STANDARDMAX+19)
#define OLEUI_OPERR_OBJINFOINVALID (OLEUI_ERR_STANDARDMAX+20)
#define OLEUI_OPERR_LINKINFOINVALID (OLEUI_ERR_STANDARDMAX+21)
#define OLEUI_QUERY_GETCLASSID 65280
#define OLEUI_QUERY_LINKBROKEN 65281 
#define IOF_SHOWHELP 1
#define IOF_SELECTCREATENEW 2
#define IOF_SELECTCREATEFROMFILE 4
#define IOF_CHECKLINK 8
#define IOF_CHECKDISPLAYASICON 16
#define IOF_CREATENEWOBJECT 32
#define IOF_CREATEFILEOBJECT 64
#define IOF_CREATELINKOBJECT 128
#define IOF_DISABLELINK 256
#define IOF_VERIFYSERVERSEXIST 512
#define IOF_DISABLEDISPLAYASICON 1024
#define IOF_HIDECHANGEICON 2048
#define IOF_SHOWINSERTCONTROL 4096
#define IOF_SELECTCREATECONTROL 8192
#define OLEUI_IOERR_LPSZFILEINVALID OLEUI_ERR_STANDARDMAX
#define OLEUI_IOERR_LPSZLABELINVALID (OLEUI_ERR_STANDARDMAX+1)
#define OLEUI_IOERR_HICONINVALID (OLEUI_ERR_STANDARDMAX+2)
#define OLEUI_IOERR_LPFORMATETCINVALID (OLEUI_ERR_STANDARDMAX+3)
#define OLEUI_IOERR_PPVOBJINVALID (OLEUI_ERR_STANDARDMAX+4)
#define OLEUI_IOERR_LPIOLECLIENTSITEINVALID (OLEUI_ERR_STANDARDMAX+5)
#define OLEUI_IOERR_LPISTORAGEINVALID (OLEUI_ERR_STANDARDMAX+6)
#define OLEUI_IOERR_SCODEHASERROR (OLEUI_ERR_STANDARDMAX+7)
#define OLEUI_IOERR_LPCLSIDEXCLUDEINVALID (OLEUI_ERR_STANDARDMAX+8)
#define OLEUI_IOERR_CCHFILEINVALID (OLEUI_ERR_STANDARDMAX+9)
#define PSF_SHOWHELP 1
#define PSF_SELECTPASTE 2
#define PSF_SELECTPASTELINK 4
#define PSF_CHECKDISPLAYASICON 8
#define PSF_DISABLEDISPLAYASICON 16
#define PSF_HIDECHANGEICON 32
#define PSF_STAYONCLIPBOARDCHANGE 64
#define PSF_NOREFRESHDATAOBJECT 128
#define OLEUI_IOERR_SRCDATAOBJECTINVALID OLEUI_ERR_STANDARDMAX
#define OLEUI_IOERR_ARRPASTEENTRIESINVALID (OLEUI_ERR_STANDARDMAX+1)
#define OLEUI_IOERR_ARRLINKTYPESINVALID (OLEUI_ERR_STANDARDMAX+2)
#define OLEUI_PSERR_CLIPBOARDCHANGED (OLEUI_ERR_STANDARDMAX+3)
#define OLEUI_PSERR_GETCLIPBOARDFAILED (OLEUI_ERR_STANDARDMAX+4)
#define OLEUI_ELERR_LINKCNTRNULL OLEUI_ERR_STANDARDMAX
#define OLEUI_ELERR_LINKCNTRINVALID (OLEUI_ERR_STANDARDMAX+1)
#define ELF_SHOWHELP 1
#define ELF_DISABLEUPDATENOW 2
#define ELF_DISABLEOPENSOURCE 4
#define ELF_DISABLECHANGESOURCE 8
#define ELF_DISABLECANCELLINK 16
#define CIF_SHOWHELP 1
#define CIF_SELECTCURRENT 2
#define CIF_SELECTDEFAULT 4
#define CIF_SELECTFROMFILE 8
#define CIF_USEICONEXE 16
#define OLEUI_CIERR_MUSTHAVECLSID OLEUI_ERR_STANDARDMAX
#define OLEUI_CIERR_MUSTHAVECURRENTMETAFILE (OLEUI_ERR_STANDARDMAX+1)
#define OLEUI_CIERR_SZICONEXEINVALID (OLEUI_ERR_STANDARDMAX+2)
#define CF_SHOWHELPBUTTON 1
#define CF_SETCONVERTDEFAULT 2
#define CF_SETACTIVATEDEFAULT 4
#define CF_SELECTCONVERTTO 8
#define CF_SELECTACTIVATEAS 16
#define CF_DISABLEDISPLAYASICON 32
#define CF_DISABLEACTIVATEAS 64
#define CF_HIDECHANGEICON 128
#define CF_CONVERTONLY 256
#define OLEUI_CTERR_CLASSIDINVALID (OLEUI_ERR_STANDARDMAX+1)
#define OLEUI_CTERR_DVASPECTINVALID (OLEUI_ERR_STANDARDMAX+2)
#define OLEUI_CTERR_CBFORMATINVALID (OLEUI_ERR_STANDARDMAX+3)
#define OLEUI_CTERR_HMETAPICTINVALID (OLEUI_ERR_STANDARDMAX+4)
#define OLEUI_CTERR_STRINGINVALID (OLEUI_ERR_STANDARDMAX+5)
#define BZ_DISABLECANCELBUTTON 1
#define BZ_DISABLESWITCHTOBUTTON 2
#define BZ_DISABLERETRYBUTTON 4
#define BZ_NOTRESPONDINGDIALOG 8
#define OLEUI_BZERR_HTASKINVALID OLEUI_ERR_STANDARDMAX
#define OLEUI_BZ_SWITCHTOSELECTED (OLEUI_ERR_STANDARDMAX+1)
#define OLEUI_BZ_RETRYSELECTED (OLEUI_ERR_STANDARDMAX+2)
#define OLEUI_BZ_CALLUNBLOCKED (OLEUI_ERR_STANDARDMAX+3)
#define CSF_SHOWHELP 1
#define CSF_VALIDSOURCE 2
#define CSF_ONLYGETSOURCE 4
#define CSF_EXPLORER 8
#define OLEUI_CSERR_LINKCNTRNULL OLEUI_ERR_STANDARDMAX
#define OLEUI_CSERR_LINKCNTRINVALID (OLEUI_ERR_STANDARDMAX+1)
#define OLEUI_CSERR_FROMNOTNULL (OLEUI_ERR_STANDARDMAX+2)
#define OLEUI_CSERR_TONOTNULL (OLEUI_ERR_STANDARDMAX+3)
#define OLEUI_CSERR_SOURCENULL (OLEUI_ERR_STANDARDMAX+4)
#define OLEUI_CSERR_SOURCEINVALID (OLEUI_ERR_STANDARDMAX+5)
#define OLEUI_CSERR_SOURCEPARSERROR (OLEUI_ERR_STANDARDMAX+6)
#define OLEUI_CSERR_SOURCEPARSEERROR (OLEUI_ERR_STANDARDMAX+7)
#define VPF_SELECTRELATIVE 1
#define VPF_DISABLERELATIVE 2
#define VPF_DISABLESCALE 4

#ifndef RC_INVOKED
#pragma pack(push, 8)
typedef UINT (CALLBACK *LPFNOLEUIHOOK)(HWND, UINT, WPARAM, LPARAM);
typedef struct tagOLEUIINSERTOBJECTW {
	DWORD cbStruct;
	DWORD dwFlags;
	HWND hWndOwner;
	LPCWSTR lpszCaption;
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	HINSTANCE hInstance;
	LPCWSTR lpszTemplate;
	HRSRC hResource;
	CLSID clsid;
	LPWSTR lpszFile;
	UINT cchFile;
	UINT cClsidExclude;
	LPCLSID lpClsidExclude;
	IID iid;
	DWORD oleRender;
	LPFORMATETC lpFormatEtc;
	LPOLECLIENTSITE lpIOleClientSite;
	LPSTORAGE lpIStorage;
	PVOID *ppvObj;
	SCODE sc;
	HGLOBAL hMetaPict;
} OLEUIINSERTOBJECTW,*POLEUIINSERTOBJECTW,*LPOLEUIINSERTOBJECTW;
typedef struct tagOLEUIINSERTOBJECTA {
	DWORD cbStruct;
	DWORD dwFlags;
	HWND hWndOwner;
	LPCSTR lpszCaption;
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	HINSTANCE hInstance;
	LPCSTR lpszTemplate;
	HRSRC hResource;
	CLSID clsid;
	LPSTR lpszFile;
	UINT cchFile;
	UINT cClsidExclude;
	LPCLSID lpClsidExclude;
	IID iid;
	DWORD oleRender;
	LPFORMATETC lpFormatEtc;
	LPOLECLIENTSITE lpIOleClientSite;
	LPSTORAGE lpIStorage;
	PVOID *ppvObj;
	SCODE sc;
	HGLOBAL hMetaPict;
} OLEUIINSERTOBJECTA,*POLEUIINSERTOBJECTA,*LPOLEUIINSERTOBJECTA;
STDAPI_(UINT) OleUIInsertObjectW(LPOLEUIINSERTOBJECTW);
STDAPI_(UINT) OleUIInsertObjectA(LPOLEUIINSERTOBJECTA);
typedef enum tagOLEUIPASTEFLAG {
	OLEUIPASTE_PASTEONLY,
	OLEUIPASTE_LINKTYPE1,
	OLEUIPASTE_LINKTYPE2,
	OLEUIPASTE_LINKTYPE3=4,
	OLEUIPASTE_LINKTYPE4=8,
	OLEUIPASTE_LINKTYPE5=16,
	OLEUIPASTE_LINKTYPE6=32,
	OLEUIPASTE_LINKTYPE7=64,
	OLEUIPASTE_LINKTYPE8=128,
	OLEUIPASTE_PASTE=512,
	OLEUIPASTE_LINKANYTYPE=1024,
	OLEUIPASTE_ENABLEICON=2048, 
} OLEUIPASTEFLAG;
typedef struct tagOLEUIPASTEENTRYW {
	FORMATETC fmtetc;
	LPCWSTR lpstrFormatName;
	LPCWSTR lpstrResultText;
	DWORD dwFlags;
	DWORD dwScratchSpace;
} OLEUIPASTEENTRYW,*POLEUIPASTEENTRYW,*LPOLEUIPASTEENTRYW;
typedef struct tagOLEUIPASTEENTRYA {
	FORMATETC fmtetc;
	LPCSTR lpstrFormatName;
	LPCSTR lpstrResultText;
	DWORD dwFlags;
	DWORD dwScratchSpace;
} OLEUIPASTEENTRYA,*POLEUIPASTEENTRYA,*LPOLEUIPASTEENTRYA;
typedef struct tagOLEUIPASTESPECIALW {
	DWORD cbStruct;
	DWORD dwFlags;
	HWND hWndOwner;
	LPCWSTR lpszCaption;
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	HINSTANCE hInstance;
	LPCWSTR lpszTemplate;
	HRSRC hResource;
	LPDATAOBJECT lpSrcDataObj;
	LPOLEUIPASTEENTRYW arrPasteEntries;
	int cPasteEntries;
	UINT *arrLinkTypes;
	int cLinkTypes;
	UINT cClsidExclude;
	LPCLSID lpClsidExclude;
	int nSelectedIndex;
	BOOL fLink;
	HGLOBAL hMetaPict;
	SIZEL sizel;
} OLEUIPASTESPECIALW,*POLEUIPASTESPECIALW,*LPOLEUIPASTESPECIALW;
typedef struct tagOLEUIPASTESPECIALA {
	DWORD cbStruct;
	DWORD dwFlags;
	HWND hWndOwner;
	LPCSTR lpszCaption;
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	HINSTANCE hInstance;
	LPCSTR lpszTemplate;
	HRSRC hResource;
	LPDATAOBJECT lpSrcDataObj;
	LPOLEUIPASTEENTRYA arrPasteEntries;
	int cPasteEntries;
	UINT *arrLinkTypes;
	int cLinkTypes;
	UINT cClsidExclude;
	LPCLSID lpClsidExclude;
	int nSelectedIndex;
	BOOL fLink;
	HGLOBAL hMetaPict;
	SIZEL sizel;
} OLEUIPASTESPECIALA,*POLEUIPASTESPECIALA,*LPOLEUIPASTESPECIALA;
#undef INTERFACE
#define INTERFACE IOleUILinkContainerW
DECLARE_INTERFACE_(IOleUILinkContainerW, IUnknown)
{
	STDMETHOD(QueryInterface) (THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef) (THIS) PURE;
	STDMETHOD_(ULONG,Release) (THIS) PURE;
	STDMETHOD_(DWORD,GetNextLink) (THIS_ DWORD dwLink) PURE;
	STDMETHOD(SetLinkUpdateOptions) (THIS_ DWORD,DWORD) PURE;
	STDMETHOD(GetLinkUpdateOptions) (THIS_ DWORD,PDWORD) PURE;
	STDMETHOD(SetLinkSource) (THIS_ DWORD, LPWSTR,ULONG,PULONG,BOOL) PURE;
	STDMETHOD(GetLinkSource) (THIS_ DWORD,LPWSTR*,PULONG,LPWSTR*,LPWSTR*,BOOL*,BOOL*) PURE;
	STDMETHOD(OpenLinkSource) (THIS_ DWORD) PURE;
	STDMETHOD(UpdateLink) (THIS_ DWORD,BOOL,BOOL) PURE;
	STDMETHOD(CancelLink) (THIS_ DWORD) PURE;
};
typedef IOleUILinkContainerW *LPOLEUILINKCONTAINERW;
#undef INTERFACE
#define INTERFACE IOleUILinkContainerA
DECLARE_INTERFACE_(IOleUILinkContainerA, IUnknown)
{
	STDMETHOD(QueryInterface) (THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef) (THIS) PURE;
	STDMETHOD_(ULONG,Release) (THIS) PURE;
	STDMETHOD_(DWORD,GetNextLink) (THIS_ DWORD) PURE;
	STDMETHOD(SetLinkUpdateOptions) (THIS_ DWORD,DWORD) PURE;
	STDMETHOD(GetLinkUpdateOptions) (THIS_ DWORD,PDWORD) PURE;
	STDMETHOD(SetLinkSource) (THIS_ DWORD, LPSTR,ULONG,PULONG,BOOL) PURE;
	STDMETHOD(GetLinkSource) (THIS_ DWORD,LPSTR*,PULONG,LPSTR*,LPSTR*,BOOL*,BOOL*) PURE;
	STDMETHOD(OpenLinkSource) (THIS_ DWORD) PURE;
	STDMETHOD(UpdateLink) (THIS_ DWORD,BOOL,BOOL) PURE;
	STDMETHOD(CancelLink) (THIS_ DWORD) PURE;
};
typedef IOleUILinkContainerA *LPOLEUILINKCONTAINERA;
typedef struct tagOLEUIEDITLINKSW {
	DWORD cbStruct;
	DWORD dwFlags;
	HWND hWndOwner;
	LPCWSTR lpszCaption;
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	HINSTANCE hInstance;
	LPCWSTR lpszTemplate;
	HRSRC hResource;
	LPOLEUILINKCONTAINERW lpOleUILinkContainer;
} OLEUIEDITLINKSW,*POLEUIEDITLINKSW,*LPOLEUIEDITLINKSW;
typedef struct tagOLEUIEDITLINKSA {
	DWORD cbStruct;
	DWORD dwFlags;
	HWND hWndOwner;
	LPCSTR lpszCaption;
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	HINSTANCE hInstance;
	LPCSTR lpszTemplate;
	HRSRC hResource;
	LPOLEUILINKCONTAINERA lpOleUILinkContainer;
} OLEUIEDITLINKSA,*POLEUIEDITLINKSA,*LPOLEUIEDITLINKSA;
typedef struct tagOLEUICHANGEICONW {
	DWORD cbStruct;
	DWORD dwFlags;
	HWND hWndOwner;
	LPCWSTR lpszCaption;
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	HINSTANCE hInstance;
	LPCWSTR lpszTemplate;
	HRSRC hResource;
	HGLOBAL hMetaPict;
	CLSID clsid;
	WCHAR szIconExe[MAX_PATH];
	int cchIconExe;
} OLEUICHANGEICONW,*POLEUICHANGEICONW,*LPOLEUICHANGEICONW;
typedef struct tagOLEUICHANGEICONA {
	DWORD cbStruct;
	DWORD dwFlags;
	HWND hWndOwner;
	LPCSTR lpszCaption;
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	HINSTANCE hInstance;
	LPCSTR lpszTemplate;
	HRSRC hResource;
	HGLOBAL hMetaPict;
	CLSID clsid;
	CHAR szIconExe[MAX_PATH];
	int cchIconExe;
} OLEUICHANGEICONA,*POLEUICHANGEICONA,*LPOLEUICHANGEICONA;
typedef struct tagOLEUICONVERTW {
	DWORD cbStruct;
	DWORD dwFlags;
	HWND hWndOwner;
	LPCWSTR lpszCaption;
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	HINSTANCE hInstance;
	LPCWSTR lpszTemplate;
	HRSRC hResource;
	CLSID clsid;
	CLSID clsidConvertDefault;
	CLSID clsidActivateDefault;
	CLSID clsidNew;
	DWORD dvAspect;
	WORD wFormat;
	BOOL fIsLinkedObject;
	HGLOBAL hMetaPict;
	LPWSTR lpszUserType;
	BOOL fObjectsIconChanged;
	LPWSTR lpszDefLabel;
	UINT cClsidExclude;
	LPCLSID lpClsidExclude;
} OLEUICONVERTW,*POLEUICONVERTW,*LPOLEUICONVERTW;
typedef struct tagOLEUICONVERTA {
	DWORD cbStruct;
	DWORD dwFlags;
	HWND hWndOwner;
	LPCSTR lpszCaption;
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	HINSTANCE hInstance;
	LPCSTR lpszTemplate;
	HRSRC hResource;
	CLSID clsid;
	CLSID clsidConvertDefault;
	CLSID clsidActivateDefault;
	CLSID clsidNew;
	DWORD dvAspect;
	WORD wFormat;
	BOOL fIsLinkedObject;
	HGLOBAL hMetaPict;
	LPSTR lpszUserType;
	BOOL fObjectsIconChanged;
	LPSTR lpszDefLabel;
	UINT cClsidExclude;
	LPCLSID lpClsidExclude;
} OLEUICONVERTA,*POLEUICONVERTA,*LPOLEUICONVERTA;
typedef struct tagOLEUIBUSYW {
	DWORD cbStruct;
	DWORD dwFlags;
	HWND hWndOwner;
	LPCWSTR lpszCaption;
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	HINSTANCE hInstance;
	LPCWSTR lpszTemplate;
	HRSRC hResource;
	HTASK hTask;
	HWND *lphWndDialog;
} OLEUIBUSYW,*POLEUIBUSYW,*LPOLEUIBUSYW;
typedef struct tagOLEUIBUSYA {
	DWORD cbStruct;
	DWORD dwFlags;
	HWND hWndOwner;
	LPCSTR lpszCaption;
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	HINSTANCE hInstance;
	LPCSTR lpszTemplate;
	HRSRC hResource;
	HTASK hTask;
	HWND *lphWndDialog;
} OLEUIBUSYA,*POLEUIBUSYA,*LPOLEUIBUSYA;
typedef struct tagOLEUICHANGESOURCEW {
	DWORD cbStruct;
	DWORD dwFlags;
	HWND hWndOwner;
	LPCWSTR lpszCaption;
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	HINSTANCE hInstance;
	LPCWSTR lpszTemplate;
	HRSRC hResource;
	OPENFILENAMEW* lpOFN;
	DWORD dwReserved1[4];
	LPOLEUILINKCONTAINERW lpOleUILinkContainer;
	DWORD dwLink;
	LPWSTR lpszDisplayName;
	ULONG nFileLength;
	LPWSTR lpszFrom;
	LPWSTR lpszTo;
} OLEUICHANGESOURCEW,*POLEUICHANGESOURCEW,*LPOLEUICHANGESOURCEW;
typedef struct tagOLEUICHANGESOURCEA {
	DWORD cbStruct;
	DWORD dwFlags;
	HWND hWndOwner;
	LPCSTR lpszCaption;
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	HINSTANCE hInstance;
	LPCSTR lpszTemplate;
	HRSRC hResource;
	OPENFILENAMEA *lpOFN;
	DWORD dwReserved1[4];
	LPOLEUILINKCONTAINERA lpOleUILinkContainer;
	DWORD dwLink;
	LPSTR lpszDisplayName;
	ULONG nFileLength;
	LPSTR lpszFrom;
	LPSTR lpszTo;
} OLEUICHANGESOURCEA,*POLEUICHANGESOURCEA,*LPOLEUICHANGESOURCEA;
#undef INTERFACE
#define INTERFACE IOleUIObjInfoW
DECLARE_INTERFACE_(IOleUIObjInfoW, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetObjectInfo)(THIS_ DWORD,PDWORD,LPWSTR*,LPWSTR*,LPWSTR*,LPWSTR*) PURE;
	STDMETHOD(GetConvertInfo)(THIS_ DWORD,CLSID*,PWORD,CLSID*,LPCLSID*,UINT*) PURE;
	STDMETHOD(ConvertObject)(THIS_ DWORD,REFCLSID) PURE;
	STDMETHOD(GetViewInfo)(THIS_ DWORD,HGLOBAL*,PDWORD,int*) PURE;
	STDMETHOD(SetViewInfo)(THIS_ DWORD,HGLOBAL,DWORD,int,BOOL) PURE;
};
typedef IOleUIObjInfoW *LPOLEUIOBJINFOW;
#undef INTERFACE
#define INTERFACE IOleUIObjInfoA
DECLARE_INTERFACE_(IOleUIObjInfoA, IUnknown)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD(GetObjectInfo)(THIS_ DWORD,PDWORD,LPSTR*,LPSTR*,LPSTR*,LPSTR*) PURE;
	STDMETHOD(GetConvertInfo)(THIS_ DWORD,CLSID*,PWORD,CLSID*,LPCLSID*,UINT*) PURE;
	STDMETHOD(ConvertObject)(THIS_ DWORD,REFCLSID) PURE;
	STDMETHOD(GetViewInfo)(THIS_ DWORD,HGLOBAL*,PDWORD,int*) PURE;
	STDMETHOD(SetViewInfo)(THIS_ DWORD,HGLOBAL,DWORD,int,BOOL) PURE;
};
typedef IOleUIObjInfoA *LPOLEUIOBJINFOA;
#undef INTERFACE
#define INTERFACE IOleUILinkInfoW
DECLARE_INTERFACE_(IOleUILinkInfoW, IOleUILinkContainerW)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD_(DWORD,GetNextLink)(THIS_ DWORD) PURE;
	STDMETHOD(SetLinkUpdateOptions)(THIS_ DWORD,DWORD) PURE;
	STDMETHOD(GetLinkUpdateOptions)(THIS_ DWORD,DWORD*) PURE;
	STDMETHOD(SetLinkSource)(THIS_ DWORD,LPWSTR,ULONG,PULONG,BOOL) PURE;
	STDMETHOD(GetLinkSource)(THIS_ DWORD,LPWSTR*,PULONG,LPWSTR*,LPWSTR*,BOOL*,BOOL*) PURE;
	STDMETHOD(OpenLinkSource)(THIS_ DWORD) PURE;
	STDMETHOD(UpdateLink)(THIS_ DWORD,BOOL,BOOL) PURE;
	STDMETHOD(CancelLink)(THIS_ DWORD) PURE;
	STDMETHOD(GetLastUpdate)(THIS_ DWORD,FILETIME*) PURE;
};
typedef IOleUILinkInfoW *LPOLEUILINKINFOW;
#undef INTERFACE
#define INTERFACE IOleUILinkInfoA
DECLARE_INTERFACE_(IOleUILinkInfoA, IOleUILinkContainerA)
{
	STDMETHOD(QueryInterface)(THIS_ REFIID,PVOID*) PURE;
	STDMETHOD_(ULONG,AddRef)(THIS) PURE;
	STDMETHOD_(ULONG,Release)(THIS) PURE;
	STDMETHOD_(DWORD,GetNextLink)(THIS_ DWORD) PURE;
	STDMETHOD(SetLinkUpdateOptions)(THIS_ DWORD,DWORD) PURE;
	STDMETHOD(GetLinkUpdateOptions)(THIS_ DWORD,DWORD*) PURE;
	STDMETHOD(SetLinkSource)(THIS_ DWORD,LPSTR,ULONG,PULONG,BOOL) PURE;
	STDMETHOD(GetLinkSource)(THIS_ DWORD,LPSTR*,PULONG,LPSTR*,LPSTR*,BOOL*,BOOL*) PURE;
	STDMETHOD(OpenLinkSource)(THIS_ DWORD) PURE;
	STDMETHOD(UpdateLink)(THIS_ DWORD,BOOL,BOOL) PURE;
	STDMETHOD(CancelLink)(THIS_ DWORD) PURE;
	STDMETHOD(GetLastUpdate)(THIS_ DWORD,FILETIME*) PURE;
};
typedef IOleUILinkInfoA* LPOLEUILINKINFOA;
struct tagOLEUIOBJECTPROPSW;
struct tagOLEUIOBJECTPROPSA;
typedef struct tagOLEUIGNRLPROPSW {
	DWORD cbStruct;
	DWORD dwFlags;
	DWORD dwReserved1[2];
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	DWORD dwReserved2[3];
	struct tagOLEUIOBJECTPROPSW* lpOP;
} OLEUIGNRLPROPSW,*POLEUIGNRLPROPSW,*LPOLEUIGNRLPROPSW;
typedef struct tagOLEUIGNRLPROPSA {
	DWORD cbStruct;
	DWORD dwFlags;
	DWORD dwReserved1[2];
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	DWORD dwReserved2[3];
	struct tagOLEUIOBJECTPROPSA* lpOP;
} OLEUIGNRLPROPSA,*POLEUIGNRLPROPSA,*LPOLEUIGNRLPROPSA;
typedef struct tagOLEUIVIEWPROPSW {
	DWORD cbStruct;
	DWORD dwFlags;
	DWORD dwReserved1[2];
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	DWORD dwReserved2[3];
	struct tagOLEUIOBJECTPROPSW* lpOP;
	int nScaleMin;
	int nScaleMax;
} OLEUIVIEWPROPSW,*POLEUIVIEWPROPSW,*LPOLEUIVIEWPROPSW;
typedef struct tagOLEUIVIEWPROPSA {
	DWORD cbStruct;
	DWORD dwFlags;
	DWORD dwReserved1[2];
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	DWORD dwReserved2[3];
	struct tagOLEUIOBJECTPROPSA *lpOP;
	int nScaleMin;
	int nScaleMax;
} OLEUIVIEWPROPSA,*POLEUIVIEWPROPSA,*LPOLEUIVIEWPROPSA;
typedef struct tagOLEUILINKPROPSW {
	DWORD cbStruct;
	DWORD dwFlags;
	DWORD dwReserved1[2];
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	DWORD dwReserved2[3];
	struct tagOLEUIOBJECTPROPSW *lpOP;
} OLEUILINKPROPSW, *POLEUILINKPROPSW,* LPOLEUILINKPROPSW;
typedef struct tagOLEUILINKPROPSA {
	DWORD cbStruct;
	DWORD dwFlags;
	DWORD dwReserved1[2];
	LPFNOLEUIHOOK lpfnHook;
	LPARAM lCustData;
	DWORD dwReserved2[3];
	struct tagOLEUIOBJECTPROPSA* lpOP;
} OLEUILINKPROPSA,*POLEUILINKPROPSA,*LPOLEUILINKPROPSA;
typedef struct tagOLEUIOBJECTPROPSW {
	DWORD cbStruct;
	DWORD dwFlags;
	LPPROPSHEETHEADERW lpPS;
	DWORD dwObject;
	LPOLEUIOBJINFOW lpObjInfo;
	DWORD dwLink;
	LPOLEUILINKINFOW lpLinkInfo;
	LPOLEUIGNRLPROPSW lpGP;
	LPOLEUIVIEWPROPSW lpVP;
	LPOLEUILINKPROPSW lpLP;
} OLEUIOBJECTPROPSW,*POLEUIOBJECTPROPSW,*LPOLEUIOBJECTPROPSW;
typedef struct tagOLEUIOBJECTPROPSA {
	DWORD cbStruct;
	DWORD dwFlags;
	LPPROPSHEETHEADERA lpPS;
	DWORD dwObject;
	LPOLEUIOBJINFOA lpObjInfo;
	DWORD dwLink;
	LPOLEUILINKINFOA lpLinkInfo;
	LPOLEUIGNRLPROPSA lpGP;
	LPOLEUIVIEWPROPSA lpVP;
	LPOLEUILINKPROPSA lpLP;
} OLEUIOBJECTPROPSA,*POLEUIOBJECTPROPSA,*LPOLEUIOBJECTPROPSA;

STDAPI_(BOOL) OleUIAddVerbMenuW(LPOLEOBJECT,LPCWSTR,HMENU,UINT,UINT,UINT,BOOL,UINT,HMENU*);
STDAPI_(BOOL) OleUIAddVerbMenuA(LPOLEOBJECT,LPCSTR,HMENU,UINT,UINT,UINT,BOOL,UINT,HMENU*);
STDAPI_(UINT) OleUIBusyW(LPOLEUIBUSYW);
STDAPI_(UINT) OleUIBusyA(LPOLEUIBUSYA);
STDAPI_(BOOL) OleUICanConvertOrActivateAs(REFCLSID,BOOL,WORD);
STDAPI_(UINT) OleUIChangeIconW(LPOLEUICHANGEICONW);
STDAPI_(UINT) OleUIChangeIconA(LPOLEUICHANGEICONA);
STDAPI_(UINT) OleUIChangeSourceW(LPOLEUICHANGESOURCEW);
STDAPI_(UINT) OleUIChangeSourceA(LPOLEUICHANGESOURCEA);
STDAPI_(UINT) OleUIConvertW(LPOLEUICONVERTW);
STDAPI_(UINT) OleUIConvertA(LPOLEUICONVERTA);
STDAPI_(UINT) OleUIEditLinksW(LPOLEUIEDITLINKSW);
STDAPI_(UINT) OleUIEditLinksA(LPOLEUIEDITLINKSA);
STDAPI_(UINT) OleUIObjectPropertiesW(LPOLEUIOBJECTPROPSW);
STDAPI_(UINT) OleUIObjectPropertiesA(LPOLEUIOBJECTPROPSA);
STDAPI_(UINT) OleUIPasteSpecialW(LPOLEUIPASTESPECIALW);
STDAPI_(UINT) OleUIPasteSpecialA(LPOLEUIPASTESPECIALA);
int OleUIPromptUserW(int,HWND,...);
int OleUIPromptUserA(int,HWND,...);
STDAPI_(BOOL) OleUIUpdateLinksW(LPOLEUILINKCONTAINERW,HWND,LPWSTR,int);
STDAPI_(BOOL) OleUIUpdateLinksA(LPOLEUILINKCONTAINERA,HWND,LPSTR,int);

#ifdef UNICODE
#define IDD_SERVERNOTREG IDD_SERVERNOTREGW
#define IDD_LINKTYPECHANGED IDD_LINKTYPECHANGEDW
#define OleUIUpdateLinks OleUIUpdateLinksW
#define OleUIAddVerbMenu OleUIAddVerbMenuW
#define tagOLEUIOBJECTPROPS tagOLEUIOBJECTPROPSW
#define OLEUIOBJECTPROPS OLEUIOBJECTPROPSW
#define POLEUIOBJECTPROPS POLEUIOBJECTPROPSW
#define LPOLEUIOBJECTPROPS LPOLEUIOBJECTPROPSW
#define OleUIObjectProperties OleUIObjectPropertiesW
#define tagOLEUIINSERTOBJECT tagOLEUIINSERTOBJECTW
#define OLEUIINSERTOBJECT OLEUIINSERTOBJECTW
#define POLEUIINSERTOBJECT POLEUIINSERTOBJECTW
#define LPOLEUIINSERTOBJECT LPOLEUIINSERTOBJECTW
#define OleUIInsertObject OleUIInsertObjectW
#define OleUIPromptUser OleUIPromptUserW
#define tagOLEUIPASTEENTRY tagOLEUIPASTEENTRYW
#define OLEUIPASTEENTRY OLEUIPASTEENTRYW
#define POLEUIPASTEENTRY POLEUIPASTEENTRYW
#define LPOLEUIPASTEENTRY LPOLEUIPASTEENTRYW
#define tagOLEUIPASTESPECIAL tagOLEUIPASTESPECIALW
#define OLEUIPASTESPECIAL OLEUIPASTESPECIALW
#define POLEUIPASTESPECIAL POLEUIPASTESPECIALW
#define LPOLEUIPASTESPECIAL LPOLEUIPASTESPECIALW
#define OleUIPasteSpecial OleUIPasteSpecialW
#define IOleUILinkContainer IOleUILinkContainerW
#define LPOLEUILINKCONTAINER LPOLEUILINKCONTAINERW
#define tagOLEUIEDITLINKS tagOLEUIEDITLINKSW
#define OLEUIEDITLINKS OLEUIEDITLINKSW
#define POLEUIEDITLINKS POLEUIEDITLINKSW
#define LPOLEUIEDITLINKS LPOLEUIEDITLINKSW
#define OleUIEditLinks OleUIEditLinksW
#define tagOLEUICHANGEICON tagOLEUICHANGEICONW
#define OLEUICHANGEICON OLEUICHANGEICONW
#define POLEUICHANGEICON POLEUICHANGEICONW
#define LPOLEUICHANGEICON LPOLEUICHANGEICONW
#define OleUIChangeIcon OleUIChangeIconW
#define tagOLEUICONVERT tagOLEUICONVERTW
#define OLEUICONVERT OLEUICONVERTW
#define POLEUICONVERT POLEUICONVERTW
#define LPOLEUICONVERT LPOLEUICONVERTW
#define OleUIConvert OleUIConvertW
#define tagOLEUIBUSY tagOLEUIBUSYW
#define OLEUIBUSY OLEUIBUSYW
#define POLEUIBUSY POLEUIBUSYW
#define LPOLEUIBUSY LPOLEUIBUSYW
#define OleUIBusy OleUIBusyW
#define tagOLEUICHANGESOURCE tagOLEUICHANGESOURCEW
#define OLEUICHANGESOURCE OLEUICHANGESOURCEW
#define POLEUICHANGESOURCE POLEUICHANGESOURCEW
#define LPOLEUICHANGESOURCE LPOLEUICHANGESOURCEW
#define OleUIChangeSource OleUIChangeSourceW
#define IOleUIObjInfo IOleUIObjInfoW
#define LPOLEUIOBJINFO LPOLEUIOBJINFOW
#define IOleUILinkInfo IOleUILinkInfoW
#define IOleUILinkInfoVtbl IOleUILinkInfoWVtbl
#define LPOLEUILINKINFO LPOLEUILINKINFOW
#define tagOLEUIGNRLPROPS tagOLEUIGNRLPROPSW
#define OLEUIGNRLPROPS OLEUIGNRLPROPSW
#define POLEUIGNRLPROPS POLEUIGNRLPROPSW
#define LPOLEUIGNRLPROPS LPOLEUIGNRLPROPSW
#define tagOLEUIVIEWPROPS tagOLEUIVIEWPROPSW
#define OLEUIVIEWPROPS OLEUIVIEWPROPSW
#define POLEUIVIEWPROPS POLEUIVIEWPROPSW
#define LPOLEUIVIEWPROPS LPOLEUIVIEWPROPSW
#define tagOLEUILINKPROPS tagOLEUILINKPROPSW
#define OLEUILINKPROPS OLEUILINKPROPSW
#define POLEUILINKPROPS POLEUILINKPROPSW
#define LPOLEUILINKPROPS LPOLEUILINKPROPSW
#else
#define IDD_SERVERNOTREG IDD_SERVERNOTREGA
#define IDD_LINKTYPECHANGED IDD_LINKTYPECHANGEDA
#define OleUIUpdateLinks OleUIUpdateLinksA
#define OleUIAddVerbMenu OleUIAddVerbMenuA
#define tagOLEUIOBJECTPROPS tagOLEUIOBJECTPROPSA
#define OLEUIOBJECTPROPS OLEUIOBJECTPROPSA
#define POLEUIOBJECTPROPS POLEUIOBJECTPROPSA
#define LPOLEUIOBJECTPROPS LPOLEUIOBJECTPROPSA
#define OleUIObjectProperties OleUIObjectPropertiesA
#define tagOLEUIINSERTOBJECT tagOLEUIINSERTOBJECTA
#define OLEUIINSERTOBJECT OLEUIINSERTOBJECTA
#define POLEUIINSERTOBJECT POLEUIINSERTOBJECTA
#define LPOLEUIINSERTOBJECT LPOLEUIINSERTOBJECTA
#define OleUIInsertObject OleUIInsertObjectA
#define OleUIPromptUser OleUIPromptUserA
#define tagOLEUIPASTEENTRY tagOLEUIPASTEENTRYA
#define OLEUIPASTEENTRY OLEUIPASTEENTRYA
#define POLEUIPASTEENTRY POLEUIPASTEENTRYA
#define LPOLEUIPASTEENTRY LPOLEUIPASTEENTRYA
#define tagOLEUIPASTESPECIAL tagOLEUIPASTESPECIALA
#define OLEUIPASTESPECIAL OLEUIPASTESPECIALA
#define POLEUIPASTESPECIAL POLEUIPASTESPECIALA
#define LPOLEUIPASTESPECIAL LPOLEUIPASTESPECIALA
#define OleUIPasteSpecial OleUIPasteSpecialA
#define IOleUILinkContainer IOleUILinkContainerA
#define LPOLEUILINKCONTAINER LPOLEUILINKCONTAINERA
#define tagOLEUIEDITLINKS tagOLEUIEDITLINKSA
#define OLEUIEDITLINKS OLEUIEDITLINKSA
#define POLEUIEDITLINKS POLEUIEDITLINKSA
#define LPOLEUIEDITLINKS LPOLEUIEDITLINKSA
#define OleUIEditLinks OleUIEditLinksA
#define tagOLEUICHANGEICON tagOLEUICHANGEICONA
#define OLEUICHANGEICON OLEUICHANGEICONA
#define POLEUICHANGEICON POLEUICHANGEICONA
#define LPOLEUICHANGEICON LPOLEUICHANGEICONA
#define OleUIChangeIcon OleUIChangeIconA
#define tagOLEUICONVERT tagOLEUICONVERTA
#define OLEUICONVERT OLEUICONVERTA
#define POLEUICONVERT POLEUICONVERTA
#define LPOLEUICONVERT LPOLEUICONVERTA
#define OleUIConvert OleUIConvertA
#define tagOLEUIBUSY tagOLEUIBUSYA
#define OLEUIBUSY OLEUIBUSYA
#define POLEUIBUSY POLEUIBUSYA
#define LPOLEUIBUSY LPOLEUIBUSYA
#define OleUIBusy OleUIBusyA
#define tagOLEUICHANGESOURCE tagOLEUICHANGESOURCEA
#define OLEUICHANGESOURCE OLEUICHANGESOURCEA
#define POLEUICHANGESOURCE POLEUICHANGESOURCEA
#define LPOLEUICHANGESOURCE LPOLEUICHANGESOURCEA
#define OleUIChangeSource OleUIChangeSourceA
#define IOleUIObjInfo IOleUIObjInfoA
#define LPOLEUIOBJINFO LPOLEUIOBJINFOA
#define IOleUILinkInfo IOleUILinkInfoA
#define IOleUILinkInfoVtbl IOleUILinkInfoAVtbl
#define LPOLEUILINKINFO LPOLEUILINKINFOA
#define tagOLEUIGNRLPROPS tagOLEUIGNRLPROPSA
#define OLEUIGNRLPROPS OLEUIGNRLPROPSA
#define POLEUIGNRLPROPS POLEUIGNRLPROPSA
#define LPOLEUIGNRLPROPS LPOLEUIGNRLPROPSA
#define tagOLEUIVIEWPROPS tagOLEUIVIEWPROPSA
#define OLEUIVIEWPROPS OLEUIVIEWPROPSA
#define POLEUIVIEWPROPS POLEUIVIEWPROPSA
#define LPOLEUIVIEWPROPS LPOLEUIVIEWPROPSA
#define tagOLEUILINKPROPS tagOLEUILINKPROPSA
#define OLEUILINKPROPS OLEUILINKPROPSA
#define POLEUILINKPROPS POLEUILINKPROPSA
#define LPOLEUILINKPROPS LPOLEUILINKPROPSA
#endif
#pragma pack(pop)
#endif
#ifdef __cplusplus
}
#endif
#endif 
