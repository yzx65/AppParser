#include "stdafx.h"
#include "keychainparser.h"
#include "utils.h"

#include <QFile>
#include <QTextStream>

#include "sqliteHelper.h"

KeyChainParser::KeyChainParser( const std::wstring& keyChainFile )
	: m_keyChainFile(keyChainFile)
{

}

KeyChainParser::~KeyChainParser()
{

}

bool KeyChainParser::Start()
{
	m_keyChainFile += L"\\keychain.csv";

	if ( !Utils::FileExist(m_keyChainFile) )
	{
		Utils::__TRACE(L"[KeyChainParser] Key chain file not found. [%s] \r\n", m_keyChainFile.c_str());
		return false;
	}

	QFile file(Utils::wtoq(m_keyChainFile));

	if ( !file.open(QIODevice::ReadOnly) )
		return false;

	QTextStream stream(&file);
	stream.setCodec("utf-8");
	QString line = stream.readLine();

	for ( ; !stream.atEnd(); line = stream.readLine() )
	{
		if ( !line.contains(';') )
			continue;

		KeyChainInfo info;
		info.service = Utils::qtos(line.section(';', 0, 0));
		info.serviceName = Utils::qtos(Utils::GetConfigValue("keychain", "type", "key", Utils::stoq(info.service), "label"));

		if ( info.serviceName.empty() )
		{
			info.prefix = info.service;
			info.service = "ÆäËû";
		}

		info.name = Utils::qtos(line.section(';', 1, 1));

		if ( info.service == "com.apple.account.SMTP.password" 
			|| info.service == "com.apple.account.IMAP.password" )
			ProcessEmailInfo(info);

		info.password = Utils::qtos(line.section(';', 2, 2));

		Utils::__TRACE("[KeyChainParser] : %s %s %s %s\r\n", info.service.c_str(), info.serviceName.c_str(), info.name.c_str(), info.password.c_str());
		
		m_keyChainList.push_back(info);
	}

	return true;
}

void KeyChainParser::ProcessEmailInfo(KeyChainInfo& info)
{
	info.service = "email";
	SQLiteHelper sqlite;
	std::wstring keychainDir = m_keyChainFile.substr(0, m_keyChainFile.rfind(L'\\'));
	std::wstring accountDb = keychainDir;
	accountDb += L"\\HomeDomain\\Library\\Accounts\\Accounts3.sqlite";

	sqlite.ConnectToDatabase(accountDb);

	char sqlCmd[1024] = {0};
	wsprintfA(sqlCmd, "select ZACCOUNTDESCRIPTION from ZACCOUNT where ZIDENTIFIER = '%s'", info.name.c_str());

	sqlite.Exec(sqlCmd);

	if ( sqlite.Step() )
		info.name = sqlite.GetTextUtf8(0);
	
	sqlite.Finalize();

	sqlite.CloseDatabase();
}

KeyChainInfo* KeyChainParser::GetFirstKeyChainInfo()
{
	if ( m_keyChainList.empty() )
		return NULL;

	return & ( *( m_cursor = m_keyChainList.begin() ) );
}

KeyChainInfo* KeyChainParser::GetNextKeyChainInfo()
{
	++m_cursor;

	if ( m_cursor == m_keyChainList.end() )
		return NULL;

	return &(*m_cursor);
}

void KeyChainParser::Free()
{
	m_keyChainList.clear();
}
