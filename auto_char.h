#ifndef _AUTO_TCHAR_H
#define _AUTO_TCHAR_H

// ����BCB6��tchar.hֻ��_TCHARȴû��TCHAR������.
#if defined(__BORLANDC__) && !defined(_TCHAR_DEFINED)
typedef _TCHAR    TCHAR, *PTCHAR;
typedef _TCHAR    TBYTE, *PTBYTE;
#define _TCHAR_DEFINED
#endif    // #if defined(__BORLANDC__) && !defined(_TCHAR_DEFINED)

#endif //_AUTO_TCHAR_H
