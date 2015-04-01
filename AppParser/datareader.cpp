#include "stdafx.h"
#include "datareader.h"
#include "utils.h"

DataReader::DataReader(const std::wstring& deviceName)
{
	m_sqlite = new SQLiteHelper;
	std::wstring dbName = Utils::GetExePath() + L"\\Save\\" + deviceName + L".sav";
	m_sqlite->ConnectToDatabase(dbName);
}

DataReader::~DataReader()
{
	m_sqlite->CloseDatabase();
	delete m_sqlite;
}

void DataReader::ReadBasicInfo(DEV_INFO& info)
{
	m_sqlite->Exec(L"select * from basic_info");
	m_sqlite->Step();

	info.baseDevInfo.bJailBroken = (bool)( m_sqlite->GetValue(0) );
	info.baseDevInfo.devType = (DEV_TYPE)( m_sqlite->GetValue(1) );
	info.baseDevInfo.diskUsage.ui64SysTtl = m_sqlite->GetValue(2);
	info.baseDevInfo.diskUsage.ui64SysUsed = m_sqlite->GetValue(3);
	info.baseDevInfo.diskUsage.ui64UserTtl = m_sqlite->GetValue(4);
	info.baseDevInfo.diskUsage.ui64UserUsed = m_sqlite->GetValue(5);

	std::string temp = m_sqlite->GetTextUtf8(6);
	memcpy(info.baseDevInfo.szCpuArc, temp.c_str(), temp.length()+1);

	temp = m_sqlite->GetTextUtf8(7);
	memcpy(info.baseDevInfo.szDevId, temp.c_str(), temp.length()+1);

	temp = m_sqlite->GetTextUtf8(8);
	memcpy(info.baseDevInfo.szDevModel, temp.c_str(), temp.length()+1);

	temp = m_sqlite->GetTextUtf8(9);
	memcpy(info.baseDevInfo.szDevName, temp.c_str(), temp.length()+1);

	temp = m_sqlite->GetTextUtf8(10);
	memcpy(info.baseDevInfo.szNumber, temp.c_str(), temp.length()+1);

	temp = m_sqlite->GetTextUtf8(11);
	memcpy(info.baseDevInfo.szOSVersion, temp.c_str(), temp.length()+1);

	temp = m_sqlite->GetTextUtf8(12);
	memcpy(info.baseDevInfo.szSerialNum, temp.c_str(), temp.length()+1);

	temp = m_sqlite->GetTextUtf8(13);
	memcpy(info.unDevInfo.androidDevInfo.szManu, temp.c_str(), temp.length()+1);

	temp = m_sqlite->GetTextUtf8(14);
	memcpy(info.unDevInfo.iosDevInfo.szColor, temp.c_str(), temp.length()+1);

	m_sqlite->Finalize();
}

void DataReader::ReadSmsInfo(SMS_InfoMap& sms)
{
	sms.clear();

	m_sqlite->Exec(L"select * from sms_info");

	while ( m_sqlite->Step() )
	{
		SMS_Info info;
		info.isSend = (bool)( m_sqlite->GetValue(0) );
		info.message = m_sqlite->GetText(1);
		info.name = m_sqlite->GetText(2);
		info.number = m_sqlite->GetText(3);
		info.time = m_sqlite->GetText(4);
		
		sms.insert(std::pair<std::wstring, SMS_Info>(info.number, info));
	}

	m_sqlite->Finalize();
}

void DataReader::ReadRecordInfo(RECORD_InfoMap& records)
{
	records.clear();

	m_sqlite->Exec(L"select * from record_info");

	while ( m_sqlite->Step() )
	{
		RECORD_Info info;
		info.date = m_sqlite->GetText(0);
		info.location = m_sqlite->GetText(1);
		info.name = m_sqlite->GetText(2);
		info.number = m_sqlite->GetText(3);
		info.time = m_sqlite->GetText(4);
		info.type = m_sqlite->GetText(5);

		records.insert(std::pair<std::wstring, RECORD_Info>(info.number, info));
	}

	m_sqlite->Finalize();
}

void DataReader::ReadContactInfo(CONTACT_InfoList& contacts)
{
	contacts.clear();

	m_sqlite->Exec(L"select * from contact_info");

	while ( m_sqlite->Step() )
	{
		CONTACT_Info info;
		info.address = m_sqlite->GetText(0);
		info.email = m_sqlite->GetText(1);
		info.group = m_sqlite->GetText(2);
		info.name = m_sqlite->GetText(3);
		info.number = m_sqlite->GetText(4);
		info.profession = m_sqlite->GetText(5);

		contacts.push_back(info);
	}

	m_sqlite->Finalize();
}