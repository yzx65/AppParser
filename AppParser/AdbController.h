/*!
	Description : Simple wrapper of the "adb.exe"
	Author		: Ruining Song
	Date		: 2014/04/21
*/

#ifndef ADBCONTROLLER_H
#define ADBCONTROLLER_H

#include <Windows.h>
#include <string>

class AdbController
{
public:
	AdbController(std::wstring adbPath);
	~AdbController();

	int InitAdb();
	bool CopyFile(std::wstring src, std::wstring dst);
	bool DeleteDir(std::wstring dir);
	bool UnInstallApk(std::wstring apkPath);
	bool InstallApk(std::wstring apkPath);
	bool CloseAdb();
	bool Reboot();

	/*
	\param
		包含 shell 命令的重定向文件
	*/
	bool ExecuteShell(std::wstring& file);

	std::string ExecuteShellCmd(const wchar_t* cmd);
	std::string ExecuteCommand(std::wstring cmd);

private:
	bool AdbCommand(std::wstring cmd, std::string& output);
	bool CreatePipe();

private:
	std::wstring m_adbPath;
	HANDLE m_pipe;
	HANDLE m_hRead;
	HANDLE m_hWrite;
};

#endif // ADBCONTROLLER_H