#include "StdAfx.h"
#include "browserrecord.h"
#include "utils.h"

#include <QtGui>

BrowserRecord::BrowserRecord(QWidget *parent)
	: QFrame(parent)
{
	m_textBrowser = new QTextBrowser(this);
	m_textBrowser->setFrameStyle(QFrame::NoFrame);
	m_textBrowser->setOpenLinks(false);
	QHBoxLayout* layout = new QHBoxLayout;
	layout->addWidget(m_textBrowser);
	layout->setContentsMargins(0, 0, 0, 0);
	setLayout(layout);

	connect(
		m_textBrowser,
		SIGNAL(anchorClicked(const QUrl&)),
		this,
		SLOT(OnLinkClicked(const QUrl&)));
}

BrowserRecord::~BrowserRecord()
{

}

void BrowserRecord::ClearText()
{
	m_html = "";
	m_textBrowser->setHtml(m_html);
}

void BrowserRecord::AddHistory( QString time, QString text, QString url )
{
	QString msg = QString(
		"<p style='margin-left:10px;font-family:Microsoft Yahei;'>"
		"<span style='color:#444444;'>%1</span>"
		"</p>"
		"<p style='margin-left:10px;font-family:Microsoft Yahei;'>"
		"<span><a href='%2'>%3</a></span>"
		"</p>"
		"<p style='margin-left:10px;font-family:Microsoft Yahei;'>"
		"<span style='color:#aaaaaa'>%4</span>"
		"</p><p style=>&nbsp;</p>").arg(time).arg(url).arg(text).arg(url);

	m_html += msg;
}

void BrowserRecord::UpdateTextBrowser()
{
	m_textBrowser->setHtml(m_html);
}

void BrowserRecord::OnLinkClicked( const QUrl& url )
{
	std::wstring filePath = Utils::qtow(url.toString());

	ShellExecuteW(NULL, L"open", filePath.c_str(), NULL, NULL, SW_SHOW);
}
