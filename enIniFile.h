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

    //�����ַ��������
    char MakecodeChar(char c, int key);

    //�����ַ�����
    char CutcodeChar(char c, int key);

    //����
    void Makecode(char* pstr, int* pkey);

    //����
    void Cutecode(char* pstr, int* pkey);

private:
    map<string, StrMap> m_iniMap;
    string m_sfName;
};

#endif //SKYPHY_INIFILE_H
