#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <Windows.h>
#include <shellapi.h>
#include <time.h>

inline bool FileExist(const std::wstring& path)
{
	DWORD dwResult = GetFileAttributesW(path.c_str());

	if ( INVALID_FILE_ATTRIBUTES == dwResult
		&& ERROR_FILE_NOT_FOUND == GetLastError() )
		return false;

	return true;
}

inline bool SHMove(LPCWSTR from, LPCWSTR to)
{
	SHFILEOPSTRUCT fileOp = {0};
	fileOp.wFunc = FO_MOVE;
	TCHAR newFrom[MAX_PATH];
	wcscpy(newFrom, from);
	newFrom[wcslen(from) + 1] = NULL;
	fileOp.pFrom = newFrom;
	WCHAR newTo[MAX_PATH];
	wcscpy(newTo, to);
	newTo[wcslen(to) + 1] = NULL;
	fileOp.pTo = newTo;
	fileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;

	int result = SHFileOperation(&fileOp);

	return result == 0;
}

inline bool SHDel(LPCWSTR dir)
{
	WCHAR wzTemp[MAX_PATH] = {0};
	wcscpy(wzTemp, dir);
	SHFILEOPSTRUCTW FileOp;
	FileOp.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI;
	FileOp.pFrom = wzTemp;
	FileOp.pTo = NULL;
	FileOp.wFunc = FO_DELETE;
	int result = SHFileOperationW(&FileOp);
	return result == 0;
}

inline std::wstring GetExePath()
{
	WCHAR path[MAX_PATH] = {0};
	GetModuleFileNameW(NULL, path, MAX_PATH);
	*wcsrchr(path, '\\') = L'\0';
	return std::wstring(path);
}

inline void ExtractPackage(const std::wstring& package)
{
	SetCurrentDirectoryW(GetExePath().c_str());
	std::wstring lzma = L"7z";
	std::wstring path = package.substr(0, package.rfind('\\'));
	std::wstring packageName = wcsrchr(package.c_str(), L'\\') + 1;
	std::wstring tarName = packageName.substr(0, packageName.length()-3);
	std::wstring dirName = packageName.substr(0, packageName.length()-7);
	std::wstring tempPath = path + L"\\temp";
	std::wstring tempTar = tempPath + L"\\" + tarName;

	WCHAR cmd[1024] = {0};
	wsprintfW(cmd, L"%s x \"%s\" -o\"%s\"", lzma.c_str(), package.c_str(), tempPath.c_str());
	_wsystem(cmd);

	wsprintfW(cmd, L"%s x \"%s\" -o\"%s\"", lzma.c_str(), tempTar.c_str(), tempPath.c_str());
	_wsystem(cmd);

	std::wstring src = tempPath + L"\\data\\data\\" + dirName;
	std::wstring dst = path + L"\\" + dirName;

	SHMove(src.c_str(), dst.c_str());
	SHDel(tempPath.c_str());
}

typedef int (WINAPI *ZlibUncompress)(char *dest, ULONG *destLen, const char *source, ULONG sourceLen);

inline void ExtractBackUp(const std::wstring& file)
{
	SetCurrentDirectoryW(GetExePath().c_str());
	std::wstring lzma = L"7z";

	std::wstring path = file.substr(0, file.rfind('\\'));
	std::wstring backupFileName = wcsrchr(file.c_str(), L'\\') + 1;
	std::wstring temp = path + L"\\temp";
	std::wstring tarFile = temp + L"\\1.tar";
	std::wstring appDirName = backupFileName.substr(0, backupFileName.length()-3);
	std::wstring tempAppDir = temp + L"\\apps\\" + appDirName;
	std::wstring finalAppDir = path + L"\\" + appDirName;

	HANDLE hf = CreateFileW(file.c_str(), FILE_GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( INVALID_HANDLE_VALUE == hf )
		return;

	DWORD fileSize = GetFileSize(hf, NULL);

	char* buffer = new char[fileSize - 24];

	SetFilePointer(hf, 24, 0, FILE_BEGIN);
	DWORD readed = 0;
	ReadFile(hf, buffer, fileSize-24, &readed, NULL);

	CloseHandle(hf);

	CreateDirectoryW(temp.c_str(), NULL);
	hf = CreateFileW(tarFile.c_str(), FILE_GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( INVALID_HANDLE_VALUE == hf )
	{
		delete [] buffer;
		return;
	}

	DWORD uncompressSize = fileSize*4;
	DWORD bufferSize = fileSize-24;
	char* uncompressBuffer = new char[uncompressSize];
	memset(uncompressBuffer, 0, uncompressSize);

	std::wstring zlib = GetExePath() + L"\\zlib1.dll";
	HMODULE hDll = LoadLibraryW(zlib.c_str());
	ZlibUncompress foo = (ZlibUncompress)GetProcAddress(hDll, "uncompress");

	foo(uncompressBuffer, &uncompressSize, buffer, bufferSize);

	DWORD written = 0;
	WriteFile(hf, uncompressBuffer, uncompressSize, &written, NULL);
	CloseHandle(hf);

	delete [] buffer;
	delete [] uncompressBuffer;

	FreeLibrary(hDll);

	WCHAR cmd[1024] = {0};
	wsprintfW(cmd, L"%s x \"%s\" -o\"%s\"", lzma.c_str(), tarFile.c_str(), temp.c_str());
	_wsystem(cmd);

	SHMove(tempAppDir.c_str(), finalAppDir.c_str());
	SHDel(temp.c_str());
}

inline std::string GetTimeStrFromLongLong(__int64 time)
{
	time_t t = (time_t)time;
	struct tm rt = {0};

	_localtime64_s(&rt, &t);

	char timeStr[256] = {0};
	wsprintfA(timeStr, "%.4d-%.2d-%.2d %.2d:%.2d:%.2d", rt.tm_year + 1900, rt.tm_mon + 1, rt.tm_mday, rt.tm_hour, rt.tm_min, rt.tm_sec);

	return timeStr;
}

#endif // UTILS_H