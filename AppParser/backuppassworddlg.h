#ifndef BACKUPPASSWORDDLG_H
#define BACKUPPASSWORDDLG_H

#include <QFrame>
#include "ui_backuppassworddlg.h"

class BackupPasswordDlg : public QFrame
{
	Q_OBJECT

public:
	BackupPasswordDlg(QWidget* parent, char* password);
	~BackupPasswordDlg();

public:
	static int Invoke(QString title, char* password);

signals:
	void OK();

public slots:
	void OnTextChanged(QString text);
	void OnBtnOKClicked();

private:
	Ui::BackupPasswordDlg ui;
	char* m_password;
};

#endif // BACKUPPASSWORDDLG_H
