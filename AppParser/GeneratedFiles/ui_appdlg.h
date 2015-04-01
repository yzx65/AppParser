/********************************************************************************
** Form generated from reading UI file 'appdlg.ui'
**
** Created: Wed Apr 1 16:19:41 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPDLG_H
#define UI_APPDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QStackedWidget>
#include <QtGui/QVBoxLayout>
#include "navview.h"

QT_BEGIN_NAMESPACE

class Ui_AppDlg
{
public:
    QHBoxLayout *horizontalLayout_2;
    NavView *lstNav;
    QVBoxLayout *verticalLayout;
    QFrame *frame_header_bar;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *edtFilter;
    QStackedWidget *stkApp;

    void setupUi(QFrame *AppDlg)
    {
        if (AppDlg->objectName().isEmpty())
            AppDlg->setObjectName(QString::fromUtf8("AppDlg"));
        AppDlg->resize(746, 544);
        AppDlg->setStyleSheet(QString::fromUtf8("QFrame{\n"
"	background-color: white;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(AppDlg);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lstNav = new NavView(AppDlg);
        lstNav->setObjectName(QString::fromUtf8("lstNav"));
        lstNav->setMinimumSize(QSize(200, 180));
        lstNav->setMaximumSize(QSize(200, 16777215));
        lstNav->setFrameShape(QFrame::NoFrame);

        horizontalLayout_2->addWidget(lstNav);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_header_bar = new QFrame(AppDlg);
        frame_header_bar->setObjectName(QString::fromUtf8("frame_header_bar"));
        frame_header_bar->setFrameShape(QFrame::NoFrame);
        frame_header_bar->setFrameShadow(QFrame::Raised);
        frame_header_bar->setLineWidth(0);
        horizontalLayout = new QHBoxLayout(frame_header_bar);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(4, 0, 0, 0);
        label = new QLabel(frame_header_bar);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(25, 24));
        label->setPixmap(QPixmap(QString::fromUtf8(":/Image/search.png")));

        horizontalLayout->addWidget(label);

        edtFilter = new QLineEdit(frame_header_bar);
        edtFilter->setObjectName(QString::fromUtf8("edtFilter"));
        edtFilter->setMinimumSize(QSize(0, 34));
        edtFilter->setMaximumSize(QSize(16777, 35));

        horizontalLayout->addWidget(edtFilter);


        verticalLayout->addWidget(frame_header_bar);

        stkApp = new QStackedWidget(AppDlg);
        stkApp->setObjectName(QString::fromUtf8("stkApp"));

        verticalLayout->addWidget(stkApp);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(AppDlg);

        QMetaObject::connectSlotsByName(AppDlg);
    } // setupUi

    void retranslateUi(QFrame *AppDlg)
    {
        AppDlg->setWindowTitle(QApplication::translate("AppDlg", "AppDlg", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        edtFilter->setPlaceholderText(QApplication::translate("AppDlg", "\350\276\223\345\205\245\345\205\263\351\224\256\345\255\227\350\277\233\350\241\214\346\220\234\347\264\242\357\274\210\345\247\223\345\220\215\343\200\201\347\224\265\350\257\235\345\217\267\347\240\201\343\200\201QQ \345\217\267\357\274\211 ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AppDlg: public Ui_AppDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPDLG_H
