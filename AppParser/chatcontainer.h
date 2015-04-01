#ifndef CHATCONTAINER_H
#define CHATCONTAINER_H

#include <QFrame>
#include <QTextBrowser>
#include <list>

class WaitDlg;

class ChatContainer : public QFrame
{
	Q_OBJECT

public:
	ChatContainer(QWidget *parent);
	~ChatContainer();

signals:
	void BackShow();
	void FrontShow();

	void BackHide();
	void FrontHide();

	void SetHtml(QTextBrowser* browser, QString* html);

public:
	void ClearText();

	void AddChatText(QString& sender, QString& time, QString& text);
	void AddChatPicture(QString& sender, QString& time, QString& picPath);
	void UpdateTextBrowser();

public slots:
	void Back();
	void Front();

private:
	void InitConnections();
	void InitTextBrowser();
	void UpdateHtml(QString& msg);
	void UpdateStatus();

private:
	QTextBrowser* m_textBrowser;
	QString m_html;
	std::list<QString> m_htmlList;
	int m_msgCount;
	std::list<QString>::iterator m_htmlPointer;
};

#endif // CHATCONTAINER_H
