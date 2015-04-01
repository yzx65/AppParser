#ifndef BASICINFODLG_H
#define BASICINFODLG_H

#include <QFrame>
#include "ui_basicinfodlg.h"

class BasicInfoDlg : public QFrame
{
	Q_OBJECT

public:
	BasicInfoDlg(QWidget *parent = 0);
	~BasicInfoDlg();

public:
	void Update();

private:
	Ui::BasicInfoDlg ui;
};

#endif // BASICINFODLG_H
