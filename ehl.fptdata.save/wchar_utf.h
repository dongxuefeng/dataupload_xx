#ifndef _wchar_utf_h__
#define _wchar_utf_h__

int FW2UTF8Convert(const wchar_t* a_szSrc, int a_nSrcSize, char* a_szDest, int a_nDestSize);
int FUTF82WConvert(const char* a_szSrc, wchar_t* a_szDest, int a_nDestSize);
int FW2UConvert(const wchar_t* a_szSrc, int  a_nSize, char* a_szDest, int a_nDestSize);
int FU2WConvert(const  char* a_szSrc, int a_nSize, wchar_t* a_szDest, int a_nDestSize);

#endif //#ifndef _wchar_utf_h__