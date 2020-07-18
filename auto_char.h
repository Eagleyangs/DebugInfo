#ifndef _AUTO_TCHAR_H
#define _AUTO_TCHAR_H

// 修正BCB6的tchar.h只有_TCHAR却没有TCHAR的问题.
#if defined(__BORLANDC__) && !defined(_TCHAR_DEFINED)
typedef _TCHAR    TCHAR, *PTCHAR;
typedef _TCHAR    TBYTE, *PTBYTE;
#define _TCHAR_DEFINED
#endif    // #if defined(__BORLANDC__) && !defined(_TCHAR_DEFINED)

#endif //_AUTO_TCHAR_H
