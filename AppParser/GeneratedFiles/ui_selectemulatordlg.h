/********************************************************************************
** Form generated from reading UI file 'selectemulatordlg.ui'
**
** Created: Wed Apr 1 13:49:51 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTEMULATORDLG_H
#define UI_SELECTEMULATORDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SelectEmulatorDlg
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *lstEmulators;

    void setupUi(QFrame *SelectEmulatorDlg)
    {
        if (SelectEmulatorDlg->objectName().isEmpty())
            SelectEmulatorDlg->setObjectName(QString::fromUtf8("SelectEmulatorDlg"));
        SelectEmulatorDlg->resize(400, 300);
        SelectEmulatorDlg->setStyleSheet(QString::fromUtf8("QFrame#SelectEmulatorDlg\n"
"{\n"
"	background-color:white;\n"
"}"));
        verticalLayout = new QVBoxLayout(SelectEmulatorDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lstEmulators = new QListWidget(SelectEmulatorDlg);
        lstEmulators->setObjectName(QString::fromUtf8("lstEmulators"));
        lstEmulators->setFrameShape(QFrame::NoFrame);
        lstEmulators->setAlternatingRowColors(true);

        verticalLayout->addWidget(lstEmulators);


        retranslateUi(SelectEmulatorDlg);

        QMetaObject::connectSlotsByName(SelectEmulatorDlg);
    } // setupUi

    void retranslateUi(QFrame *SelectEmulatorDlg)
    {
        SelectEmulatorDlg->setWindowTitle(QApplication::translate("SelectEmulatorDlg", "SelectEmulatorDlg", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SelectEmulatorDlg: public Ui_SelectEmulatorDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTEMULATORDLG_H
