#ifndef DATASAVER_H
#define DATASAVER_H

#include "CommonDef.h"
#include "ParserInterface.h"
#include "datastructure.h"
#include "SQLiteHelper.h"

class DataSaver
{
public:

	DataSaver(const std::wstring& deviceName);
	~DataSaver();

	void SaveBasicInfo(DEV_INFO& devInfo);
	void SaveSmsInfo(SMS_InfoMap& sms);
	void SaveRecordInfo(RECORD_InfoMap& records);
	void SaveContactInfo(const CONTACT_InfoList& contact);

private:
	SQLiteHelper* m_sqlite;
};

#endif // DATASAVER_H