
#include "FramelessDlg.h"
#include <QtGui>
#include <Windows.h>
#include <Windowsx.h>

#include "colordefines.h"
#include "utils.h"

FramelessDlg::FramelessDlg(QWidget *parent, unsigned int flag) :
    QDialog(parent),
	m_shadow(":/Image/window_shadow.png"),
	m_title(0),
	m_flag(flag)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    setAttribute(Qt::WA_TranslucentBackground);

	Utils::InitStyle(this);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setContentsMargins(5, 3, 5, 7);
	layout->setSpacing(0);
	setLayout(layout);

	InitTitleBar();
}

FramelessDlg::~FramelessDlg()
{
}

void FramelessDlg::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    QRect bottom(5, 136, 200, 7);
    QRect top(5, 0, 200, 3);
    QRect left(0, 3, 5, 133);
    QRect right(205, 3, 5, 133);
    QRect topRight(205, 0, 5, 3);
    QRect topLeft(0, 0, 5, 3);
    QRect bottomLeft(0, 136, 5, 7);
    QRect bottomRight(205, 136, 5, 7);

    QRect tBottom(5, this->height() - 7, this->width() - 10, 7);
    QRect tTop(5, 0, this->width() - 10, 3);
    QRect tLeft(0, 3, 5, this->height() - 10);
    QRect tRight(this->width() - 5, 3, 5, this->height() - 10);
    QRect tTopLeft(0, 0, 5, 3);
    QRect tTopRight(this->width() - 5, 0, 5, 3);
    QRect tBottomLeft(0, this->height() - 7, 5, 7);
    QRect tBottomRight(this->width() - 5, this->height() - 7, 5, 7);

    painter.drawPixmap(tBottom, m_shadow, bottom);
    painter.drawPixmap(tTop, m_shadow, top);
    painter.drawPixmap(tLeft, m_shadow, left);
    painter.drawPixmap(tRight, m_shadow, right);
    painter.drawPixmap(tTopRight, m_shadow, topRight);
    painter.drawPixmap(tTopLeft, m_shadow, topLeft);
    painter.drawPixmap(tBottomLeft, m_shadow, bottomLeft);
    painter.drawPixmap(tBottomRight, m_shadow, bottomRight);
}

void FramelessDlg::showEvent(QShowEvent *e)
{
    // Necessary! If not do this, when you minimize the window
    // and restore, the button will ignore the hover event.
    repaint();
}

bool FramelessDlg::winEvent(MSG *message, long *result)
{	
	switch (message->message) 
	{
	case WM_NCHITTEST:
		int xPos = GET_X_LPARAM(message->lParam) - this->frameGeometry().x();
		int yPos = GET_Y_LPARAM(message->lParam) - this->frameGeometry().y();

		QWidget* w = childAt(xPos, yPos);

		if ( w && 
			( w->objectName() == "closeBtn"
			|| w->objectName() == "minBtn" 
			|| w->objectName() == "menuBtn" ) )
		{
			return false;
		}

		if ( yPos >= 0 && yPos < 50 )
			*result = HTCAPTION;

		if ( xPos > 1 && xPos < 6 ) 
			*result = HTLEFT;
		if ( xPos > (this->width() - 6) && xPos < (this->width() - 1) )
			*result = HTRIGHT;
		if ( yPos > 1 && yPos < 6 )
			*result = HTTOP;
		if ( yPos > (this->height() - 6) && yPos < (this->height() - 1) )
			*result = HTBOTTOM;
		if ( xPos > 1 && xPos < 6 && yPos > 1 && yPos < 6 )
			*result = HTTOPLEFT;
		if ( xPos > (this->width() - 6) && xPos < (this->width() - 1) && yPos > 1 && yPos < 6 )
			*result = HTTOPRIGHT;
		if ( xPos > 1 && xPos < 6 && yPos > (this->height() - 6) && yPos < (this->height() - 1) )
			*result = HTBOTTOMLEFT;
		if ( xPos > (this->width() - 6) && xPos < (this->width() - 1) && yPos > (this->height() - 6) && yPos < (this->height() - 1) )
			*result = HTBOTTOMRIGHT;
		if ( *result )
			return true;

		break;
	}
	return false;
}

void FramelessDlg::SetDlg(QWidget* dlg)
{
	QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(this->layout());
	layout->addWidget(dlg);
}

void FramelessDlg::SetTitle(QString title)
{
	setWindowTitle(title);

	if ( m_title )
		m_title->setText(title);
}

void FramelessDlg::SetSubTitle(QString subTitle)
{
	if ( m_subTitle )
		m_subTitle->setText(subTitle);
}

void FramelessDlg::AddMenuAction(QAction *action)
{
	m_menu->addAction(action);
}

void FramelessDlg::RemoveMenuAction(QAction* action)
{
	m_menu->removeAction(action);
}

void FramelessDlg::AddSubMenu(QMenu* menu)
{
	QList<QAction*> actions = m_menu->actions();

	if ( actions.count() != 0 )
	{
		m_menu->insertMenu(actions[0], menu);
	}
	else
		m_menu->addMenu(menu);
}

void FramelessDlg::SetCloseEnable(bool enable)
{
	m_closeBtn->setVisible(enable);
}

void FramelessDlg::Resize(QSize size)
{
	this->setFixedSize(size);
}

void FramelessDlg::CenterWindow()
{
	int screenWidth = QApplication::desktop()->availableGeometry().width();
	int screenHeight = QApplication::desktop()->availableGeometry().height();

	this->move((screenWidth-this->width())/2, (screenHeight-this->height())/2);
}

void FramelessDlg::InitTitleBar()
{
	QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(this->layout());

	m_closeBtn = new QToolButton(this);
	QToolButton* minBtn = new QToolButton(this);
	QToolButton* menuBtn = new QToolButton(this);

	m_subTitle = new QLabel(this);
	m_subTitle->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

	m_closeBtn->setObjectName("closeBtn");
	minBtn->setObjectName("minBtn");
	menuBtn->setObjectName("menuBtn");
	m_subTitle->setObjectName("subTitle");

	menuBtn->setPopupMode(QToolButton::InstantPopup);
	m_menu = new QMenu(this);
	menuBtn->setMenu(m_menu);

	m_closeBtn->setFixedSize(27, 22);
	minBtn->setFixedSize(27, 22);
	menuBtn->setFixedSize(27, 22);
	m_subTitle->setFixedSize(400, 25);

	connect(m_closeBtn, SIGNAL(clicked()), this, SLOT(reject()));
	connect(m_closeBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(minBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));

	QFrame* tb = new QFrame(this);
	tb->setObjectName("titleBar");
	QHBoxLayout* tbLayout = new QHBoxLayout;
	m_title = new QLabel(this);
	m_title->setObjectName("label_title");
	m_title->setFixedSize(300, 25);

	tbLayout->addWidget(m_title);
	tbLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Fixed));

	if ( m_flag & SUB_TITLE )
		tbLayout->addWidget(m_subTitle);

	if ( m_flag & MENU_BUTTON )
		tbLayout->addWidget(menuBtn);

	if ( m_flag & MIN_BUTTON )
		tbLayout->addWidget(minBtn);

	if ( m_flag & CLOSE_BUTTON )
		tbLayout->addWidget(m_closeBtn);

	tb->setLayout(tbLayout);
	layout->addWidget(tb);
}