#include "stdafx.h"
#include "SQLiteHelper.h"

#include <stdio.h>
#include <string>

#include "utils.h"

#pragma comment(lib, "SqliteLib.lib")

SQLiteHelper::SQLiteHelper()
	: m_sqlite(NULL)
{

}

bool SQLiteHelper::ConnectToDatabase(const std::wstring& fileName)
{
	int errNo = 0;

	if ( SQLITE_OK != (errNo = sqlite3_open16((void*)fileName.c_str(), &m_sqlite)) )
	{
		Utils::__TRACE(
			L"[SQLiteHelper] Open database file failed. [%s] [%d]\r\n", 
			fileName.c_str(), 
			errNo);
		return false;
	}

	return true;
}

void SQLiteHelper::CloseDatabase()
{
	if ( m_sqlite )
	{
		sqlite3_close(m_sqlite);
		m_sqlite = NULL;
	}
}

bool SQLiteHelper::Exec(const std::wstring& sql)
{
	int errNo = sqlite3_prepare16(
		m_sqlite,
		(const void*)sql.c_str(), 
		2*sql.length(),
		&m_state,
		NULL);

	if ( SQLITE_OK != errNo )
	{
		Utils::__TRACE(
			L"[SQLiteHelper] Execute sql failed. [%s] [%d]\r\n", 
			sql.c_str(), 
			errNo);
		return false;
	}

	return true;
}

bool SQLiteHelper::Exec(const std::string& sql)
{
	int errNo = sqlite3_prepare(
		m_sqlite,
		sql.c_str(), 
		sql.length(),
		&m_state,
		NULL);

	if ( SQLITE_OK != errNo )
	{
		Utils::__TRACE(
			"[SQLiteHelper] Execute sql failed. [%s] [%d]\r\n", 
			sql.c_str(), 
			errNo);
		return false;
	}

	return true;
}

bool SQLiteHelper::Step()
{
	int ret = sqlite3_step(m_state);
	
	if ( SQLITE_DONE == ret )
		return false;

	if ( SQLITE_ROW != ret )
	{
		Utils::__TRACE(
			L"[SQLiteHelper] Step sql failed. [%d]\r\n", 
			ret);
		return false;
	}

	return true;
}

const char* SQLiteHelper::GetData(int column, __int64* size)
{
	*size = sqlite3_column_bytes(m_state, column);
	const void* data = sqlite3_column_blob(m_state, column);
	return (const char*)sqlite3_column_blob(m_state, column);
}

std::wstring SQLiteHelper::GetText(int column)
{
	const void* data = sqlite3_column_text16(m_state, column);

	if ( NULL == data )
		return L"";

	return std::wstring(static_cast<const wchar_t*>(data));
}

std::string SQLiteHelper::GetTextUtf8(int column)
{
	const unsigned char* data = sqlite3_column_text(m_state, column);

	if ( NULL == data )
		return "";

	return std::string((const char*)(data));
}

__int64 SQLiteHelper::GetValue(int column)
{
	return sqlite3_column_int64(m_state, column);
}

bool SQLiteHelper::Finalize()
{
	int errNo = sqlite3_finalize(m_state);

	if ( SQLITE_OK != errNo )
	{
		Utils::__TRACE(
			L"[SQLiteHelper] Finalize state failed. [%d]\r\n", 
			errNo);
		return false;
	}

	return true;
}