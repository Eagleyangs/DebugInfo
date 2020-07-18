#include "../pch.h"
#include "TextLog.h"
#ifdef WIN32
#include "XZip.h"
#endif
#include <iostream> 
#include <fstream>
#include <time.h>
#include <stdio.h> 

TextLog::TextLog(int lev)
{
    m_filterLev = lev;
    m_RunFlag = false;
}

bool TextLog::PopOneLogItem(LogItem& item)
{
    std::lock_guard<std::mutex> lock(m_logMutex);
    if (!m_logQue.empty())
    {
        item = m_logQue.front();
        m_logQue.pop_front();
        return true;
    }
    return false;
}

void TextLog::ProcRun()
{
#ifdef WIN32
    ::CreateDirectory(L"d:/log/", 0);
#else
    mkdir("log", S_IRWXU | S_IRWXG | S_IROTH);
#endif
    for (unsigned long tick = 0; m_RunFlag; ++tick)
    {
        LogItem item;
        if (PopOneLogItem(item))
        {
            string fname = "D://log/" + item.file;
            wstring wfname = A2U(fname);
            ofstream log(fname, ios::app);
            time_t now;
            time(&now);
            tm _tm;
            char mbstr[100];

            localtime_s(&_tm, &now);
            strftime(mbstr, sizeof(mbstr), "%F %T", &_tm);
            log << mbstr << ' ' << item.message;
#ifdef WIN32
            long long pos = log.tellp();
            if (pos > 10 * 1024 * 1024)
            {
                log.close();

                string::size_type pos = fname.find('.', 0);
                if (pos != string::npos)
                    fname.erase(pos);
                wstring zfname = A2U(fname + to_string(now) + ".zip");
                HZIP hz = CreateZip((void*)zfname.c_str(), 0, ZIP_FILENAME);
                wstring zname = A2U(item.file);
                ZRESULT rst = ZipAdd(hz, zname.c_str(), (void*)wfname.c_str(), 0, ZIP_FILENAME);
                CloseZip(hz);

                ::DeleteFile(wfname.c_str());
            }
#endif
        }
        Sleep(10);
    }
}


TextLog& TextLog::Singleton()
{
    static TextLog log;
    return log;
}

TextLog::~TextLog()
{
}

void TextLog::Start()
{
    m_RunFlag = true;
    m_thrdLog = std::thread(&TextLog::ProcRun, std::ref(*this));
}

void TextLog::Stop()
{
    m_RunFlag = false;

    if (m_thrdLog.joinable())
    {
        m_thrdLog.join();
    }
}

void TextLog::Write(const string& fname, const string& msg, int level)
{
    if (level >= m_filterLev)
    {
        std::lock_guard<std::mutex> lock(m_logMutex);
        m_logQue.emplace_back(fname, msg, level);
    }
}
