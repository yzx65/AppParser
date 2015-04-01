#include "StdAfx.h"
#include "HistoryDelegate.h"

HistoryDelegate::HistoryDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{

}

HistoryDelegate::~HistoryDelegate()
{

}

QSize HistoryDelegate::sizeHint( const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	return QSize(400, 50);
}

void HistoryDelegate::paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	QString text = index.data(Qt::DisplayRole).toString();
	QString name = text.section('\n', 0, 0);
	QString url = text.section('\n', 1, 1);
	QString time = text.section('\n', 2, 2);

	QString firstLine = time.isEmpty() ? name : time + " " + name;
	QString secondLine = url;

	QPen h1(QColor(67, 95, 185));
	painter->setPen(h1);

	QFont firstLineFont("Microsoft Yahei", 10);

	if ( option.state & QStyle::State_MouseOver )
		firstLineFont.setUnderline(true);
	else
		firstLineFont.setUnderline(false);

	painter->setFont(firstLineFont);

	if ( secondLine.isEmpty() )
	{
		QRect r1 = option.rect;
		r1.setX(10);
		painter->drawText(r1, Qt::AlignLeft | Qt::AlignVCenter, firstLine);
		return;
	}

	QRect r1 = option.rect;
	r1.setHeight(option.rect.height() / 2 - 5);
	r1.setY(option.rect.y());
	r1.setX(10);
	r1.moveTop(option.rect.top() + 5);
	painter->drawText(r1, Qt::AlignLeft | Qt::AlignVCenter, firstLine);

	QPen h2(QColor(180, 180, 180));
	painter->setPen(h2);

	QFont secLineFont("Microsoft Yahei", 10);
	painter->setFont(secLineFont);

	QRect r2 = option.rect;
	r2.setHeight(option.rect.height() / 2 - 5);
	r2.setY(option.rect.y());
	r2.moveBottom(option.rect.bottom() - 5);
	r2.setX(10);
	painter->drawText(r2, Qt::AlignLeft | Qt::AlignVCenter, secondLine);
}
