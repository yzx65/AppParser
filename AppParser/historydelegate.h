#ifndef HISTORYDELEGATE_H
#define HISTORYDELEGATE_H

#include <QStyledItemDelegate>

class HistoryDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	HistoryDelegate(QObject *parent);
	~HistoryDelegate();

public:
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const ;
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
	
};

#endif // HISTORYDELEGATE_H
