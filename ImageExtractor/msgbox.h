#ifndef MSGBOX_H
#define MSGBOX_H

#include <QWidget>
#include "ui_msgbox.h"

class MsgBox : public QFrame
{
	Q_OBJECT

public:
	MsgBox(QWidget *parent);
	~MsgBox();

	static void Information(QWidget* parent, QString title, QString message);

	void SetText(QString text);

signals:
	void OK();

private:
	Ui::MsgBox ui;
};

#endif // MSGBOX_H
