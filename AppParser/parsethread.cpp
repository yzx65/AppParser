#include "StdAfx.h"
#include "parsethread.h"
#include "utils.h"
#include "datamanager.h"

#include <Windows.h>

ParseThread::ParseThread(QObject *parent)
	: QThread(parent)
	, m_clear(false)
	, m_extractPassword("")
	, m_input(false)
{

}

ParseThread::~ParseThread()
{

}

void ParseThread::SetKey(std::wstring key)
{
	m_key = key;
}

void ParseThread::SetClear(bool clear)
{
	m_clear = clear;
}

void ParseThread::WaitForUserInput()
{
	while ( ! m_input )
	{
		qDebug() << "WaitForUserInput";
		Sleep(100);
	}
}

void ParseThread::run()
{
	emit TotalProcess(18);

	HANDLE hLog = Utils::LogStart();

	int process = 0;
	emit CurrentProcess(process++);

	DataManager& dm = DataManager::GetInstance();
	std::wstring device = m_key.substr(0, m_key.find('\\'));

	std::wstring path = dm.GetDirPath() + L"\\" + m_key;
	Utils::Log(hLog, L"设备路径 : %s\r\n\r\n", path.c_str());

	if ( m_clear )
	{
		dm.Clear();
		dm.ParseCaseInfo();

		const std::list<CASE_INFO>& cases = dm.GetCaseList();

		for ( std::list<CASE_INFO>::const_iterator it = cases.begin();
			it != cases.end();
			++it )
		{
			const wchar_t* deviceName = it->wzDirPath;
			dm.ParseDeviceInfo(deviceName);;
		}
	}

	emit CurrentProcess(process++);
	emit CurrentStatus(Utils::stoq("正在解压文件 ..."));
	Utils::Log(hLog, L"正在解压文件 ...\r\n");
	dm.ExtractBackupFile(m_key);

	m_cancleExtract = false;
	m_input = false;

	while ( DataManager::EXTRACT_IOS_BACKUP_FAILED == dm.GetError() )
	{
		emit QueryIosBackupPassword();
		WaitForUserInput();

		if ( m_cancleExtract )
			break;

		dm.SetIosBackupPassword(m_extractPassword);
		dm.ExtractBackupFile(m_key);
		m_input = false;
	}

	dm.SetIosBackupPassword("");

	emit CurrentProcess(process++);
	emit CurrentStatus(Utils::stoq("正在解析密码信息 ..."));
	Utils::Log(hLog, L"正在解析密码信息 ...\r\n");
	dm.ParseKeyChainInfo(m_key);

	emit CurrentProcess(process++);
	emit CurrentStatus(Utils::stoq("正在解析应用信息 ..."));
	Utils::Log(hLog, L"正在解析应用信息 ...\r\n");
	dm.ParseAppInfo(m_key);

	emit CurrentProcess(process++);
	emit CurrentStatus(Utils::stoq("正在解析短信记录 ..."));
	Utils::Log(hLog, L"正在解析短信记录 ...\r\n");
	dm.ParseSmsInfo(m_key);

	emit CurrentProcess(process++);
	emit CurrentStatus(Utils::stoq("正在解析通讯录 ..."));
	Utils::Log(hLog, L"正在解析通讯录 ...\r\n");
	dm.ParseContactInfo(m_key);

	emit CurrentProcess(process++);
	emit CurrentStatus(Utils::stoq("正在解析通话记录 ..."));
	Utils::Log(hLog, L"正在解析通话记录 ...\r\n");
	dm.ParseRecordInfo(m_key);

	emit CurrentProcess(process++);
	emit CurrentStatus(Utils::stoq("正在解析 QQ 聊天记录 ..."));
	Utils::Log(hLog, L"正在解析 QQ 聊天记录 ...\r\n");
	dm.ParseQQInfo(m_key);

	emit CurrentProcess(process++);
	emit CurrentStatus(Utils::stoq("正在解析微信聊天记录 ..."));
	Utils::Log(hLog, L"正在解析微信聊天记录 ...\r\n");
	dm.ParseWeixinInfo(m_key);

	emit CurrentProcess(process++);
	emit CurrentStatus(Utils::stoq("正在解析 Line 聊天记录 ..."));
	Utils::Log(hLog, L"正在解析 Line 聊天记录 ...\r\n");
	dm.ParseLineInfo(m_key);

	emit CurrentProcess(process++);
	emit CurrentStatus(Utils::stoq("正在解析 UC 浏览器历史记录 ..."));
	Utils::Log(hLog, L"正在解析 UC 浏览器历史记录 ...\r\n");
	dm.ParseUCBrowserInfo(m_key);

	emit CurrentProcess(process++);
	emit CurrentStatus(Utils::stoq("正在解析系统浏览器历史记录 ..."));
	Utils::Log(hLog, L"正在解析系统浏览器历史记录 ...\r\n");
	dm.ParseDefaultBrowserInfo(m_key);

	emit CurrentProcess(process++);
	emit CurrentStatus(Utils::stoq("正在解析 QQ 浏览器历史记录 ..."));
	Utils::Log(hLog, L"正在解析 QQ 浏览器历史记录 ...\r\n");
	dm.ParseQQBrowserInfo(m_key);

	emit CurrentProcess(process++);
	emit CurrentStatus(Utils::stoq("正在解析百度浏览器历史记录 ..."));
	Utils::Log(hLog, L"正在解析百度浏览器历史记录 ...\r\n");
	dm.ParseBaiduBrowserInfo(m_key);

	emit CurrentProcess(process++);
	emit CurrentStatus(Utils::stoq("正在解析猎豹浏览器历史记录 ..."));
	Utils::Log(hLog, L"正在解析猎豹浏览器历史记录 ...\r\n");
	dm.ParseJinShanBrowserInfo(m_key);

	emit CurrentProcess(process++);
	emit CurrentStatus(Utils::stoq("正在解析 Safari 浏览器历史记录 ..."));
	Utils::Log(hLog, L"正在解析 Safari 浏览器历史记录 ...\r\n");
	dm.ParseSafariBrowserInfo(m_key);

	emit CurrentProcess(process++);
	emit CurrentStatus(Utils::stoq("正在解析百度地图历史记录 ..."));
	Utils::Log(hLog, L"正在解析百度地图历史记录 ...\r\n");
	dm.ParseBaiduMapInfo(m_key);

	emit CurrentProcess(process++);
	emit CurrentStatus(Utils::stoq("正在解析高德地图历史记录 ..."));
	Utils::Log(hLog, L"正在解析高德地图历史记录 ...\r\n");
	dm.ParseGaodeMapInfo(m_key);

	m_clear = false;

	emit ParseDone();

	Utils::LogEnd(hLog);
}
