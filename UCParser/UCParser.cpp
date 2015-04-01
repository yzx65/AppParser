// UCParser.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "UCParser.h"
#include "utils.h"
#include <list>
#include <vector>

#pragma comment(lib, "shell32.lib")

BookmarkList g_bookmarks;
HistoryList g_historys;

BookmarkList::iterator g_iBookmark;
HistoryList::iterator g_iHistory;

bool UC_Start_iOS(const wchar_t* dataPath)
{
	return false;
}

bool GetXorKey(const std::wstring& zipToolPath, char* key)
{
	HANDLE hf = CreateFile(zipToolPath.c_str(), FILE_GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( INVALID_HANDLE_VALUE == hf )
		return false;

	SetFilePointer(hf, 0x2020, NULL, FILE_BEGIN);

	DWORD readed = 0;
	ReadFile(hf, key, 8, &readed, NULL);
	CloseHandle(hf);

	return (readed == 8); 
}

bool GetXorKeyFromXml(const std::wstring& xmlPath, char* key)
{
	HANDLE hf = CreateFile(xmlPath.c_str(), FILE_GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( INVALID_HANDLE_VALUE == hf )
		return false;

	char text[9] = "<?xml ve";
	char buf[8] = {0};

	DWORD readed = 0;
	ReadFile(hf, buf, 8, &readed, NULL);
	CloseHandle(hf);

	for ( int i = 0; i < 8; ++i )
		key[i] = text[i] ^ buf[i];

	return (readed == 8);
}

std::string XorDecrypt(const char* src, int srcLen, const char* key)
{
	int keyLen = strlen(key);
	char* buffer = new char[srcLen];
	memset(buffer, 0, srcLen);

	for ( int i = 0, decode = 0; i < srcLen; ++i, ++decode )
	{
		buffer[i] = src[i] ^ key[decode%keyLen];
	}

	std::string result = buffer;
	delete [] buffer;
	return result;
}

// 0 == history 1 == bookmark
void DecryptFile(const std::wstring& file, char* key, int type)
{
	HANDLE hf = CreateFileW(file.c_str(), FILE_GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( INVALID_HANDLE_VALUE == hf )
		return;

	DWORD fileSize = GetFileSize(hf, NULL);
	char* buffer = new char[fileSize];
	DWORD readed = 0;

	ReadFile(hf, buffer, fileSize, &readed, NULL);
	std::string result = XorDecrypt(buffer, fileSize, key);

	int pos = 0;
	int lastPos = 0;

	std::vector<std::string> lines;

	while ( ( pos = result.find('\r', pos) ) != std::string::npos )
	{
		lines.push_back(result.substr(lastPos, pos-lastPos));
		pos += 2;
		lastPos = pos;
	}

	int count = lines.size();

	int step, nameIndex, urlIndex;

	if ( type == 0 )
	{
		step = 3;
		nameIndex = 0;
		urlIndex = 1;
	}
	else
	{
		step = 7;
		nameIndex = 1;
		urlIndex = 2;
	}

	for ( int i = 1; i < count; i += step )
	{
		if ( i + step-1 >= count )
			break;

		BrowseBasicInfo info;
		info.name = lines[i+nameIndex];
		info.url = lines[i+urlIndex];

		if ( info.url.empty() || info.name.empty() )
			continue;

		if ( 0 == type )
		{
			const char* timeStr = lines[i+2].c_str() + 2;
			info.time = GetTimeStrFromLongLong(_atoi64(timeStr));
		}

		if ( 0 == type )
			g_historys.push_back(info);
		else
			g_bookmarks.push_back(info);
	}

	CloseHandle(hf);
	delete [] buffer;
}

bool UC_Start_Android(const wchar_t* dataPath)
{
	std::wstring dirPath = std::wstring(dataPath) + L"\\com.UCMobile";
	std::wstring archivePath = std::wstring(dataPath) + L"\\com.UCMobile.tar.gz";
	std::wstring backupFile = std::wstring(dataPath) + L"\\com.UCMobile.ab";

	if ( !FileExist(dirPath) && !FileExist(archivePath) && !FileExist(backupFile) )
		return false;

	if ( !FileExist(dirPath) && FileExist(archivePath) )
		ExtractPackage(archivePath);

	if ( !FileExist(dirPath) && FileExist(backupFile) )
		ExtractBackUp(backupFile);

	std::wstring zipTool = dirPath + L"\\ziptool";
	std::wstring xml = dirPath + L"\\files\\AddonsManifest.xml";
	std::wstring xmlBackup = dirPath + L"\\f\\AddonsManifest.xml";

	char key[9] = {0};

	if ( !GetXorKey(zipTool, key) && !GetXorKeyFromXml(xml, key) && !GetXorKeyFromXml(xmlBackup, key) )
		return false;

	DecryptFile(dirPath + L"\\UCMobile\\userdata\\history.ini", key, 0);
	DecryptFile(dirPath + L"\\UCMobile\\userdata\\bookmarks.ini", key, 1);

	DecryptFile(dirPath + L"\\r\\UCMobile\\userdata\\history.ini", key, 0);
	DecryptFile(dirPath + L"\\r\\UCMobile\\userdata\\bookmarks.ini", key, 1);

	return true;
}

bool UCBrowser_Start( const wchar_t* dataPath, int sysType )
{
	if ( 1 == sysType )
		return UC_Start_iOS(dataPath);
	else
		return UC_Start_Android(dataPath);
}

BrowserBookmark* UCBrowser_GetFirstBookMark()
{
	if ( g_bookmarks.empty() )
		return NULL;

	g_iBookmark = g_bookmarks.begin();
	return &(*g_iBookmark);
}

BrowserBookmark* UCBrowser_GetNextBookMark()
{
	if ( ++g_iBookmark != g_bookmarks.end() )
		return &(*g_iBookmark);

	return NULL;
}

BrowserHistory* UCBrowser_GetFirstHistory()
{
	if ( g_historys.empty() )
		return NULL;

	g_iHistory = g_historys.begin();
	return &(*g_iHistory);
}

BrowserHistory* UCBrowser_GetNextHistory()
{
	if ( ++g_iHistory != g_historys.end() )
		return &(*g_iHistory);

	return NULL;
}

void UCBrowser_Free()
{
	g_historys.clear();
	g_bookmarks.clear();
}
