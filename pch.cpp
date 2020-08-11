
#include "pch.h"

inline void swapDoubleInAsc(double& d1, double& d2)
{
    if (d1 - d2 > LT_EPSILON)
        swap(d1, d2);
}

//  LT_Equal = 0,
//  LT_GreatThan = 1,
//  LT_LessThan = -1
LT_COMPARE compDouble(double d1, double d2)
{
    if (d1 - d2 > LT_EPSILON)
        return LT_GreatThan;
    else if (d2 - d1 > LT_EPSILON)
        return LT_LessThan;

    return LT_Equal;
}

inline bool findStr(const string& src, const string& str)
{
    if (src.find(str) == string::npos) // 未找到
        return false;
    return true;
}

#ifdef WIN32
inline wstring Utf2U(const string& strUtf8)
{
    wstring wstrRet(L"");
    int nLen = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), strUtf8.length(), NULL, 0);
    if (nLen == ERROR_NO_UNICODE_TRANSLATION)
        throw "Utf8ToUnicode出错：无效的UTF-8字符串。";
    wstrRet.resize(nLen, '\0');
    MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), strUtf8.length(), (LPWSTR)wstrRet.c_str(), nLen);
    return wstrRet;
}

inline string U2Utf(const wstring& wstr)
{
    string strDes;
    if (wstr.empty())
        return strDes;
    int nLen = ::WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
    if (0 == nLen)
        return strDes;

    strDes.resize(nLen);
    ::WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.size(), (LPSTR)strDes.c_str(), nLen, NULL, NULL);
    return strDes;
}

inline string U2A(const wstring& str)
{
    string strDes;
    if (str.empty())
        return strDes;
    int nLen = ::WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.size(), NULL, 0, NULL, NULL);
    if (0 == nLen)
        return strDes;

    strDes.resize(nLen);
    ::WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.size(), (LPSTR)strDes.c_str(), nLen, NULL, NULL);
    return strDes;
}

inline wstring A2U(const string& str)
{
    wstring wstrRet;
    if (str.empty())
        return wstrRet;
    int nLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
    if (0 == nLen)
        return wstrRet;
    wstrRet.resize(nLen, '\0');
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), (LPWSTR)wstrRet.c_str(), nLen);
    return wstrRet;
}


string StringToUtf(string strValue)
{
    int nwLen = MultiByteToWideChar(CP_UTF8, 0, strValue.c_str(), -1, NULL, 0);
    wchar_t* pwBuf = new wchar_t[nwLen + 1];//加上末尾'\0'
    memset(pwBuf, 0, nwLen * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, strValue.c_str(), strValue.length(), pwBuf, nwLen);
    int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
    char* pBuf = new char[nLen + 1];
    memset(pBuf, 0, nLen + 1);
    WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
    std::string retStr = pBuf;
    delete[]pBuf;
    delete[]pwBuf;
    return retStr;
}

#else

#define Sleep(X) std::this_thread::sleep_for(std::chrono::milliseconds(X));

wstring Utf2U(const string& s)
{
    setlocale(LC_CTYPE, "zh_CN.UTF-8");
    int iWLen = mbstowcs(NULL, s.c_str(), s.length());
    wchar_t* lpwsz = new wchar_t[iWLen + 1];
    mbstowcs(lpwsz, s.c_str(), s.length());

    wstring wstr(lpwsz);
    delete[]lpwsz;
    return wstr;
}

string U2A(const wstring& ws)
{
    //string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";  

    //setlocale(LC_ALL, "chs");

    //const wchar_t* _Source = ws.c_str();
    //size_t _Dsize = 2 * ws.size() + 1;
    //char *_Dest = new char[_Dsize];
    //std::memset(_Dest, 0, _Dsize);
    //wcstombs(_Dest, _Source, _Dsize);
    //string result = _Dest;
    //delete[]_Dest;

    //setlocale(LC_ALL, curLocale.c_str());
    //  return result;

    string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";  

    setlocale(LC_ALL, "zh_CN.UTF-8");

    const wchar_t* _Source = ws.c_str();
    size_t _Dsize = 3 * ws.size() + 1;
    char* _Dest = new char[_Dsize];
    std::memset(_Dest, 0, _Dsize);
    wcstombs(_Dest, _Source, _Dsize);
    string result = _Dest;
    delete[]_Dest;

    setlocale(LC_ALL, curLocale.c_str());

    return result;
}

wstring A2U(const string& s)
{
    //setlocale(LC_ALL, "chs");

    //const char* _Source = s.c_str();
    //size_t _Dsize = s.size() + 1;
    //wchar_t *_Dest = new wchar_t[_Dsize];
    //wmemset(_Dest, 0, _Dsize);
    //mbstowcs(_Dest, _Source, _Dsize);
    //wstring result = _Dest;
    //delete[]_Dest;

    //setlocale(LC_ALL, "C");

    //return result;
    setlocale(LC_CTYPE, "zh_CN.UTF-8");
    int iWLen = mbstowcs(NULL, s.c_str(), s.length());
    wchar_t* lpwsz = new wchar_t[iWLen + 1];
    mbstowcs(lpwsz, s.c_str(), s.length());

    wstring wstr(lpwsz);
    delete[]lpwsz;
    return wstr;
}

string U2Utf(const wstring& ws)
{
    string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";  

    setlocale(LC_ALL, "zh_CN.UTF-8");

    const wchar_t* _Source = ws.c_str();
    size_t _Dsize = 3 * ws.size() + 1;
    char* _Dest = new char[_Dsize];
    std::memset(_Dest, 0, _Dsize);
    wcstombs(_Dest, _Source, _Dsize);
    string result = _Dest;
    delete[]_Dest;

    setlocale(LC_ALL, curLocale.c_str());

    return result;
}

#endif
