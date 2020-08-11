// file debug.h 
/**
* 打日志 可在 DebugView中显示 2019.12.8 
**/
#ifndef __DEBUG_H__
#define __DEBUG_H__

//// 关闭警告
#pragma warning(disable:4996)
#pragma warning(disable:4018)
//// 关闭警告
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdarg.h>
#include <windows.h>

using namespace std;

#ifdef _DEBUG

#ifdef _DEBUG
#define OUTPUT(arg) {fprintf(stdout, "[%s] [%s] [%s/%s:%d] : [%s]\n", __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__, arg);}
#endif

//#define PRINTFILEINFO "file = %s, fun = %s, name = %s, line = %d,\t ", __FILE__, __FUNCTION__, __FUNCDNAME__, __LINE__
#define PRINTFILEINFO "file = %s, function = %s, line = %d,\t ", __FILE__, __FUNCTION__, __LINE__
#define PRINTDATEINFO "date = %s, time = %s,\t ", __DATE__ , __TIME__

void _trace(char *fmt, ...);

#define ASSERT(x) {if(!(x)) _asm{int 0x03}}
#define VERIFY(x) {if(!(x)) _asm{int 0x03}}  // 译注：为调试版本时产生中断有效

#else
#define ASSERT(x)
#define VERIFY(x) x							 // 译注：为发行版本时不产生中断
#endif

#ifdef _DEBUG
#define TRACE _trace

#else
inline void _trace(LPCTSTR fmt, ...) { }
#define TRACE  1 ? (void)0 : _trace
#endif

#ifdef _DEBUG
void _trace(char *fmt, ...)
{
	char out[2048] = {};
	va_list body;
	va_start(body, fmt);
	vsprintf(out, fmt, body);     // 译注：格式化输入的字符串 fmtt
	va_end(body);                 //       到输出字符串 ou
	OutputDebugString(out);       // 译注：输出格式化后的字符串到调试器
}
#endif

#endif // __DEBUG_H__


/*************************
Usage
	TRACE(PRINTFILEINFO); // file position info
	TRACE(PRINTDATEINFO); // date info
	TRACE("file = %s, fun  = %s, name = %s, line = %d", __FILE__, __FUNCTION__, __FUNCDNAME__, __LINE__); // loginfo
*************************/
