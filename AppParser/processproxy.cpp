#include "stdafx.h"
#include "processproxy.h"
#include "utils.h"
#include <string>
#include <Windows.h>
#include <Tlhelp32.h>

ProcessProxy::ProcessProxy(QString procPath)
	: m_procPath(procPath)
	, m_process(0)
{
	connect(&m_check, SIGNAL(timeout()), this, SLOT(CheckProcess()));
	m_check.start(100);
}

ProcessProxy::~ProcessProxy()
{
	if ( m_process )
		CloseHandle(m_process);
}

bool ProcessProxy::Start()
{
	std::wstring procPath = Utils::qtow(m_procPath);
	
	PROCESS_INFORMATION piProcInfo = {0}; 
	STARTUPINFO siStartInfo = {0};

	WCHAR cmd[1024] = {0};
	wcscpy(cmd, procPath.c_str());

	if ( !::CreateProcessW(NULL, cmd, NULL, NULL, TRUE, NULL, NULL, NULL, &siStartInfo, &piProcInfo) )
	{
		Utils::__TRACE(L"[ProcessProxy] CreateProcessW failed. [%d] [%s] \r\n", GetLastError(), cmd);
		return false;
	}

	m_process = piProcInfo.hProcess;

	return true;

}

bool ProcessProxy::Terminate()
{
	if ( !m_process )
	{
		Utils::__TRACE(L"[ProcessProxy] Cannot terminate process because the process isn't exist.\r\n");
		return false;
	}

	if ( !TerminateProcess(m_process, -1) )
	{
		Utils::__TRACE(L"[ProcessProxy] TerminateProcess failed. [%d]\r\n", GetLastError());
		return false;
	}

	CloseHandle(m_process);
	m_process = NULL;

	emit Finished();

	return true;
}

void ProcessProxy::CheckProcess()
{
	if ( !m_process )
	{
		if ( Utils::FindProcess(Utils::qtow(m_procPath).c_str(), m_process) )
			emit Attached();

		return;
	}

	if ( WAIT_OBJECT_0 == WaitForSingleObject(m_process, 0) )
	{
		CloseHandle(m_process);
		m_process = NULL;
		emit Finished();
	}
}

PROCESS_INFORMATION ProcessProxy::CreateProcess(const wchar_t* processName, DWORD flag)
{
	PROCESS_INFORMATION piProcInfo = {0}; 
	STARTUPINFO siStartInfo = {0};

	WCHAR cmd[1024] = {0};
	wsprintfW(cmd, L"%s", processName);

	if ( !::CreateProcessW(NULL, cmd, NULL, NULL, TRUE, flag, NULL, NULL, &siStartInfo, &piProcInfo) )
	{
		int errorId = GetLastError();
		return piProcInfo;
	}
	
	return piProcInfo;
}

void ProcessProxy::KillProcess(const wchar_t* processName)
{
	HANDLE tool = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	PROCESSENTRY32W pe = {0};
	pe.dwSize = sizeof(PROCESSENTRY32W);

	if ( !Process32First(tool, &pe) )
	{
		int errorId = GetLastError();
		CloseHandle(tool);
		return;
	}

	do 
	{
		if ( 0 == wcscmp(pe.szExeFile, processName) )
		{
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);
			TerminateProcess(hProcess, -1);
		}

	} while ( Process32NextW(tool, &pe) );

	CloseHandle(tool);
}
