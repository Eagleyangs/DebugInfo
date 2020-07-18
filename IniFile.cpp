#include "../pch.h"
#include "IniFile.h"

struct NotSpace
{
	bool operator()(const char& ch) { return ch != ' ' && ch != '\t' && ch != '\r'; }
};

void StrTrim(string& str)
{
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), NotSpace()));
	str.erase(std::find_if(str.rbegin(), str.rend(), NotSpace()).base(), str.end());
}

using namespace std;

IniFile::IniFile()
{
	
}

IniFile::~IniFile()  
{
	
}

bool IniFile::Load(const char* fname)
{
	ifstream	in(fname);
	if (!in)
		return false;

	string	line;
	string	section("");
	while (getline(in, line))
	{
		string str( line.begin(), find(line.begin(), line.end(), '#'));
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
		string	key(str.begin(), it);
		string	val(++it, str.end());
		StrTrim(key);
		StrTrim(val);
		if (!key.empty())
		{
			cout << section << '.' << key << '=' << val << endl;
			m_iniMap[section].insert( make_pair(key, val) );
		}
	} 

	return true;
}

string IniFile::GetSetting(const char* sec, const char* key, const char* def_val)
{
	auto it = m_iniMap.find(sec);
	if (it != m_iniMap.end())
	{
		auto kv = it->second.find(key);
		if (kv != it->second.end())
			return kv->second;
	}

	return string(def_val);
}

bool IniFile::SetSetting(const char* sec, const char* key, const char* val)
{
	auto it = m_iniMap.find(sec);
	if (it != m_iniMap.end())
	{
		auto kv = it->second.find(key);
		if (kv != it->second.end())
		{
			kv->second = val;
			return true;
		}
	}
	return false;
}
bool IniFile::Save(const char* fname)
{
	ofstream out(fname);
	if (!out)
		return false;
	
	for (auto& sm : m_iniMap)
	{
		out << '[' << sm.first << ']' << std::endl;
		for (auto& kv : sm.second)
		{
			cout << kv.first << '=' << kv.second << std::endl;
		}
	}

	return true;
}

