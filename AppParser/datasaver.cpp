#include "stdafx.h"
#include "datasaver.h"
#include "utils.h"

#include <sstream>

DataSaver::DataSaver( const std::wstring& deviceName )
{
	m_sqlite = new SQLiteHelper;
	std::wstring dbName = Utils::GetExePath() + L"\\Save\\" + deviceName + L".sav";
	DeleteFileW(dbName.c_str());
	m_sqlite->ConnectToDatabase(dbName);

}

DataSaver::~DataSaver()
{
	m_sqlite->CloseDatabase();
	delete m_sqlite;
}

void DataSaver::SaveBasicInfo( DEV_INFO& devInfo )
{
	char sqlCmd[2048] = {0};
	wsprintfA(sqlCmd, "create table basic_info("
		"bJailBroken INT, devType INT, ui64SysTtl INT, ui64SysUser INT, "
		"ui64UserTtl INT, ui64UserUsed INT, szCpuArc TEXT, szDevId TEXT, "
		"szDevModel TEXT, szDevName TEXT, szNumber TEXT, szOSVersion TEXT, "
		"szSerialNum TEXT, szManu TEXT, szColor TEXT )");

	m_sqlite->Exec(sqlCmd);
	m_sqlite->Step();
	m_sqlite->Finalize();

	sprintf(sqlCmd, "insert into basic_info values(%d, %d, %I64u, %I64u, %I64u, %I64u, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
		devInfo.baseDevInfo.bJailBroken,
		devInfo.baseDevInfo.devType,
		devInfo.baseDevInfo.diskUsage.ui64SysTtl,
		devInfo.baseDevInfo.diskUsage.ui64SysUsed,
		devInfo.baseDevInfo.diskUsage.ui64UserTtl,
		devInfo.baseDevInfo.diskUsage.ui64UserUsed,
		devInfo.baseDevInfo.szCpuArc,
		devInfo.baseDevInfo.szDevId,
		devInfo.baseDevInfo.szDevModel,
		devInfo.baseDevInfo.szDevName,
		devInfo.baseDevInfo.szNumber,
		devInfo.baseDevInfo.szOSVersion,
		devInfo.baseDevInfo.szSerialNum,
		devInfo.unDevInfo.androidDevInfo.szManu,
		devInfo.unDevInfo.iosDevInfo.szColor);

	m_sqlite->Exec(sqlCmd);
	m_sqlite->Step();
	m_sqlite->Finalize();
}

void DataSaver::SaveSmsInfo( SMS_InfoMap& sms )
{
	// use transaction to comit multi sql commands;
	SMS_Info* info;
	m_sqlite->Exec(L"create table sms_info(sms_isSend INT, sms_message TEXT, sms_name TEXT, sms_number TEXT, sms_time TEXT)");
	m_sqlite->Step();
	m_sqlite->Finalize();

	m_sqlite->Exec(L"begin;");
	m_sqlite->Step();
	m_sqlite->Finalize();

	for ( SMS_InfoMap::iterator it = sms.begin(); it != sms.end(); ++it )
	{
		std::wstringstream sqlCmd;
		sqlCmd << L"insert into sms_info values("
			   << (int)( (*it).second.isSend ) << ","
			   << L"'" << (*it).second.message << L"',"
			   << L"'" << (*it).second.name << L"',"
			   << L"'" << (*it).second.number << L"',"
			   << L"'" << (*it).second.time << L"'" << L");\n";

		m_sqlite->Exec(sqlCmd.str());
		m_sqlite->Step();
		m_sqlite->Finalize();
	}

	m_sqlite->Exec(L"commit;");
	m_sqlite->Step();
	m_sqlite->Finalize();
}

void DataSaver::SaveRecordInfo( RECORD_InfoMap& records )
{
	// use transaction to comit multi sql commands;
	m_sqlite->Exec(L"create table record_info"
		L"(record_date TEXT, record_location TEXT, record_name TEXT, record_number TEXT, record_time TEXT, record_type TEXT)");
	m_sqlite->Step();
	m_sqlite->Finalize();

	m_sqlite->Exec(L"begin;");
	m_sqlite->Step();
	m_sqlite->Finalize();

	for ( RECORD_InfoMap::iterator it = records.begin(); it != records.end(); ++it )
	{
		std::wstringstream sqlCmd;
		sqlCmd << L"insert into record_info values("
			<< L"'" << (*it).second.date << "',"
			<< L"'" << (*it).second.location << L"',"
			<< L"'" << (*it).second.name << L"',"
			<< L"'" << (*it).second.number << L"',"
			<< L"'" << (*it).second.time << L"'," 
			<< L"'" << (*it).second.type << L"'" << L");\n";

		m_sqlite->Exec(sqlCmd.str());
		m_sqlite->Step();
		m_sqlite->Finalize();
	}

	m_sqlite->Exec(L"commit;");
	m_sqlite->Step();
	m_sqlite->Finalize();
}

void DataSaver::SaveContactInfo( const CONTACT_InfoList& contact )
{
	// use transaction to comit multi sql commands;
	m_sqlite->Exec(L"create table contact_info"
		L"(contact_address TEXT, contact_email TEXT, contact_group TEXT, contact_name TEXT, contact_number TEXT, contact_profession TEXT)");
	m_sqlite->Step();
	m_sqlite->Finalize();

	m_sqlite->Exec(L"begin;");
	m_sqlite->Step();
	m_sqlite->Finalize();

	for ( CONTACT_InfoList::const_iterator it = contact.begin(); it != contact.end(); ++it )
	{
		std::wstringstream sqlCmd;
		sqlCmd << L"insert into contact_info values("
			<< L"'" << it->address << "',"
			<< L"'" << it->email << L"',"
			<< L"'" << it->group << L"',"
			<< L"'" << it->name << L"',"
			<< L"'" << it->number << L"'," 
			<< L"'" << it->profession << L"'" << L");\n";

		m_sqlite->Exec(sqlCmd.str());
		m_sqlite->Step();
		m_sqlite->Finalize();
	}

	m_sqlite->Exec(L"commit;");
	m_sqlite->Step();
	m_sqlite->Finalize();
}
