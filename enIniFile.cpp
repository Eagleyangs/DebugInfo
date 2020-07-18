#include "IniFile.h"
#include <iostream>
#include <fstream>
#include <minmax.h>

using namespace std;

int s_skey[] = { 1,2,3,4,5 };//加密字符

struct NotSpace
{
    bool operator()(const char& ch) { return ch != ' ' && ch != '\t' && ch != '\r'; }
};

void StrTrim(string& str)
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), NotSpace()));
    str.erase(std::find_if(str.rbegin(), str.rend(), NotSpace()).base(), str.end());
}

bool IniFile::Load(const char* fname)
{
    ifstream    in(fname);
    if (!in)
        return false;

    m_iniMap.clear();

    string  line;
    string  section("");
    while (getline(in, line))
    {
        string str(line.begin(), find(line.begin(), line.end(), '#'));
        StrTrim(str);
        if (str.empty())
            continue;
        if (str[0] == '[')
        {
            auto it = find(str.begin(), str.end(), ']');
            if (it != str.end())
            {
                section.assign(str.begin() + 1, it);
                cout << '[' << section << ']' << endl;
            }
            continue;
        }
        string::iterator it = find(str.begin(), str.end(), '=');
        if (it == str.end())
            continue;
        string  key(str.begin(), it);
        string  val(++it, str.end());
        StrTrim(key);
        StrTrim(val);
        if (!key.empty())
        {
            cout << section << '.' << key << '=' << val << endl;
            m_iniMap[section].insert(make_pair(key, val));
        }
    }

    m_sfName = fname;
    return true;
}

string IniFile::GetSetting(const char* sec, const char* key, const char* def_val, bool bEnc /*= false*/)
{
    auto it = m_iniMap.find(sec);
    if (it != m_iniMap.end())
    {
        auto kv = it->second.find(key);
        if (kv != it->second.end())
        {
            if (bEnc)
            {
                char pc[64] = { 0 };
                memset(pc, 0, sizeof(char) * 64);
                memcpy(&pc, kv->second.c_str(), min(sizeof(char) * 64, kv->second.length()));
                Cutecode(pc, s_skey);
                string s(pc);

                return s;
            }
            else
            {
                return kv->second;
            }
        }
    }

    return string(def_val);
}

bool IniFile::SetSetting(const char* sec, const char* key, const char* val, bool bEnc /*= false*/)
{
    auto it = m_iniMap.find(sec);
    if (it != m_iniMap.end())
    {
        auto kv = it->second.find(key);
        if (kv != it->second.end())
        {
            if (bEnc)
            {
                char* pc = new char[64];
                ZeroMemory(pc, sizeof(char) * 64);
                memcpy(pc, val, min(sizeof(char) * 64, std::strlen(val)));
                Makecode(pc, s_skey);
                kv->second = pc;
                delete[]pc;
            }
            else
            {
                kv->second = val;
            }
            return true;
        }
    }
    return false;
}

bool IniFile::Save(const char* fname)
{
    if (fname == nullptr) fname = m_sfName.c_str();

    ofstream out(fname);
    if (!out)
        return false;

    for (auto& sm : m_iniMap)
    {
        out << '[' << sm.first << ']' << std::endl;
        for (auto& kv : sm.second)
        {
            out << kv.first << '=' << kv.second << std::endl;
        }
    }

    return true;
}

//单个字符异或运算
char IniFile::MakecodeChar(char c, int key) {
    return c = c ^ key;
}
//单个字符解密
char IniFile::CutcodeChar(char c, int key) {
    return c ^ key;
}


//加密
void IniFile::Makecode(char* pstr, int* pkey) {
    int len = strlen(pstr);//获取长度
    for (int i = 0; i < len; i++)
        *(pstr + i) = MakecodeChar(*(pstr + i), pkey[i % 5]);
}

//解密
void IniFile::Cutecode(char* pstr, int* pkey) {
    int len = strlen(pstr);
    for (int i = 0; i < len; i++)
        *(pstr + i) = CutcodeChar(*(pstr + i), pkey[i % 5]);
}
