#ifndef SKYPHY_INIFILE_H
#define SKYPHY_INIFILE_H

#include <string>
#include <map>
using std::string;
using std::map;
typedef map<string, string>		StrMap;

class IniFile
{
public:
    IniFile();
    ~IniFile();
	
	bool Load(const char* fname);
	string GetSetting(const char* sec, const char* key, const char* def_val = "");
	bool SetSetting(const char* sec, const char* key, const char* val);
	bool Save(const char* fname);

private:
	map<string, StrMap>	m_iniMap;
};

#endif //SKYPHY_INIFILE_H
