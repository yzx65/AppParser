#include "StdAfx.h"
#include "navview.h"
#include "colordefines.h"

NavView::NavView(QWidget *parent)
	: QListView(parent)
{
	setStyleSheet(
		QString(
		"QListView{background-color:%1;"
		"border:0px solid %2;"
		"border-right-width:1px;}")
		.arg(ColorToString(color_child_normal))
		.arg(ColorToString(color_line)));
}

NavView::~NavView()
{

}
