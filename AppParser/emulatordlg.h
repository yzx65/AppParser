#ifndef EMULATORDLG_H
#define EMULATORDLG_H

#include <QFrame>
#include "ui_emulatordlg.h"

class IOS_EmulatorDlg;
class Android_EmulatorDlg;

class EmulatorDlg : public QFrame
{
	Q_OBJECT

public:
	EmulatorDlg(QWidget *parent = 0);
	~EmulatorDlg();

public:
	void Update();

private:

	Ui::EmulatorDlg ui;
	Android_EmulatorDlg* m_android;
	IOS_EmulatorDlg* m_ios;
};

#endif // EMULATORDLG_H
