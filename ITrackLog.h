#ifndef _TTRACKLOG_H_
#define _TTRACKLOG_H_

#include <string>

enum LOGLEVEL
{
    LL_DEBUG = 0,
    LL_INFO = 1,
    LL_EXCEPTION,
    LL_CRITICAL,
};

typedef struct strInfoMsg
{
    int nType;          //0, error; 1, info; 3, progress; 999,清空
    int nInfoIndex;     //信息索引
    int nTxtFormat;     //字体类型
    int nDelay;         //显示时间长短, 毫秒
    int nPos;           //0~100 百分比
    std::string sCustomInfo;    //自定义显示内容

    strInfoMsg(int mType, int mIndex)
    {
        nType = mType;
        nInfoIndex = mIndex;
        nTxtFormat = 0;  // CLR_PURE_WRITE;
        nDelay = 5000;
        nPos = 0;
        sCustomInfo = "";
    }
}INFOMSG, * LPINFOMSG;

class ITrackLog
{
public:

    virtual void Start() = 0;
    virtual void Stop() = 0;

    virtual void Write(const std::string& fname, const std::string& msg, int level = LL_INFO) = 0;
    virtual ~ITrackLog() {}
};

#endif // _ILTTRACKLOG_H_
