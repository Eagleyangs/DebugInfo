#ifndef SKYPHY_INIFILE_H
#define SKYPHY_INIFILE_H

#include <string>
#include <map>
using std::string;
using std::map;
typedef map<string, string>     StrMap;

class IniFile
{
public:
    IniFile() {}
    ~IniFile() {}

    bool Load(const char* fname);
    string GetSetting(const char* sec, const char* key, const char* def_val = "", bool bEnc = false);
    bool SetSetting(const char* sec, const char* key, const char* val, bool bEnc = false);
    bool Save(const char* fname);

private:

    //单个字符异或运算
    char MakecodeChar(char c, int key);

    //单个字符解密
    char CutcodeChar(char c, int key);

    //加密
    void Makecode(char* pstr, int* pkey);

    //解密
    void Cutecode(char* pstr, int* pkey);

private:
    map<string, StrMap> m_iniMap;
    string m_sfName;
};

#endif //SKYPHY_INIFILE_H
