#ifndef DATAREADER_H
#define DATAREADER_H

#include "CommonDef.h"
#include "ParserInterface.h"
#include "datastructure.h"

#include "SQLiteHelper.h"

class DataReader
{
public:
	DataReader(const std::wstring& deviceName);
	~DataReader();

	void ReadBasicInfo(DEV_INFO& info);
	void ReadSmsInfo(SMS_InfoMap& sms);
	void ReadRecordInfo(RECORD_InfoMap& records);
	void ReadContactInfo(CONTACT_InfoList& contacts);

private:
	SQLiteHelper* m_sqlite;
};

#endif // DATAREADER_H