#ifndef KEYCHAINPARSER_H
#define KEYCHAINPARSER_H

#include <Windows.h>
#include <string>
#include <list>

#include "datastructure.h"

typedef std::list<KeyChainInfo> KeyChainList;

class KeyChainParser
{
public:
	KeyChainParser(const std::wstring& keyChainFile);
	~KeyChainParser();

public:
	bool Start();
	KeyChainInfo* GetFirstKeyChainInfo();
	KeyChainInfo* GetNextKeyChainInfo();
	void Free();

private:
	void ProcessEmailInfo(KeyChainInfo& info);

private:
	std::wstring m_keyChainFile;
	KeyChainList m_keyChainList;
	KeyChainList::iterator m_cursor;
};

#endif // KEYCHAINPARSER_H