#ifndef IMAGEEXTRACTOR_H
#define IMAGEEXTRACTOR_H

#include <QtGui>
#include "ui_imageextractor.h"

class WorkThread : public QThread
{
	Q_OBJECT

signals:

	void emitStatus(QString status);
	void emitProcess(int value);
	void emitInformation(QString info);

public:
	WorkThread(QObject* parent = 0);
	~WorkThread();

	void SetParameters(std::wstring srcPath, std::wstring dstPath, bool extractFile, bool mergeFile, bool extractImageFile);

	void SetStatus(QString status)
	{
		emitStatus(status);
	}

	void SetInformation(QString info)
	{
		emitInformation(info);
	}

protected:
	void run();

private:
	bool ExtractFile();
	bool ExtractImage();

private:
	bool m_cancle;
	std::wstring m_srcPath;
	std::wstring m_dstPath;
	bool m_extractFile;
	bool m_mergeFile;
	bool m_extractImageFile;
};

class ImageExtractor : public QFrame
{
	Q_OBJECT

public:
	ImageExtractor(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ImageExtractor();

public slots:

	void OnBtnBrowseOutputPathClicked();

	void OnParameterChanged();

	void OnBtnStartClicked();

	void OnEmitWorkStatus(QString status);
	void OnEmitWorkProcess(int process);
	void OnEmitWorkInformation(QString info);

	void OnWorkDone();

private:
	void InitConnection();
	void InitTaskList();
	void InitDefaultPath();

private:
	Ui::ImageExtractorClass ui;
	WorkThread* m_workThread;
	std::wstring m_defaultPath;
};

#endif // IMAGEEXTRACTOR_H
