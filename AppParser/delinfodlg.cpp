#include "StdAfx.h"
#include "delinfodlg.h"

#include "utils.h"
#include "datamanager.h"

const wchar_t* Del_info_name[] = {L"\\sms.bin", L"\\Contacts.bin", L"\\Records.bin"};

DelInfoDlg::DelInfoDlg(QWidget *parent, InfoType type)
	: QFrame(parent)
	, m_type(type)
{
	ui.setupUi(this);
	Utils::InitStyle(this);
}

DelInfoDlg::~DelInfoDlg()
{

}

void DelInfoDlg::Update()
{
	DataManager& dm = DataManager::GetInstance();
	std::wstring dirPath = dm.GetDirPath() + L"\\" + dm.GetCurrentForensicsDir();

	ui.content->clear();

	std::wstring fileName = dirPath + Del_info_name[m_type];

	HANDLE hf = CreateFileW(fileName.c_str(), FILE_GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( INVALID_HANDLE_VALUE == hf )
		return;

	DWORD size = GetFileSize(hf, NULL);

	char* buffer = new char[size];
	DWORD readed = 0;
	ReadFile(hf, buffer, size, &readed, NULL);
	CloseHandle(hf);

	ui.content->setPlainText(QString::fromUtf8(buffer, size));

	delete [] buffer;
}
