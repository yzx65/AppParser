#include "stdafx.h"
#include "waitdlg.h"

#include <QtGui>

const int OutRadius = 20;
const int InRadius = 10;

WaitDlg::WaitDlg(QWidget *parent) :
    QWidget(parent), angle(0),displayMode(IMAGE), m_opacity(150)
{
    this->setWindowModality(Qt::ApplicationModal);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));
    this->setFixedSize(parent->size());
    circleCenter = QPoint(parent->width()/2, parent->height()/2);
    timer.start(1000/30);
}

void WaitDlg::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

	if ( WaitDlg::IMAGE == displayMode)
		DrawCircle(&painter);
	else
		DrawText(&painter);
}

void WaitDlg::DrawCircle(QPainter* painter)
{
	painter->fillRect(0, 0, this->width(), this->height(), QBrush(QColor(255,255,255,m_opacity)));
    QRectF outRect(circleCenter.x()-OutRadius, circleCenter.y()-OutRadius, OutRadius*2, OutRadius*2);
    QRectF inRect(circleCenter.x()-InRadius, circleCenter.y()-InRadius, InRadius*2, InRadius*2);

    QPainterPath path;
    path.addEllipse(outRect);
    path.addEllipse(inRect);
    painter->setClipPath(path);

    QPen pen(Qt::white);
    painter->setPen(pen);

    QConicalGradient gradient(circleCenter, angle);
    gradient.setColorAt(0, QColor(130, 170, 255, 255));
    gradient.setColorAt(1, QColor(130, 170, 255, 0));

    QBrush brush(gradient);

    painter->setBrush(brush);
    painter->drawEllipse(circleCenter.x()-OutRadius, circleCenter.y()-OutRadius, OutRadius*2, OutRadius*2);
}

void WaitDlg::timeout()
{
    angle = (angle+360-12) % 360;
    update();
}

void WaitDlg::SetDisplayMode( WaitDlg::DisplayMode mode )
{
	displayMode = mode;
}

void WaitDlg::DrawText( QPainter* painter )
{
	painter->fillRect(0, 0, this->width(), this->height(), QBrush(QColor(255,255,255,m_opacity)));

	QPen pen(QColor(100, 120, 255, 255));
	QFont font(QFont("Microsoft Yahei", 20));
	painter->setFont(font);
	painter->setPen(pen);
	painter->drawText(this->rect(), Qt::AlignCenter, displayText);
}

void WaitDlg::SetText( QString text )
{
	displayText = text;
}

void WaitDlg::SetSize( QSize size )
{
	this->setFixedSize(size);
	circleCenter = QPoint(size.width()/2, size.height()/2);
}

void WaitDlg::SetOpacity(int opacity)
{
	m_opacity = opacity;
}
