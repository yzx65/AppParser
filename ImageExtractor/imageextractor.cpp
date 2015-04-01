#include "imageextractor.h"

#include <QFileDialog>
#include "utils.h"

#include "androidimageadapter.h"
#include "msgbox.h"

typedef BOOL (*InitialExtractModule)(LPWSTR lpMissionId, LPWSTR lpOutputPath);
typedef BOOL (*StartDecrypt)();

HMODULE g_hExtractModule = NULL;
InitialExtractModule g_ExtractInit = NULL;
StartDecrypt g_ExtractStart = NULL;


WorkThread::WorkThread(QObject* parent /* = 0 */)
	: QThread(parent)
	, m_cancle(false)
{
	std::wstring extractDll = Utils::GetExePath() + L"\\ExtractModule.dll";
	g_hExtractModule = LoadLibrary(extractDll.c_str());

	if ( g_hExtractModule )
	{
		g_ExtractInit = (InitialExtractModule)GetProcAddress(g_hExtractModule, "InitialExtractModule");
		g_ExtractStart = (StartDecrypt)GetProcAddress(g_hExtractModule, "StartDecrypt");
	}
}

WorkThread::~WorkThread()
{
	if ( g_hExtractModule )
		FreeLibrary(g_hExtractModule);
}

void WorkThread::SetParameters(std::wstring srcPath, std::wstring dstPath, bool extractFile, bool mergeFile, bool extractImageFile)
{
	m_srcPath = srcPath;
	m_dstPath = dstPath;
	m_cancle = false;
	m_extractFile = extractFile;
	m_mergeFile = mergeFile;
	m_extractImageFile = extractImageFile;
}

void WorkThread::run()
{
	std::wstring srcDevInfo = m_srcPath + L"\\DeviceInfo";
	std::wstring dstDevInfo = m_dstPath + L"\\DeviceInfo";

	CopyFile(srcDevInfo.c_str(), dstDevInfo.c_str(), FALSE);

	srcDevInfo = m_srcPath + L"\\Device_Info.xml";
	dstDevInfo = m_dstPath + L"\\Device_Info.xml";

	CopyFile(srcDevInfo.c_str(), dstDevInfo.c_str(), FALSE);


	if ( m_extractFile )
		ExtractFile();

	if ( m_mergeFile )
		ExtractImage();
}

bool WorkThread::ExtractFile()
{
	WCHAR missionId[MAX_PATH] = {0};
	wsprintfW(missionId, L"%s", wcsrchr(m_srcPath.c_str(), L'\\')+1);
	WCHAR destPath[MAX_PATH] = {0};
	wsprintfW(destPath, L"%s\\", m_dstPath.c_str());

	emit emitStatus(Utils::stoq("正在释放快速取证文件 ... "));

	if ( g_ExtractInit == NULL )
	{
		MessageBoxW(NULL, L"未找到释放文件模块", L"提示", MB_OK);
		return false;
	}

	if ( !g_ExtractInit(missionId, destPath) )
	{
		emit emitInformation(Utils::stoq("释放快速取证文件失败"));
		return false;
	}

	if ( !g_ExtractStart() )
	{
		emit emitInformation(Utils::stoq("释放快速取证文件失败"));
		return false;
	}

	return true;
}

bool WorkThread::ExtractImage()
{
	std::wstring dstImagePath = m_dstPath + L"\\OfflineImage";
	CreateDirectory(dstImagePath.c_str(), NULL);
	return AndroidImageAdapter::ExtractImageFile(m_srcPath, dstImagePath, m_extractImageFile, this);
}

ImageExtractor::ImageExtractor(QWidget *parent, Qt::WFlags flags)
	: QFrame(parent, flags)
{
	ui.setupUi(this);
	Utils::InitStyle(this);

	ui.btnStart->setEnabled(false);

	InitConnection();
	InitTaskList();
	InitDefaultPath();
}

ImageExtractor::~ImageExtractor()
{
	if ( m_workThread )
	{
		if ( m_workThread->isRunning() )
			m_workThread->terminate();

		delete m_workThread;
	}
}

void ImageExtractor::InitConnection()
{
	connect(ui.btnBrowseOutputPath, SIGNAL(clicked()), this, SLOT(OnBtnBrowseOutputPathClicked()));
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(OnBtnStartClicked()));

	connect(ui.cmbTask, SIGNAL(currentIndexChanged(int)), this, SLOT(OnParameterChanged()));
	connect(ui.btnCustomOutputPath, SIGNAL(clicked()), this, SLOT(OnParameterChanged()));
	connect(ui.btnExtractFile, SIGNAL(clicked()), this, SLOT(OnParameterChanged()));
	connect(ui.btnExtractImageFile, SIGNAL(clicked()), this, SLOT(OnParameterChanged()));
	connect(ui.btnMergeImage, SIGNAL(clicked()), this, SLOT(OnParameterChanged()));

	m_workThread = new WorkThread;
	connect(m_workThread, SIGNAL(emitStatus(QString)), this, SLOT(OnEmitWorkStatus(QString)));
	connect(m_workThread, SIGNAL(emitProcess(int)), this, SLOT(OnEmitWorkProcess(int)));
	connect(m_workThread, SIGNAL(emitInformation(QString)), this, SLOT(OnEmitWorkInformation(QString)));
	connect(m_workThread, SIGNAL(finished()), this, SLOT(OnWorkDone()));
}

