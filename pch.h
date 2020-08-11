#ifndef PCH_H
#define PCH_H

//#define BUGTEST // test
//#define TESTDemo // demo test

//#ifdef BUGTEST
//#define OUTPUT(arg) {fprintf(stdout, "[%s] [%s] [%s/%s:%d] : [%s]\n", __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__, arg);}
//#endif

#ifdef WIN32
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#else

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define __FUNCDNAME__ __func__
#define Sleep(X) std::this_thread::sleep_for(std::chrono::milliseconds(X));
#endif

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <thread>
#include <mutex>
#include <functional>
#include <iterator>
#include <cassert>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <string>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <climits>
#include <atomic>
#include <chrono>
#include <future>
#include <functional>

#include <signal.h>
#include <locale.h>

#include <stdint.h>
#include "json/json.h"

using namespace std;

#define LT_EPSILON 0.0001

#ifdef WIN32
string StringToUtf(string strValue);
#endif //WIN32

extern string U2A(const wstring& ws);
extern wstring A2U(const string& s);
extern wstring Utf2U(const string& s);
extern string U2Utf(const wstring& ws);
extern bool findStr(const string& src, const string& str);
void swapDoubleInAsc(double& d1, double& d2);

enum LT_COMPARE
{
    LT_Equal = 0,
    LT_GreatThan = 1,
    LT_LessThan = -1
};
LT_COMPARE compDouble(double d1, double d2);

// 比较数字在一定范围内
template<class T>
bool NumInArea(const T& begin, const T& end, const T& num)
{
    return (num >= begin && num <= end);
}

#endif //PCH_H
