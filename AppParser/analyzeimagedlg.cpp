#include "StdAfx.h"
#include "analyzeimagedlg.h"
#include "utils.h"
#include "msgbox.h"
#include "datamanager.h"
#include "nofocusstyle.h"

#include <QtGui>
#include <QDateTime>

const int BufferSize = 1024 * 1024 * 10;
const int ContentSize = 200;

void SearchImageThread::SetSearchParameters(std::wstring imageFile, QString searchStr, bool utf8)
{
	m_imageFile = imageFile;
	m_searchStr = searchStr;
	m_utf8 = utf8;
}

void SearchImageThread::run()
{
	HANDLE hFile = CreateFile(
		m_imageFile.c_str(), 
		FILE_GENERIC_READ, 
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if ( INVALID_HANDLE_VALUE == hFile )
	{
		return;
	}

	LARGE_INTEGER fs = {0};
	GetFileSizeEx(hFile, &fs);
	LONGLONG fileSize = fs.QuadPart;

	DWORD readPieceSize = BufferSize;
	LONGLONG currentProcess = 0;
	DWORD readed = 0;

	emit TotalProgress(100);

	unsigned char* buffer = new unsigned char[readPieceSize];

	QByteArray searchStr = m_utf8 ? m_searchStr.toUtf8() : m_searchStr.toLocal8Bit();
	int patternLen = searchStr.length();
	unsigned char* pattern = new unsigned char[patternLen];
	memcpy(pattern, searchStr.data(), patternLen);

	while (true)
	{
		memset(buffer, 0, readPieceSize);
		ReadFile(hFile, buffer, readPieceSize, &readed, NULL);

		// Search buffer
		char displayText[ContentSize+1] = {0};

		for ( int i = 0; i < readPieceSize; )
		{			
			if ( 0 == memcmp(buffer+i, pattern, patternLen) )
			{
				for ( int j = 0; j < ContentSize; ++j )
				{
					if ( buffer[i+j] == 0 )
						displayText[j] = ' ';
					else
						displayText[j] = buffer[i+j];
				}

				QString result = m_utf8 ? QString::fromUtf8(displayText, ContentSize+1) : QString::fromLocal8Bit(displayText, ContentSize+1);
				emit SearchResult(result, currentProcess + i);
				i += ContentSize;
			}
			else
				++i;
		}

		currentProcess += readed;
		emit CurrentProgress((int)(currentProcess * 100 / fileSize));

		if ( 0 == readed )
			break;
	}

	delete [] buffer;
	CloseHandle(hFile);
}

AnalyzeImageDlg::AnalyzeImageDlg(QWidget *parent)
	: QFrame(parent)
	, m_resultCount(0)
	, m_closed(false)
{
	ui.setupUi(this);
	Utils::InitStyle(this);

	QStyledItemDelegate* itemDelegate = new QStyledItemDelegate();
	ui.cmbImage->setItemDelegate(itemDelegate);
	NoFocusStyle* style = new NoFocusStyle(this);
	ui.cmbImage->setStyle(style);

	ui.edtResult->setAcceptRichText(false);

	qRegisterMetaType<__int64>("__int64");
	
	m_searchThd = new SearchImageThread;
	InitConnections();
}

AnalyzeImageDlg::~AnalyzeImageDlg()
{
	m_closed = true;

	if ( m_searchThd->isRunning() )
	{
		m_searchThd->terminate();
		m_searchThd->wait();
	}

	delete m_searchThd;
}

void AnalyzeImageDlg::InitConnections()
{
	connect(ui.btnBrowseSavePath, SIGNAL(clicked()), this, SLOT(OnBtnBrowseSavePathClicked()));
	connect(ui.btnRecovery, SIGNAL(clicked()), this, SLOT(OnBtnRecoveryClicked()));
	connect(ui.edtSearchStr, SIGNAL(textChanged(const QString&)), this, SLOT(OnEdtSearchStrTextChanged(const QString&)));
	connect(ui.btnSearch, SIGNAL(clicked()), this, SLOT(OnBtnSearchClicked()));
	connect(ui.btnExport, SIGNAL(clicked()), this, SLOT(OnBtnExportClicked()));

	connect(m_searchThd, SIGNAL(finished()), this, SLOT(SearchFinished()));
	connect(m_searchThd, SIGNAL(CurrentProgress(int)), this, SLOT(CurrentProgress(int)));
	connect(m_searchThd, SIGNAL(TotalProgress(int)), this, SLOT(TotalProgress(int)));
	connect(m_searchThd, SIGNAL(SearchResult(QString, __int64)), this, SLOT(SearchResult(QString, __int64)));

	connect(ui.btnBrowseImage, SIGNAL(clicked()), this, SLOT(OnBtnBrowseImageClicked()));
}

void AnalyzeImageDlg::Update()
{
	if ( m_searchThd->isRunning() )
	{
		m_searchThd->terminate();
		m_searchThd->wait();
	}

	ui.cmbImage->clear();
	ui.edtResult->clear();
	ui.edtSearchStr->clear();
	ui.edtSavePath->clear();
	ui.searchProgress->setValue(0);

	DataManager& dm = DataManager::GetInstance();
	std::wstring imagePath = dm.GetCurrentDevicePath() + L"\\Image\\*.*";

	WIN32_FIND_DATAW fd = {0};

	HANDLE hf = FindFirstFileW(imagePath.c_str(), &fd);

	if ( INVALID_HANDLE_VALUE == hf )
	{
		ui.image_frame_2->setEnabled(false);
		ui.image_frame_3->setEnabled(false);
		return;
	}

	do 
	{
		if ( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			continue;

		if ( 0 == wcscmp(fd.cFileName, L"ImageInfo") )
			continue;

		ui.cmbImage->insertItem(0, Utils::wtoq(fd.cFileName));

		DataManager& dm = DataManager::GetInstance();
		std::wstring fullPath = dm.GetCurrentDevicePath() + L"\\Image\\" + fd.cFileName;
		ui.cmbImage->setItemData(0, Utils::wtoq(fullPath));

	} while ( FindNextFileW(hf, &fd));

	FindClose(hf);

	if ( 0 == ui.cmbImage->count() )
	{
		ui.image_frame_2->setEnabled(false);
		ui.image_frame_3->setEnabled(false);
	}
	else
	{
		ui.image_frame_2->setEnabled(true);
		ui.image_frame_3->setEnabled(true);
	}

	ui.btnRecovery->setEnabled(false);
	ui.btnSearch->setEnabled(false);
}

void AnalyzeImageDlg::OnBtnBrowseSavePathClicked()
{
	QString str = QFileDialog::getExistingDirectory(this, Utils::stoq("选择存放目录"));

	if ( str.isEmpty() )
		return;

	str.replace("/", "\\");

	ui.edtSavePath->setText(str);

	ui.btnRecovery->setEnabled(true);
}

void AnalyzeImageDlg::OnBtnRecoveryClicked()
{
	wchar_t cmd[2048] = {0};
	std::wstring toolPath = Utils::GetExePath() + L"\\tools\\TestDisk\\photorec_win.exe";
	std::wstring outputDir = Utils::qtow(ui.edtSavePath->text());

	std::wstring inputFile = Utils::qtow(ui.cmbImage->itemData(ui.cmbImage->currentIndex()).toString());

	wsprintfW(cmd, 
		L"%s /debug /d \"%s\\recovery\" /cmd \"%s\" options,keep_corrupted_file,fileopt,everything,disable,jpg,enable,gif,enable,png,enable,sqlite,enable,wholespace,search",
		toolPath.c_str(),
		outputDir.c_str(),
		inputFile.c_str());

	PROCESS_INFORMATION piProcInfo = {0}; 
	STARTUPINFO siStartInfo = {0};
	
	if ( !CreateProcess(NULL, cmd, NULL, NULL, TRUE, NULL, NULL, NULL, &siStartInfo, &piProcInfo) )
	{
		char message[1024] = {0};
		sprintf(message, "启动 photorec_win 工具失败 [%d]", GetLastError());
		MsgBox::Information(0, Utils::stoq("提示"), Utils::stoq(message));
		return;
	}

	WaitForSingleObject(piProcInfo.hProcess, INFINITE);
	CloseHandle(piProcInfo.hThread);
	CloseHandle(piProcInfo.hProcess);

	char message[1024] = {0};
	int count = 0;

	std::wstring findStr = outputDir + L"\\recovery.1\\*.*";

	WIN32_FIND_DATAW fd = {0};
	HANDLE hf = FindFirstFileW(findStr.c_str(), &fd);

	if ( INVALID_HANDLE_VALUE != hf )
	{
		do 
		{
			if ( ! ( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )
				++count;

		} while ( FindNextFileW(hf, &fd) );

		FindClose(hf);
	}

	sprintf(message, "成功恢复了 %d 个文件", count);
	MsgBox::Information(0, Utils::stoq("提示"), Utils::stoq(message));

	std::wstring recoveryPath = outputDir + L"\\recovery.1";
	ShellExecute(NULL, L"open", recoveryPath.c_str(), NULL, NULL, SW_SHOW);
}

void AnalyzeImageDlg::OnEdtSearchStrTextChanged( const QString & text )
{
	if ( text.isEmpty() )
		ui.btnSearch->setEnabled(false);
	else
		ui.btnSearch->setEnabled(true);
}

void AnalyzeImageDlg::OnBtnSearchClicked()
{
	if ( ui.btnSearch->text() == Utils::stoq("开始搜索") )
	{
		ui.searchProgress->setValue(0);
		ui.edtResult->clear();
		std::wstring inputFile = Utils::qtow(ui.cmbImage->itemData(ui.cmbImage->currentIndex()).toString());
		m_searchThd->SetSearchParameters(inputFile, ui.edtSearchStr->text(), ui.btnUtf8->isChecked());
		m_searchThd->start();
		ui.btnExport->setEnabled(false);
		ui.btnSearch->setText(Utils::stoq("取消搜索"));
	}
	else
	{
		m_searchThd->terminate();
	}
}

void AnalyzeImageDlg::TotalProgress(int process)
{
	ui.searchProgress->setMaximum(process);
}

void AnalyzeImageDlg::CurrentProgress(int process)
{
	ui.searchProgress->setValue(process);
}

void AnalyzeImageDlg::SearchFinished()
{
	if ( m_closed )
		return;

	ui.btnExport->setEnabled(true);
	ui.btnSearch->setText(Utils::stoq("开始搜索"));
	ui.searchProgress->setValue(100);

	wchar_t msg[1024] = {0};
	wsprintfW(msg, L"搜索结束，共找到 %d 条记录", m_resultCount);
	MsgBox::Information(0, Utils::stoq("提示"), Utils::wtoq(msg));
	m_resultCount = 0;
}

void AnalyzeImageDlg::SearchResult(QString result, __int64 offset)
{
	++m_resultCount;

	wchar_t header[1024] = {0};
	wsprintfW(header, L"[%s]   id : %d    offset : %.8I64X\r\n-------------------------------------------------------------------------", 
		Utils::qtow(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).c_str(),
		m_resultCount, offset);
	ui.edtResult->append(Utils::wtoq(header));

	result += "\r\n\r\n";
	ui.edtResult->append(result);
}

void AnalyzeImageDlg::OnBtnExportClicked()
{
	if ( ui.edtResult->toPlainText().isEmpty() )
	{
		MsgBox::Information(0, Utils::stoq("提示"), Utils::stoq("无搜索结果用于导出"));
		return;
	}

	QString fileName = QFileDialog::getSaveFileName(this, Utils::stoq("输入导出文件名"), "export_result.txt", "text files(*.txt)");

	if ( fileName.isEmpty() )
		return;

	fileName.replace("/", "\\");

	QFile file(fileName);
	if ( !file.open(QIODevice::Truncate | QIODevice::WriteOnly) )
		return;

	QTextStream stream(&file);
	stream.setCodec("unicode");
	stream << ui.edtResult->toPlainText();

	file.close();

	wchar_t msg[1024] = {0};
	wsprintfW(msg, L"成功导出搜索结果\r\n%s", Utils::qtow(fileName).c_str());
	MsgBox::Information(0, Utils::stoq("提示"), Utils::wtoq(msg));
}

void AnalyzeImageDlg::OnBtnBrowseImageClicked()
{
	QString file = QFileDialog::getOpenFileName(this, Utils::stoq("选择镜像文件"));

	if ( file.isEmpty() )
		return;

	file.replace("/", "\\");

	QString fileName = file.section('\\', -1, -1);

	ui.cmbImage->insertItem(0, fileName);
	ui.cmbImage->setItemData(0, file);

	ui.cmbImage->setCurrentIndex(0);

	ui.image_frame_2->setEnabled(true);
	ui.image_frame_3->setEnabled(true);

	ui.edtResult->clear();
	ui.edtSearchStr->clear();

	if ( ui.edtSavePath->text().isEmpty() )
		ui.btnRecovery->setEnabled(false);

	ui.btnSearch->setEnabled(false);
}
