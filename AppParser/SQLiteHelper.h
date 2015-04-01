#ifndef SQLITEHELPER_H
#define SQLITEHELPER_H

#include <string>
#include <map>
#include "sqlite3.h"

class SQLiteHelper
{
public:
	SQLiteHelper();
	bool ConnectToDatabase(const std::wstring& fileName);
	void CloseDatabase();

	bool Exec(const std::wstring& sql);
	bool Exec(const std::string& sql);
	bool Step();
	const char* GetData(int column, __int64* size);
	std::wstring GetText(int column);
	std::string GetTextUtf8(int column);
	__int64 GetValue(int column);
	bool Finalize();

private:
	sqlite3* m_sqlite;
	sqlite3_stmt* m_state;
};

#endif // SQLITEHELPER_H