void ImageExtractor::InitTaskList()
{
	std::wstring rootPath;
	Utils::HaveFlashDisk(rootPath);

	rootPath += L"OfflineMode";

	std::wstring findStr = rootPath + L"\\*.*";

	WIN32_FIND_DATAW fd = {0};
	HANDLE hf = FindFirstFileW(findStr.c_str(), &fd);

	if ( INVALID_HANDLE_VALUE == hf )
		return;

	do 
	{
		std::wstring fileName = fd.cFileName;

		if ( fileName == L".." || fileName == L"." )
			continue;

		ui.cmbTask->insertItem(0, Utils::wtoq(fileName));
		ui.cmbTask->setItemData(0, Utils::wtoq(rootPath + L"\\" + fileName));

	} while ( FindNextFileW(hf, &fd) );

	FindClose(hf);
}

void ImageExtractor::InitDefaultPath()
{
	wchar_t defaultPath[MAX_PATH] = L"C:\\PhoneForensics";

	for ( wchar_t driver = L'C'; driver <= 'Z'; ++driver )
	{
		defaultPath[0] = driver;

		if ( Utils::FileExist(defaultPath) )
		{
			m_defaultPath = defaultPath;
			ui.btnDefaultOutputPath->setText(Utils::wtoq(std::wstring(L"默认目录") + L"  " + defaultPath));
			return;
		}
	}

	ui.btnDefaultOutputPath->setEnabled(false);
	ui.btnCustomOutputPath->setChecked(true);
}

void ImageExtractor::OnBtnBrowseOutputPathClicked()
{
	QString outputPath = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("选择镜像文件目录"));

	if ( outputPath.isEmpty() )
		return;

	outputPath.replace("/", "\\");
	ui.edtOutputPath->setText(outputPath);
	OnParameterChanged();
}

void ImageExtractor::OnParameterChanged()
{
	if ( ui.btnCustomOutputPath->isChecked() )
	{
		ui.edtOutputPath->setEnabled(true);
		ui.btnBrowseOutputPath->setEnabled(true);
	}
	else
	{
		ui.edtOutputPath->setEnabled(false);
		ui.btnBrowseOutputPath->setEnabled(false);
	}

	if ( !ui.btnMergeImage->isChecked() )
	{
		ui.btnExtractImageFile->setChecked(false);
		ui.btnExtractImageFile->setEnabled(false);
	}
	else
	{
		ui.btnExtractImageFile->setEnabled(true);
	}

	if ( !ui.btnMergeImage->isChecked() && !ui.btnExtractFile->isChecked() && !ui.btnExtractImageFile->isChecked() )
	{
		ui.btnStart->setEnabled(false);
		return;
	}

	if ( ui.cmbTask->currentText().isEmpty() || ( ui.btnCustomOutputPath->isChecked() && ui.edtOutputPath->text().isEmpty() ) )
	{
		ui.btnStart->setEnabled(false);
		return;
	}

	ui.btnStart->setEnabled(true);
}

void ImageExtractor::OnBtnStartClicked()
{
	std::wstring outputPath = ui.btnDefaultOutputPath->isChecked() ? m_defaultPath : Utils::qtow(ui.edtOutputPath->text());
	outputPath = outputPath + L"\\" + Utils::qtow(ui.cmbTask->currentText());
	CreateDirectory(outputPath.c_str(), NULL);

	m_workThread->SetParameters(
		Utils::qtow(ui.cmbTask->itemData(ui.cmbTask->currentIndex()).toString()), 
		outputPath,
		ui.btnExtractFile->isChecked(),
		ui.btnMergeImage->isChecked(),
		ui.btnExtractImageFile->isChecked());
	ui.progressBar->setMaximum(0);
	m_workThread->start();
	ui.btnStart->setEnabled(false);
}

void ImageExtractor::OnEmitWorkStatus(QString status)
{
	ui.lbStatus->setText(status);
}

void ImageExtractor::OnEmitWorkInformation(QString info)
{
	MsgBox::Information(0, Utils::stoq("提示"), info);
}

void ImageExtractor::OnEmitWorkProcess(int process)
{

}

void ImageExtractor::OnWorkDone()
{
	ui.btnStart->setEnabled(true);
	ui.progressBar->setMaximum(1);
	ui.progressBar->setValue(1);
	ui.lbStatus->setText(Utils::stoq("操作完成"));
}