#pragma once
#include <thread>
#include <string>
#include <deque>
#include <mutex>
#include <string>
#include "ILtTrackLog.h"

using namespace std;

enum LOGLEVEL
{
    LL_DEBUG = 0,
    LL_INFO = 1,
    LL_EXCEPTION,
    LL_CRITICAL,
};
class TextLog : public ILtTrackLog
{
public:
    static TextLog& Singleton();
    ~TextLog();

    virtual void Start();
    virtual void Stop();

    virtual void Write(const std::string& fname, const std::string& msg, int level = LTLL_INFO);

private:
    struct LogItem
    {
        LogItem(const string& f = "", const string& m = "", int l = LL_INFO)
            :file(f), message(m), level(l)
        {}
        string  file;
        string  message;
        int     level;
    };

    TextLog(int lev = LL_INFO);
    bool PopOneLogItem(LogItem& item);
    void ProcRun();

private:
    bool                m_RunFlag;
    std::thread         m_thrdLog;

    int                 m_filterLev;
    std::deque<LogItem> m_logQue;
    mutable std::mutex  m_logMutex;
};
