#ifndef BROWSERRECORD_H
#define BROWSERRECORD_H

#include <QFrame>
#include <QTextBrowser>

class BrowserRecord : public QFrame
{
	Q_OBJECT

public:
	BrowserRecord(QWidget *parent);
	~BrowserRecord();

public:
	void ClearText();
	void AddHistory(QString time, QString text, QString url);
	void UpdateTextBrowser();

public slots:
	void OnLinkClicked(const QUrl& url);

private:
	QTextBrowser* m_textBrowser;
	QString m_html;
};

#endif // BROWSERRECORD_H
