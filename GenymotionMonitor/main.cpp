#include <Windows.h>
#include <ShlObj.h>

#include "VirtualMachine.h"

#pragma comment(lib, "shell32.lib")

WCHAR g_virtualBoxConfig[MAX_PATH] = {0};

using namespace VirtualMachine;

inline bool InitVirtualBoxConfig()
{
	SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, NULL, g_virtualBoxConfig);
	wcscat(g_virtualBoxConfig, L"\\.VirtualBox\\VirtualBox.xml");

	HANDLE hf = CreateFile(g_virtualBoxConfig, FILE_GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( INVALID_HANDLE_VALUE == hf )
		return false;

	CloseHandle(hf);

	return true;
}

bool FindInList(Node* list, const wchar_t* text)
{
	while ( list )
	{
		if ( 0 == wcscmp(list->machineName, text) )
			return true;

		list = list->next;
	}

	return false;
}

bool MonitorForegroundWindow(Node* machineList)
{
	while ( true )
	{
		HWND window = GetForegroundWindow();
		WCHAR windowText[1024] = {0};
		GetWindowTextW(window, windowText, 1024);

		if ( FindInList(machineList, windowText) )
			ShowWindow(window, SW_HIDE);

		if ( 0 != wcsstr(windowText, L"Genymotion for personal use") )
			SetWindowTextW(window, L"手机取证-模拟器");

		Sleep(100);
	}
}

int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	if ( !InitVirtualBoxConfig() )
		return -1;

	Node* machineList = NULL;

	if ( NULL == ( machineList = GetMachineList(g_virtualBoxConfig) ) )
		return -1;

	MonitorForegroundWindow(machineList);

	DeleteList(machineList);

	return 0;
}