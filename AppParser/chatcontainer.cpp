#include "StdAfx.h"
#include "chatcontainer.h"
#include "utils.h"

#include <QtGui>

const int MessagePerPage = 30;

ChatContainer::ChatContainer(QWidget *parent)
	: QFrame(parent)
	, m_msgCount(0)
{
	m_htmlPointer = m_htmlList.begin();

	InitConnections();
	InitTextBrowser();
}

ChatContainer::~ChatContainer()
{
}

void ChatContainer::InitConnections()
{
}

void ChatContainer::InitTextBrowser()
{
	m_textBrowser = new QTextBrowser(this);
	m_textBrowser->setFrameStyle(QFrame::NoFrame);
	QHBoxLayout* layout = new QHBoxLayout;
	layout->addWidget(m_textBrowser);
	layout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(layout);
}

void ChatContainer::ClearText()
{
	m_html = "";
	m_msgCount = 0;
	m_htmlList.clear();
	m_textBrowser->setHtml(m_html);
}

void ChatContainer::AddChatText( QString& sender, QString& time, QString& text )
{
	//text.replace("\n", "<br/>");
	QString msg = 
		QString(
		"<p style='margin-left:10px;font-family:Microsoft Yahei;'><span style='color:#0055ff;font-size:13px;'>%1&nbsp;&nbsp;&nbsp;</span>"
		"<span style='color:#999999;font-size:11px;'>%2</span></p>"
		"<p style='margin-left:10px;font-family:Microsoft Yahei;font-size:13px;color:rgb(58,58,58);'>%3</p>")
		.arg(sender).arg(time).arg(text);

	UpdateHtml(msg);
}

void ChatContainer::UpdateHtml(QString& msg)
{
	m_html += msg;
	++m_msgCount;

	if ( m_msgCount == MessagePerPage )
	{
		m_htmlList.push_back(m_html);
		m_html = "";
		m_msgCount = 0;
	}
}

void ChatContainer::AddChatPicture( QString& sender, QString& time, QString& picPath )
{
	picPath = picPath.replace('\\', '/');

	QString msg = 
		QString(
		"<p style='margin-left:10px;font-family:Microsoft Yahei;'><span style='color:#0055ff;font-size:13px;'>%1&nbsp;&nbsp;&nbsp;</span>"
		"<span style='color:#999999;font-size:11px;'>%2</span></p>"
		"<p style='margin-left:10px'><img src='%3'></img></p>")
		.arg(sender).arg(time).arg(picPath);

	UpdateHtml(msg);
}

void ChatContainer::UpdateTextBrowser()
{
	if ( m_html != "" )
		m_htmlList.push_back(m_html);

	if ( m_htmlList.empty() )
	{
		UpdateStatus();
		return;
	}

	m_htmlPointer = m_htmlList.begin();

	setUpdatesEnabled(false);
	m_textBrowser->setHtml(*m_htmlPointer);
	setUpdatesEnabled(true);

	UpdateStatus();
}

void ChatContainer::Back()
{
	++m_htmlPointer;
	m_textBrowser->setHtml(*m_htmlPointer);
	
	UpdateStatus();
}

void ChatContainer::Front()
{
	--m_htmlPointer;
	m_textBrowser->setHtml(*m_htmlPointer);

	UpdateStatus();
}

void ChatContainer::UpdateStatus()
{
	FrontShow();
	BackShow();

	if ( m_htmlList.empty() )
	{
		FrontHide();
		BackHide();
		return;
	}

	std::list<QString>::iterator next = m_htmlPointer;
	++next;

	if ( next == m_htmlList.end() )
		BackHide();

	if ( m_htmlPointer == m_htmlList.begin() )
		FrontHide();
}