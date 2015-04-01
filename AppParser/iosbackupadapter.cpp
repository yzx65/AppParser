#include "stdafx.h"
#include "iosbackupadapter.h"
#include <Windows.h>
#include <string>
#include "utils.h"

#include "CommonDef.h"

bool ProcessDir(const std::wstring& dir)
{
	std::wstring backupDir = dir + L"\\Backup";

	if ( ! Utils::FileExist(backupDir) )
		return false;

	std::wstring newDir = dir + L"(Backup)";
	CreateDirectory(newDir.c_str(), NULL);

	std::wstring oldDeviceInfo = dir + L"\\DeviceInfo";
	std::wstring newDeviceInfo = newDir + L"\\DeviceInfo";

	CopyFileW(oldDeviceInfo.c_str(), newDeviceInfo.c_str(), false);

	std::wstring newBackupDir = newDir + L"\\Backup_1";
	Utils::SHMove(backupDir.c_str(), newBackupDir.c_str());

	return true;
}

void HackCaseInfo(const std::wstring& dataDir, const std::wstring& deviceName)
{
	std::wstring caseInfo = dataDir + L"\\CaseInfo";
	HANDLE hf = CreateFileW(caseInfo.c_str(), FILE_ALL_ACCESS, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( INVALID_HANDLE_VALUE == hf )
		return;

	SetFilePointer(hf, 0, 0, FILE_END);

	CASE_INFO appendItem = {0};
	wcscpy(appendItem.wzDirPath, deviceName.c_str());

	DWORD writted = 0;
	WriteFile(hf, &appendItem, sizeof(CASE_INFO), &writted, NULL);

	CloseHandle(hf);
}

void IosBackupAdapter::SeparateDir(const std::wstring& dataDir)
{
	std::wstring findStr = std::wstring(dataDir) + L"\\*.*";
	WIN32_FIND_DATAW fd = {0};

	HANDLE hf = FindFirstFile(findStr.c_str(), &fd);

	if ( INVALID_HANDLE_VALUE == hf )
		return;

	do 
	{
		if ( ! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
			continue;

		if ( 0 == wcscmp(fd.cFileName, L".") || 0 == wcscmp(fd.cFileName, L"..") )
			continue;

		if ( ProcessDir(std::wstring(dataDir) + L"\\" + fd.cFileName) )
			HackCaseInfo(dataDir, std::wstring(dataDir) + L"\\" + fd.cFileName + L"(Backup)");

	} while ( FindNextFileW(hf, &fd) );

	FindClose(hf);
}

bool IosBackupAdapter::UnBackup( const std::wstring& appDir, const std::string& password )
{
	std::wstring unBackupTool = Utils::GetExePath() + L"\\tools\\ios_backup\\backup_tool.exe";
	
	std::wstring originDir = appDir;
	std::wstring unBackupDir = appDir;

	// If already unbackup, just return
	if ( Utils::FileExist(unBackupDir + L"\\Manifest.plist") )
		return true;

	PROCESS_INFORMATION piProcInfo = {0}; 
	STARTUPINFOA siStartInfo = {0};

	siStartInfo.wShowWindow = SW_HIDE;

	// Find hash dir such as '8c386c653b87f810d28b6e674f2ee2d75a456e02'
	std::wstring hashDir;
	std::wstring findStr = originDir + L"\\*.*";
	WIN32_FIND_DATAW fd = {0};

	HANDLE hf = FindFirstFile(findStr.c_str(), &fd);

	if ( INVALID_HANDLE_VALUE == hf )
		return true;

	do 
	{
		if ( wcslen(fd.cFileName) == wcslen(L"8c386c653b87f810d28b6e674f2ee2d75a456e02") )
		{
			hashDir = fd.cFileName;
			break;
		}

	} while ( FindNextFileW(hf, &fd) );

	FindClose(hf);

	if ( hashDir.empty() )
	{
		Utils::__TRACE(L"[IosBackupAdapter] Cannot find hash dir.\r\n");
		return true;
	}

	// Create process 'backup_tool.exe'
	char cmd[1024] = {0};
	wsprintfA(cmd, " \"%s\\%s\" \"%s\" 0 9999 %s",
		Utils::WideToAnsi(originDir).c_str(), 
		Utils::WideToAnsi(hashDir).c_str(),
		Utils::WideToAnsi(unBackupDir).c_str(),
		password.c_str());

	if ( !CreateProcessA(Utils::WideToAnsi(unBackupTool).c_str(), cmd, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &siStartInfo, &piProcInfo) )
	{
		Utils::__TRACE(L"[IosBackupAdapter] CreateProcessW failed. [%d] [%s] \r\n", GetLastError(), Utils::AnsiToWide(cmd).c_str());
		return true;
	}

	WaitForSingleObject(piProcInfo.hProcess, INFINITE);

	CloseHandle(piProcInfo.hProcess);
	CloseHandle(piProcInfo.hThread);

	return Utils::FileExist(unBackupDir + L"\\Manifest.plist");
}

void IosBackupAdapter::GenerateKeyChain( const std::wstring& appDir )
{
	std::wstring keychainTool = Utils::GetExePath() + L"\\tools\\ios_backup\\keychain_tool.exe";
	std::wstring originDir = appDir;
	std::wstring workDir = appDir;

	if ( Utils::FileExist(workDir + L"\\keychain.csv") )
		return;

	PROCESS_INFORMATION piProcInfo = {0}; 
	STARTUPINFOA siStartInfo = {0};

	siStartInfo.wShowWindow = SW_HIDE;

	// Create process 'keychain_tool.exe'
	char cmd[1024] = {0};
	wsprintfA(cmd, " -p \"%s\\KeychainDomain\\keychain-backup.plist\" \"%s\\Manifest.plist\"",
		Utils::WideToAnsi(workDir).c_str(),
		Utils::WideToAnsi(workDir).c_str());

	std::string currentDir = "C:\\Temp";
	CreateDirectoryA(currentDir.c_str(), NULL);

	if ( !CreateProcessA(
		      Utils::WideToAnsi(keychainTool).c_str(), 
			  cmd, 
			  NULL, 
			  NULL,
			  TRUE, 
			  CREATE_NO_WINDOW, 
			  NULL, 
			  currentDir.c_str(),
			  &siStartInfo, 
			  &piProcInfo) )
	{
		Utils::__TRACE(L"[IosBackupAdapter] CreateProcessW failed. [%d] [%s] \r\n", GetLastError(), Utils::AnsiToWide(cmd).c_str());
		return;
	}

	WaitForSingleObject(piProcInfo.hProcess, INFINITE);

	CloseHandle(piProcInfo.hProcess);
	CloseHandle(piProcInfo.hThread);

	std::wstring src = Utils::AnsiToWide(currentDir) + L"\\keychain.csv";
	std::wstring dst = workDir + L"\\keychain.csv";

	CopyFileW(src.c_str(), dst.c_str(), FALSE);

	Utils::SHMove(Utils::AnsiToWide(currentDir).c_str(), (workDir+L"\\keychain").c_str());
	Utils::SHDel(Utils::AnsiToWide(currentDir).c_str());
}
