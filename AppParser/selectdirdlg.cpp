#include "StdAfx.h"
#include "selectdirdlg.h"
#include "framelessdlg.h"
#include "utils.h"
#include "msgbox.h"

#include "parsethread.h"
#include "waitdlg.h"

#include <QFileDialog>

int SelectDirDlg::Invoke(QString dir)
{
	FramelessDlg container(0, CLOSE_BUTTON);
	SelectDirDlg* dlg = new SelectDirDlg(&container);

	connect(dlg, SIGNAL(OK()), &container, SLOT(accept()));
	connect(dlg, SIGNAL(Resize(QSize)), &container, SLOT(Resize(QSize)));
	connect(dlg, SIGNAL(CenterWindow()), &container, SLOT(CenterWindow()));
	connect(dlg, SIGNAL(SetSubTitle(QString)), &container, SLOT(SetTitle(QString)));

	container.SetDlg(dlg);
	container.SetTitle(Utils::stoq("选择案例所在目录"));
	container.setFixedSize(400, 110);
	container.CenterWindow();

	dlg->SetDataDir(dir);

	return container.exec();	
}

SelectDirDlg::SelectDirDlg(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);
	Utils::InitStyle(this);
	ui.stack->hide();

	InitConnections();
}

SelectDirDlg::~SelectDirDlg()
{
}

void SelectDirDlg::InitConnections()
{
	connect(ui.btnBrowse, SIGNAL(clicked()), this, SLOT(Browse()));
	connect(ui.lstDevices, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(SelectForensicsType()));
	connect(ui.lstForensicsType, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(SelectForensicsTypeFinished()));
}

void SelectDirDlg::SetDataDir(QString dir)
{
	ui.edtPath->setText(dir);

	if ( dir.isEmpty() )
		return;

	ListDevices();
}

void SelectDirDlg::Browse()
{
	QString dir = QFileDialog::getExistingDirectory(this, Utils::stoq("选择案例所在目录"));

	if ( dir.isEmpty() )
		return;

	dir.replace("/", "\\");
	ui.edtPath->setText(dir);

	ListDevices();
}

void SelectDirDlg::SelectForensicsType()
{
	QList<QListWidgetItem*> items = ui.lstDevices->selectedItems();
	std::wstring device = Utils::qtow(items[0]->text());
	m_dm.SetCurrentDevice(device);

	ui.stack->setCurrentIndex(1);

	ui.lstForensicsType->clear();
	DeviceDataDirMap& dirs = m_dm.GetDeviceDataDirMap();
	ForensicsTypeMap& types = m_dm.GetForensicsTypeMap();

	int count = dirs.count(device);
	DeviceDataDirMap::iterator it = dirs.find(device);

	if ( count == 1 )
	{
		DataManager::GetInstance().SetCurrentForensicsDir((*it).second);

		QString dir = ui.edtPath->text();
		DataManager::GetInstance().SetDirPath(Utils::qtow(dir));
		DataManager::GetInstance().SetCurrentDevice(device);
		emit OK();
		return;
	}

	for ( int i = 0; i != count ; ++i, ++it )
	{
		QListWidgetItem* item = new QListWidgetItem;
		std::wstring name = types[(*it).second].name;
		item->setText(Utils::wtoq(name));
		item->setData(Qt::UserRole, Utils::wtoq((*it).second));
		item->setIcon(QPixmap(Utils::wtoq(types[(*it).second].icon)));
		ui.lstForensicsType->insertItem(0, item);
	}

	emit SetSubTitle(Utils::stoq("选择取证数据类型"));
}

void SelectDirDlg::SelectForensicsTypeFinished()
{
	QList<QListWidgetItem*> items = ui.lstForensicsType->selectedItems();
	std::wstring currentDir = Utils::qtow(items[0]->data(Qt::UserRole).toString());
	DataManager::GetInstance().SetCurrentForensicsDir(currentDir);
	DataManager::GetInstance().SetCurrentDevice(m_dm.GetCurrentDevice());

	QString dir = ui.edtPath->text();
	DataManager::GetInstance().SetDirPath(Utils::qtow(dir));

	emit OK();
}

void SelectDirDlg::ListDevices()
{
	QString dir = ui.edtPath->text();
	ui.lstDevices->clear();
	m_dm.Clear();
	m_dm.SetDirPath(Utils::qtow(dir));

	if ( !m_dm.ParseCaseInfo() )
	{
		MsgBox::Information(this, Utils::stoq("解析失败"), Utils::stoq("解析失败，指定目录中不存在案例配置文件"));
		return;
	}

	const std::list<CASE_INFO>& cases = m_dm.GetCaseList();

	for ( std::list<CASE_INFO>::const_iterator it = cases.begin();
		it != cases.end();
		++it )
	{
		const wchar_t* deviceName = it->wzDirPath;
		m_dm.ParseDeviceInfo(deviceName);
		DeviceInfoMap& deviceInfo = m_dm.GetDeviceMap();
		DEV_INFO info = deviceInfo[deviceName];

		QListWidgetItem* item = new QListWidgetItem;
		item->setText(Utils::wtoq(deviceName));

		if ( info.baseDevInfo.devType == DEV_TYPE_ANDROID )
			item->setIcon(QIcon(QPixmap(":/Image/android_icon.png")));
		else
			item->setIcon(QIcon(QPixmap(":/Image/ios.png")));

		ui.lstDevices->addItem(item);
	}

	ui.stack->show();
	emit Resize(QSize(400, 300));
	emit CenterWindow();

	ui.stack->setCurrentIndex(0);

	emit SetSubTitle(Utils::stoq("选择要分析的设备"));
}
