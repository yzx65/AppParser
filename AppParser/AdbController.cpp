
#include "stdafx.h"
#include "AdbController.h"
#include "utils.h"

#include <list>
#include <TlHelp32.h>

std::list<std::string> SplitLines(std::string& result)
{
	int pos = 0;
	std::list<std::string> lines;

	for ( int i = 0; i < result.size(); ++i )
	{
		if ( result[i] == '\n' || i == result.size()-1 )
		{
			std::string line = 
				result.substr(pos, i == result.size()-1 ? result.size() : i);

			if ( !line.empty() && line != "\r\n" )
				lines.push_back(line);

			pos = i + 1 < result.size() ? i + 1 : i;
		}
	}

	return lines;
}

AdbController::AdbController(std::wstring adbPath)
: m_adbPath ( adbPath )
, m_hRead (NULL)
, m_hWrite (NULL)
{
}

AdbController::~AdbController()
{
	if ( m_hRead )
		CloseHandle(m_hRead);

	if ( m_hWrite )
		CloseHandle(m_hWrite);
}

int AdbController::InitAdb()
{
	if ( !Utils::FileExist(m_adbPath.c_str()) )
		return false;

	std::string output;

	if ( !AdbCommand(m_adbPath + L" start-server", output) )
	{
		Utils::__TRACE(L"[AdbController] start-server failed.\r\n");
		return false;
	}

	AdbCommand(m_adbPath + L" devices", output);
	
	std::list<std::string> lines = SplitLines(output);

	return lines.size();
}

bool AdbController::CopyFile(std::wstring src, std::wstring dst )
{
	wchar_t cmd[MAX_PATH] = {0};
	wchar_t dir[MAX_PATH] = {0};

	std::string output;

	wsprintf(cmd, L"%s push \"%s\" \"%s\"", m_adbPath.c_str(), src.c_str(), dst.c_str());

	Utils::__TRACE(L"[CopyFile] %s\r\n", cmd);
	return AdbCommand(cmd, output);
}

bool AdbController::UnInstallApk(std::wstring apkPath)
{
	wchar_t cmd[MAX_PATH] = {0};
	wsprintf(cmd, L"%s uninstall \"%s\"", m_adbPath.c_str(), apkPath.c_str());
	std::string output;

	return AdbCommand(cmd, output);
}

bool AdbController::InstallApk(std::wstring apkPath)
{
	wchar_t cmd[MAX_PATH] = {0};
	wsprintf(cmd, L"%s install \"%s\"", m_adbPath.c_str(), apkPath.c_str());
	std::string output;

	return AdbCommand(cmd, output);
}

bool AdbController::CloseAdb()
{
	wchar_t cmd[MAX_PATH] = {0};
	wsprintf(cmd, L"%s kill-server", m_adbPath.c_str());
	std::string output;

	return AdbCommand(cmd, output);
}

bool AdbController::Reboot()
{
	wchar_t cmd[MAX_PATH] = {0};
	wsprintf(cmd, L"%s reboot", m_adbPath.c_str());
	std::string output;

	return AdbCommand(cmd, output);
}

bool AdbController::CreatePipe()
{
	SECURITY_ATTRIBUTES sa = {0};
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	// 创建匿名管道用于获取 adb 输出
	if ( !::CreatePipe(&m_hRead, &m_hWrite, &sa, 0) )
	{
		Utils::__TRACE(L"[AdbController] CreatePipe Failed. [%d] \r\n", GetLastError());
		return false;
	}

	SetHandleInformation(m_hRead, HANDLE_FLAG_INHERIT, 0);

	return true;
}

bool AdbController::AdbCommand(std::wstring cmd, std::string& output)
{
	if ( !CreatePipe() )
	{
		Utils::__TRACE(
			L"[AdbController] CreatePipe Failed.\r\n");
		return false;
	}

	PROCESS_INFORMATION piProcInfo = {0}; 
	STARTUPINFO siStartInfo = {0};

	ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) ); 
	ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );

	siStartInfo.cb = sizeof(STARTUPINFO); 
	siStartInfo.hStdOutput = m_hWrite;
	siStartInfo.hStdInput = m_hRead;
	siStartInfo.hStdError = m_hRead;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	wchar_t cmdLine[MAX_PATH] = {0};
	wcscpy_s(cmdLine, MAX_PATH, cmd.c_str());
	CreateProcessW(NULL, cmdLine, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &siStartInfo, &piProcInfo);
	WaitForSingleObject(piProcInfo.hProcess, INFINITE);

	DWORD exitCode = 0;
	GetExitCodeProcess(piProcInfo.hProcess, &exitCode);
	
	CloseHandle(piProcInfo.hProcess);
	CloseHandle(piProcInfo.hThread);

	// 找不到设备时 adb.exe 返回错误码 1
	if ( 1 == exitCode )
	{
		Utils::__TRACE(
			L"[AdbController] AdbCommand Failed.\r\n");
		return false;
	}

	char* buffer = new char[1024 * 1024];
	memset(buffer, 0, 1024*1024);
	DWORD dwRead = 0;
	
	BOOL bRet = PeekNamedPipe(m_hRead, buffer, 1024*1024, &dwRead, NULL, NULL);

	Utils::__TRACE(
		L"[AdbController] Command : %s\r\n",
		cmdLine);

	Utils::__TRACE(
		"[AdbController] Result : %s\r\n",
		buffer);

	CloseHandle(m_hRead);
	CloseHandle(m_hWrite);

	m_hRead = m_hWrite = NULL;
	output = buffer;

	delete [] buffer;

	return true;
}

bool AdbController::ExecuteShell(std::wstring& file )
{
	if ( !Utils::FileExist(file.c_str()) )
		return false;

	wchar_t cmd[MAX_PATH] = {0};
	wsprintf(cmd, L"cmd.exe /c %s shell < \"%s\"", m_adbPath.c_str(), file.c_str());

	std::string output;
	return AdbCommand(cmd, output);
}

std::string AdbController::ExecuteCommand( std::wstring cmd )
{

	wchar_t command[MAX_PATH] = {0};
	wsprintf(command, L"%s %s", m_adbPath.c_str(), cmd.c_str());

	std::string output;
	AdbCommand(command, output);

	return output;
}

std::string AdbController::ExecuteShellCmd( const wchar_t* cmd )
{
	wchar_t command[MAX_PATH] = {0};
	wsprintf(command, L"%s shell %s", m_adbPath.c_str(), cmd);

	std::string output;
	AdbCommand(command, output);

	return output;
}

bool AdbController::DeleteDir(std::wstring dir)
{
	wchar_t cmd[MAX_PATH] = {0};
	wsprintf(cmd, L"%s shell su -c \"rm -r \"%s\"\"", m_adbPath.c_str(), dir.c_str());

	std::string output;
	return AdbCommand(cmd, output);
}
