
#include "msgbox.h"
#include "framelessdlg.h"
#include "utils.h"

void MsgBox::Information(QWidget* parent, QString title, QString message)
{
	FramelessDlg container(0, CLOSE_BUTTON);
	MsgBox* dlg = new MsgBox(&container);
	container.SetDlg(dlg);
	container.setFixedSize(400, 200);
	container.SetTitle(title);
	dlg->SetText(message);
	connect(dlg, SIGNAL(OK()), &container, SLOT(accept()));

	container.exec();
}

MsgBox::MsgBox(QWidget *parent)
	: QFrame(parent)
{
	ui.setupUi(this);
	Utils::InitStyle(this);
	connect(ui.btnOK, SIGNAL(clicked()), this, SIGNAL(OK()));
}

MsgBox::~MsgBox()
{

}

void MsgBox::SetText( QString text )
{
	ui.lbMsg->setText(text);
}
