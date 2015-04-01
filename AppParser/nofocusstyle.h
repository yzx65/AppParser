/*!
	Description : 用于去除虚线框
	Author		: Ruining Song
	Date		: 2013.12.11
	Remark		:
*/

#ifndef NOFOCUSSTYLE_H
#define NOFOCUSSTYLE_H

#include <QWindowsVistaStyle>

class NoFocusStyle : public QWindowsVistaStyle
{
	Q_OBJECT

public:
	NoFocusStyle(QObject *parent);
	~NoFocusStyle();

protected:
	void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
		QPainter *painter, const QWidget *widget) const;

private:
	
};

#endif // NOFOCUSSTYLE_H
