#ifndef _WINNLS_H
#define _WINNLS_H
#ifdef __cplusplus
extern "C" {
#endif

#define MAX_LEADBYTES 	12
#define MAX_DEFAULTCHAR	2
#define LOCALE_NOUSEROVERRIDE	0x80000000
#define LOCALE_USE_CP_ACP	0x40000000
#define LOCALE_ILANGUAGE	1
#define LOCALE_SLANGUAGE	2
#define LOCALE_SENGLANGUAGE	0x1001
#define LOCALE_SABBREVLANGNAME	3
#define LOCALE_SNATIVELANGNAME	4
#define LOCALE_ICOUNTRY	5
#define LOCALE_SCOUNTRY	6
#define LOCALE_SENGCOUNTRY	0x1002
#define LOCALE_SABBREVCTRYNAME	7
#define LOCALE_SNATIVECTRYNAME	8
#define LOCALE_IDEFAULTLANGUAGE	9
#define LOCALE_IDEFAULTCOUNTRY	10
#define LOCALE_IDEFAULTCODEPAGE	11
#define LOCALE_IDEFAULTANSICODEPAGE 0x1004
#define LOCALE_SLIST	12
#define LOCALE_IMEASURE	13
#define LOCALE_SDECIMAL	14
#define LOCALE_STHOUSAND	15
#define LOCALE_SGROUPING	16
#define LOCALE_IDIGITS	17
#define LOCALE_ILZERO	18
#define LOCALE_INEGNUMBER	0x1010
#define LOCALE_SNATIVEDIGITS	19
#define LOCALE_SCURRENCY	20
#define LOCALE_SINTLSYMBOL	21
#define LOCALE_SMONDECIMALSEP	22
#define LOCALE_SMONTHOUSANDSEP	23
#define LOCALE_SMONGROUPING	24
#define LOCALE_ICURRDIGITS	25
#define LOCALE_IINTLCURRDIGITS	26
#define LOCALE_ICURRENCY	27
#define LOCALE_INEGCURR	28
#define LOCALE_SDATE	29
#define LOCALE_STIME	30
#define LOCALE_SSHORTDATE	31
#define LOCALE_SLONGDATE	32
#define LOCALE_STIMEFORMAT	0x1003
#define LOCALE_IDATE	33
#define LOCALE_ILDATE	34
#define LOCALE_ITIME	35
#define LOCALE_ITIMEMARKPOSN	0x1005
#define LOCALE_ICENTURY	36
#define LOCALE_ITLZERO	37
#define LOCALE_IDAYLZERO	38
#define LOCALE_IMONLZERO	39
#define LOCALE_S1159	40
#define LOCALE_S2359	41
#define LOCALE_ICALENDARTYPE	0x1009
#define LOCALE_IOPTIONALCALENDAR	0x100B
#define LOCALE_IFIRSTDAYOFWEEK	0x100C
#define LOCALE_IFIRSTWEEKOFYEAR	0x100D
#define LOCALE_SDAYNAME1	42
#define LOCALE_SDAYNAME2	43
#define LOCALE_SDAYNAME3	44
#define LOCALE_SDAYNAME4	45
#define LOCALE_SDAYNAME5	46
#define LOCALE_SDAYNAME6	47
#define LOCALE_SDAYNAME7	48
#define LOCALE_SABBREVDAYNAME1	49
#define LOCALE_SABBREVDAYNAME2	50
#define LOCALE_SABBREVDAYNAME3	51
#define LOCALE_SABBREVDAYNAME4	52
#define LOCALE_SABBREVDAYNAME5	53
#define LOCALE_SABBREVDAYNAME6	54
#define LOCALE_SABBREVDAYNAME7	55
#define LOCALE_SMONTHNAME1	56
#define LOCALE_SMONTHNAME2	57
#define LOCALE_SMONTHNAME3	58
#define LOCALE_SMONTHNAME4	59
#define LOCALE_SMONTHNAME5	60
#define LOCALE_SMONTHNAME6	61
#define LOCALE_SMONTHNAME7	62
#define LOCALE_SMONTHNAME8	63
#define LOCALE_SMONTHNAME9	64
#define LOCALE_SMONTHNAME10	65
#define LOCALE_SMONTHNAME11	66
#define LOCALE_SMONTHNAME12	67
#define LOCALE_SMONTHNAME13	0x100E
#define LOCALE_SABBREVMONTHNAME1	68
#define LOCALE_SABBREVMONTHNAME2	69
#define LOCALE_SABBREVMONTHNAME3	70
#define LOCALE_SABBREVMONTHNAME4	71
#define LOCALE_SABBREVMONTHNAME5	72
#define LOCALE_SABBREVMONTHNAME6	73
#define LOCALE_SABBREVMONTHNAME7	74
#define LOCALE_SABBREVMONTHNAME8	75
#define LOCALE_SABBREVMONTHNAME9	76
#define LOCALE_SABBREVMONTHNAME10	77
#define LOCALE_SABBREVMONTHNAME11	78
#define LOCALE_SABBREVMONTHNAME12	79
#define LOCALE_SABBREVMONTHNAME13	0x100F
#define LOCALE_SPOSITIVESIGN	80
#define LOCALE_SNEGATIVESIGN	81
#define LOCALE_IPOSSIGNPOSN	82
#define LOCALE_INEGSIGNPOSN	83
#define LOCALE_IPOSSYMPRECEDES	84
#define LOCALE_IPOSSEPBYSPACE	85
#define LOCALE_INEGSYMPRECEDES	86
#define LOCALE_INEGSEPBYSPACE	87
#define LOCALE_FONTSIGNATURE	88
#define LOCALE_SYSTEM_DEFAULT	0x800
#define LOCALE_USER_DEFAULT	0x400
#define NORM_IGNORECASE	1
#define NORM_IGNOREKANATYPE	65536
#define NORM_IGNORENONSPACE	2
#define NORM_IGNORESYMBOLS	4
#define NORM_IGNOREWIDTH	131072
#define SORT_STRINGSORT	4096
#define LCMAP_BYTEREV	2048
#define LCMAP_FULLWIDTH	8388608
#define LCMAP_HALFWIDTH	4194304
#define LCMAP_HIRAGANA	1048576
#define LCMAP_KATAKANA	2097152
#define LCMAP_LOWERCASE	256
#define LCMAP_SORTKEY	1024
#define LCMAP_UPPERCASE	512
#define ENUM_ALL_CALENDARS (-1)
#define DATE_SHORTDATE 1
#define DATE_LONGDATE 2
#define DATE_USE_ALT_CALENDAR 4
#define CP_INSTALLED 1
#define CP_SUPPORTED 2
#define LCID_INSTALLED 1
#define LCID_SUPPORTED 2
#define MAP_FOLDCZONE 16
#define MAP_FOLDDIGITS 128
#define MAP_PRECOMPOSED 32
#define MAP_COMPOSITE 64
#define CP_ACP 0
#define CP_OEMCP 1
#define CP_MACCP 2
#define CP_THREAD_ACP 3
#define CP_SYMBOL 42
#define CP_UTF7 65000
#define CP_UTF8 65001
#define CT_CTYPE1 1
#define CT_CTYPE2 2
#define CT_CTYPE3 4
#define C1_UPPER 1
#define C1_LOWER 2
#define C1_DIGIT 4
#define C1_SPACE 8
#define C1_PUNCT 16
#define C1_CNTRL 32
#define C1_BLANK 64
#define C1_XDIGIT 128
#define C1_ALPHA 256
#define C2_LEFTTORIGHT 1
#define C2_RIGHTTOLEFT 2
#define C2_EUROPENUMBER 3
#define C2_EUROPESEPARATOR 4
#define C2_EUROPETERMINATOR 5
#define C2_ARABICNUMBER 6
#define C2_COMMONSEPARATOR 7
#define C2_BLOCKSEPARATOR 8
#define C2_SEGMENTSEPARATOR 9
#define C2_WHITESPACE 10
#define C2_OTHERNEUTRAL 11
#define C2_NOTAPPLICABLE 0
#define C3_NONSPACING 1
#define C3_DIACRITIC 2
#define C3_VOWELMARK 4
#define C3_SYMBOL 8
#define C3_KATAKANA 16
#define C3_HIRAGANA 32
#define C3_HALFWIDTH 64
#define C3_FULLWIDTH 128
#define C3_IDEOGRAPH 256
#define C3_KASHIDA 512
#define C3_ALPHA 32768
#define C3_NOTAPPLICABLE 0
#define TIME_NOMINUTESORSECONDS 1
#define TIME_NOSECONDS 2
#define TIME_NOTIMEMARKER 4
#define TIME_FORCE24HOURFORMAT 8
#define LCMAP_BYTEREV 2048
#define LCMAP_FULLWIDTH 8388608
#define LCMAP_HALFWIDTH 4194304
#define LCMAP_HIRAGANA 1048576
#define LCMAP_KATAKANA 2097152
#define LCMAP_LOWERCASE 256
#define LCMAP_SORTKEY 1024
#define LCMAP_UPPERCASE 512
#define SORT_STRINGSORT 4096
#define NORM_IGNORECASE 1
#define NORM_IGNORENONSPACE 2
#define NORM_IGNORESYMBOLS 4
#define NORM_IGNOREKANATYPE 65536
#define NORM_IGNOREWIDTH 131072
#define MB_PRECOMPOSED 1
#define MB_COMPOSITE 2
#define MB_ERR_INVALID_CHARS 8
#define MB_USEGLYPHCHARS 4
#define WC_COMPOSITECHECK 512
#define WC_DISCARDNS 16
#define WC_SEPCHARS 32
#define WC_DEFAULTCHAR 64
#define CTRY_DEFAULT 0
#define CTRY_AUSTRALIA 61
#define CTRY_AUSTRIA 43
#define CTRY_BELGIUM 32
#define CTRY_BRAZIL 55
#define CTRY_BULGARIA 359
#define CTRY_CANADA 2
#define CTRY_CROATIA 385
#define CTRY_CZECH 42
#define CTRY_DENMARK 45
#define CTRY_FINLAND 358
#define CTRY_FRANCE 33
#define CTRY_GERMANY 49
#define CTRY_GREECE 30
#define CTRY_HONG_KONG 852
#define CTRY_HUNGARY 36
#define CTRY_ICELAND 354
#define CTRY_IRELAND 353
#define CTRY_ITALY 39
#define CTRY_JAPAN 81
#define CTRY_MEXICO 52
#define CTRY_NETHERLANDS 31
#define CTRY_NEW_ZEALAND 64
#define CTRY_NORWAY 47
#define CTRY_POLAND 48
#define CTRY_PORTUGAL 351
#define CTRY_PRCHINA 86
#define CTRY_ROMANIA 40
#define CTRY_RUSSIA 7
#define CTRY_SINGAPORE 65
#define CTRY_SLOVAK 42
#define CTRY_SLOVENIA 386
#define CTRY_SOUTH_KOREA 82
#define CTRY_SPAIN 34
#define CTRY_SWEDEN 46
#define CTRY_SWITZERLAND 41
#define CTRY_TAIWAN 886
#define CTRY_TURKEY 90
#define CTRY_UNITED_KINGDOM 44
#define CTRY_UNITED_STATES 1
#define CAL_ICALINTVALUE 1
#define CAL_SCALNAME 2
#define CAL_IYEAROFFSETRANGE 3
#define CAL_SERASTRING 4
#define CAL_SSHORTDATE 5
#define CAL_SLONGDATE 6
#define CAL_SDAYNAME1 7
#define CAL_SDAYNAME2 8
#define CAL_SDAYNAME3 9
#define CAL_SDAYNAME4 10
#define CAL_SDAYNAME5 11
#define CAL_SDAYNAME6 12
#define CAL_SDAYNAME7 13
#define CAL_SABBREVDAYNAME1 14
#define CAL_SABBREVDAYNAME2 15
#define CAL_SABBREVDAYNAME3 16
#define CAL_SABBREVDAYNAME4 17
#define CAL_SABBREVDAYNAME5 18
#define CAL_SABBREVDAYNAME6 19
#define CAL_SABBREVDAYNAME7 20
#define CAL_SMONTHNAME1 21
#define CAL_SMONTHNAME2 22
#define CAL_SMONTHNAME3 23
#define CAL_SMONTHNAME4 24
#define CAL_SMONTHNAME5 25
#define CAL_SMONTHNAME6 26
#define CAL_SMONTHNAME7 27
#define CAL_SMONTHNAME8 28
#define CAL_SMONTHNAME9 29
#define CAL_SMONTHNAME10 30
#define CAL_SMONTHNAME11 31
#define CAL_SMONTHNAME12 32
#define CAL_SMONTHNAME13 33
#define CAL_SABBREVMONTHNAME1 34
#define CAL_SABBREVMONTHNAME2 35
#define CAL_SABBREVMONTHNAME3 36
#define CAL_SABBREVMONTHNAME4 37
#define CAL_SABBREVMONTHNAME5 38
#define CAL_SABBREVMONTHNAME6 39
#define CAL_SABBREVMONTHNAME7 40
#define CAL_SABBREVMONTHNAME8 41
#define CAL_SABBREVMONTHNAME9 42
#define CAL_SABBREVMONTHNAME10 43
#define CAL_SABBREVMONTHNAME11 44
#define CAL_SABBREVMONTHNAME12 45
#define CAL_SABBREVMONTHNAME13 46
#define CAL_GREGORIAN 1
#define CAL_GREGORIAN_US 2
#define CAL_JAPAN 3
#define CAL_TAIWAN 4
#define CAL_KOREA 5

#ifndef RC_INVOKED
typedef DWORD LCTYPE;
typedef ULONG CALTYPE;
typedef ULONG CALID;
typedef BOOL (CALLBACK *CALINFO_ENUMPROCA)(LPSTR);
typedef BOOL (CALLBACK *CALINFO_ENUMPROCW)(LPWSTR);
typedef BOOL (CALLBACK *LOCALE_ENUMPROCA)(LPSTR);
typedef BOOL (CALLBACK *LOCALE_ENUMPROCW)(LPWSTR);
typedef BOOL (CALLBACK *CODEPAGE_ENUMPROCA)(LPSTR);
typedef BOOL (CALLBACK *CODEPAGE_ENUMPROCW)(LPWSTR);
typedef BOOL (CALLBACK *DATEFMT_ENUMPROCA)(LPSTR);
typedef BOOL (CALLBACK *DATEFMT_ENUMPROCW)(LPWSTR);
typedef BOOL (CALLBACK *TIMEFMT_ENUMPROCA)(LPSTR);
typedef BOOL (CALLBACK *TIMEFMT_ENUMPROCW)(LPWSTR);
typedef struct _cpinfo {
	UINT MaxCharSize;
	BYTE DefaultChar[MAX_DEFAULTCHAR];
	BYTE LeadByte[MAX_LEADBYTES];
} CPINFO,*LPCPINFO;
typedef struct _currencyfmtA {
	UINT NumDigits;
	UINT LeadingZero;
	UINT Grouping;
	LPSTR lpDecimalSep;
	LPSTR lpThousandSep;
	UINT NegativeOrder;
	UINT PositiveOrder;
	LPSTR lpCurrencySymbol;
} CURRENCYFMTA;
typedef struct _currencyfmtW {
	UINT NumDigits;
	UINT LeadingZero;
	UINT Grouping;
	LPWSTR lpDecimalSep;
	LPWSTR lpThousandSep;
	UINT NegativeOrder;
	UINT PositiveOrder;
	LPWSTR lpCurrencySymbol;
} CURRENCYFMTW;
typedef struct _numberfmtA {
	UINT NumDigits;
	UINT LeadingZero;
	UINT Grouping;
	LPSTR lpDecimalSep;
	LPSTR lpThousandSep;
	UINT NegativeOrder;
} NUMBERFMTA;
typedef struct _numberfmtW {
	UINT NumDigits;
	UINT LeadingZero;
	UINT Grouping;
	LPWSTR lpDecimalSep;
	LPWSTR lpThousandSep;
	UINT NegativeOrder;
} NUMBERFMTW;

int WINAPI CompareStringA(LCID,DWORD,LPCSTR,int,LPCSTR,int);
int WINAPI CompareStringW(LCID,DWORD,LPCWSTR,int,LPCWSTR,int);
LCID WINAPI ConvertDefaultLocale(LCID);
BOOL WINAPI EnumCalendarInfoA(CALINFO_ENUMPROCA,LCID,CALID,CALTYPE);
BOOL WINAPI EnumCalendarInfoW(CALINFO_ENUMPROCW,LCID,CALID,CALTYPE);
BOOL WINAPI EnumDateFormatsA(DATEFMT_ENUMPROCA,LCID,DWORD);
BOOL WINAPI EnumDateFormatsW(DATEFMT_ENUMPROCW,LCID,DWORD);
BOOL WINAPI EnumSystemCodePagesA(CODEPAGE_ENUMPROCA,DWORD);
BOOL WINAPI EnumSystemCodePagesW(CODEPAGE_ENUMPROCW,DWORD);
BOOL WINAPI EnumSystemLocalesA(LOCALE_ENUMPROCA,DWORD);
BOOL WINAPI EnumSystemLocalesW(LOCALE_ENUMPROCW,DWORD);
BOOL WINAPI EnumTimeFormatsA(TIMEFMT_ENUMPROCA,LCID,DWORD);
BOOL WINAPI EnumTimeFormatsW(TIMEFMT_ENUMPROCW,LCID,DWORD);
int WINAPI FoldStringA(DWORD,LPCSTR,int,LPSTR,int);
int WINAPI FoldStringW(DWORD,LPCWSTR,int,LPWSTR,int);
UINT WINAPI GetACP(void);
BOOL WINAPI GetCPInfo(UINT,LPCPINFO);
int WINAPI GetCurrencyFormatA(LCID,DWORD,LPCSTR,const CURRENCYFMTA*,LPSTR,int);
int WINAPI GetCurrencyFormatW(LCID,DWORD,LPCWSTR,const CURRENCYFMTW*,LPWSTR,int);
int WINAPI GetDateFormatA(LCID,DWORD,const SYSTEMTIME*,LPCSTR,LPSTR,int);
int WINAPI GetDateFormatW(LCID,DWORD,const SYSTEMTIME*,LPCWSTR,LPWSTR,int);
int WINAPI GetLocaleInfoA(LCID,LCTYPE,LPSTR,int);
int WINAPI GetLocaleInfoW(LCID,LCTYPE,LPWSTR,int);
int WINAPI GetNumberFormatA(LCID,DWORD,LPCSTR,const NUMBERFMTA*,LPSTR,int);
int WINAPI GetNumberFormatW(LCID,DWORD,LPCWSTR,const NUMBERFMTW*,LPWSTR,int);
UINT WINAPI GetOEMCP(void);
BOOL WINAPI GetStringTypeA(LCID,DWORD,LPCSTR,int,LPWORD);
BOOL WINAPI GetStringTypeW(DWORD,LPCWSTR,int,LPWORD);
BOOL WINAPI GetStringTypeExA(LCID,DWORD,LPCSTR,int,LPWORD);
BOOL WINAPI GetStringTypeExW(LCID,DWORD,LPCWSTR,int,LPWORD);
LANGID WINAPI GetSystemDefaultLangID(void);
LCID WINAPI GetSystemDefaultLCID(void);
LCID WINAPI GetThreadLocale(void);
int WINAPI GetTimeFormatA(LCID,DWORD,const SYSTEMTIME*,LPCSTR,LPSTR,int);
int WINAPI GetTimeFormatW(LCID,DWORD,const SYSTEMTIME*,LPCWSTR,LPWSTR,int);
LANGID WINAPI GetUserDefaultLangID(void);
LCID WINAPI GetUserDefaultLCID(void);
BOOL WINAPI IsDBCSLeadByte(BYTE);
BOOL WINAPI IsDBCSLeadByteEx(UINT,BYTE);
BOOL WINAPI IsValidCodePage(UINT);
BOOL WINAPI IsValidLocale(LCID,DWORD);
int WINAPI LCMapStringA(LCID,DWORD,LPCSTR,int,LPSTR,int);
int WINAPI LCMapStringW(LCID,DWORD,LPCWSTR,int,LPWSTR,int);
int WINAPI MultiByteToWideChar(UINT,DWORD,LPCSTR,int,LPWSTR,int);
BOOL WINAPI SetLocaleInfoA(LCID,LCTYPE,LPCSTR);
BOOL WINAPI SetLocaleInfoW(LCID,LCTYPE,LPCWSTR);
BOOL WINAPI SetThreadLocale(LCID);
int WINAPI WideCharToMultiByte(UINT,DWORD,LPCWSTR,int,LPSTR,int,LPCSTR,LPBOOL);

#ifdef UNICODE
#define CALINFO_ENUMPROC CALINFO_ENUMPROCW
#define LOCALE_ENUMPROC LOCALE_ENUMPROCW
#define CODEPAGE_ENUMPROC CODEPAGE_ENUMPROCW
#define DATEFMT_ENUMPROC DATEFMT_ENUMPROCW
#define TIMEFMT_ENUMPROC TIMEFMT_ENUMPROCW
typedef CURRENCYFMTW CURRENCYFMT;
typedef NUMBERFMTW NUMBERFMT;
#define CompareString CompareStringW
#define EnumCalendarInfo EnumCalendarInfoW
#define EnumSystemCodePages EnumSystemCodePagesW
#define EnumSystemLocales EnumSystemLocalesW
#define EnumTimeFormats EnumTimeFormatsW
#define FoldString FoldStringA
#define GetCurrencyFormat GetCurrencyFormatW
#define GetDateFormat GetDateFormatW
#define GetLocaleInfo GetLocaleInfoW
#define GetNumberFormat GetNumberFormatW
#define GetStringTypeEx GetStringTypeExW
#define GetTimeFormat GetTimeFormatW
#define LCMapString LCMapStringW
#define SetLocaleInfo SetLocaleInfoW
#else
#define CALINFO_ENUMPROC CALINFO_ENUMPROCA
#define LOCALE_ENUMPROC LOCALE_ENUMPROCA
#define CODEPAGE_ENUMPROC CODEPAGE_ENUMPROCA
#define DATEFMT_ENUMPROC DATEFMT_ENUMPROCA
#define TIMEFMT_ENUMPROC TIMEFMT_ENUMPROCA
typedef CURRENCYFMTA CURRENCYFMT;
typedef NUMBERFMTA NUMBERFMT;
#define CompareString CompareStringA
#define EnumCalendarInfo EnumCalendarInfoA
#define EnumSystemCodePages EnumSystemCodePagesA
#define EnumSystemLocales EnumSystemLocalesA
#define EnumTimeFormats EnumTimeFormatsA
#define FoldString FoldStringW
#define GetCurrencyFormat GetCurrencyFormatA
#define GetDateFormat GetDateFormatA
#define GetLocaleInfo GetLocaleInfoA
#define GetNumberFormat GetNumberFormatA
#define GetStringTypeEx GetStringTypeExA
#define GetTimeFormat GetTimeFormatA
#define LCMapString LCMapStringA
#define SetLocaleInfo SetLocaleInfoA
#endif
#endif
#ifdef __cplusplus
}
#endif
#endif
