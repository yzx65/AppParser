#ifndef SELECTEMULATORDLG_H
#define SELECTEMULATORDLG_H

#include <QFrame>
#include "ui_selectemulatordlg.h"

class SelectEmulatorDlg : public QFrame
{
	Q_OBJECT

public:
	static int Invoke();

public:
	SelectEmulatorDlg(QWidget *parent = 0);
	~SelectEmulatorDlg();

signals:
	void OK();

public slots:
	void OnLstEmulatorsItemDoubleClicked(QListWidgetItem* item);

private:
	void InitVirtualMachine();

private:
	Ui::SelectEmulatorDlg ui;
};

#endif // SELECTEMULATORDLG_H
