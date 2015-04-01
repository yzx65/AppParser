#include "StdAfx.h"
#include "backuppassworddlg.h"

#include "framelessdlg.h"

#include <Windows.h>
#include "utils.h"

int BackupPasswordDlg::Invoke(QString title, char* password)
{
	FramelessDlg container(0, CLOSE_BUTTON);
	BackupPasswordDlg* dlg = new BackupPasswordDlg(&container, password);
	container.SetTitle(title);

	connect(dlg, SIGNAL(OK()), &container, SLOT(accept()));

	container.SetDlg(dlg);
	container.setFixedSize(300, 180);
	container.CenterWindow();

	return container.exec();
}

BackupPasswordDlg::BackupPasswordDlg(QWidget *parent, char* password)
	: QFrame(parent)
	, m_password(password)
{
	ui.setupUi(this);
	Utils::InitStyle(this);
	ui.btnOK->setEnabled(false);

	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOKClicked()));
	connect(ui.edtPassword, SIGNAL(textChanged(QString)), this, SLOT(OnTextChanged(QString)));
}

BackupPasswordDlg::~BackupPasswordDlg()
{

}

void BackupPasswordDlg::OnTextChanged(QString text)
{
	ui.btnOK->setEnabled(!text.isEmpty());
}

void BackupPasswordDlg::OnBtnOKClicked()
{
	wsprintfA(m_password, "%s", ui.edtPassword->text().toLocal8Bit().data());
	emit OK();
}