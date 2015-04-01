#include "stdafx.h"
#include "nofocusstyle.h"

NoFocusStyle::NoFocusStyle(QObject *parent)
	: QWindowsVistaStyle()
{

}

NoFocusStyle::~NoFocusStyle()
{

}

void NoFocusStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option,
								 QPainter *painter, const QWidget *widget) const
{
	if (QStyle::PE_FrameFocusRect == element && widget )
	{
		return;
	}
	else
	{
		QCommonStyle::drawPrimitive(element, option, painter, widget);
	}
}
