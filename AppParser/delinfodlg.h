#ifndef DELINFODLG_H
#define DELINFODLG_H

#include <QFrame>
#include "ui_delinfodlg.h"

class DelInfoDlg : public QFrame
{
	Q_OBJECT

public:

	enum InfoType{SMS, CONTACT, RECORD};

	DelInfoDlg(QWidget *parent, InfoType type);
	~DelInfoDlg();

public:
	void Update();

private:
	Ui::DelInfoDlg ui;
	int m_type;
};

#endif // DELINFODLG_H
