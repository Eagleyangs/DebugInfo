#pragma once
#include <thread>
#include <string>
#include <deque>
#include <mutex>
#include <string>
#include "ITrackLog.h"

using namespace std;

class TextLog : public ITrackLog
{
public:
    static TextLog& Singleton();
    ~TextLog();

    virtual void Start();
    virtual void Stop();

    virtual void Write(const std::string& fname, const std::string& msg, int level = LOGLEVEL::LL_INFO);

private:
    struct LogItem
    {
        LogItem(const string& f = "", const string& m = "", int lv = LOGLEVEL::LL_INFO)
            :file(f), message(m), level(lv)
        {}
        string  file;
        string  message;
        int     level;
    };

    TextLog(int lev = LOGLEVEL::LL_INFO);
    bool PopOneLogItem(LogItem& item);
    void ProcRun();

private:
    bool                m_RunFlag;
    std::thread         m_thrdLog;

    int                 m_filterLev;
    std::deque<LogItem> m_logQue;
    mutable std::mutex  m_logMutex;
};
