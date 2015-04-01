/********************************************************************************
** Form generated from reading UI file 'emulatordlg.ui'
**
** Created: Wed Apr 1 13:49:51 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMULATORDLG_H
#define UI_EMULATORDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QStackedWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EmulatorDlg
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *stack;

    void setupUi(QFrame *EmulatorDlg)
    {
        if (EmulatorDlg->objectName().isEmpty())
            EmulatorDlg->setObjectName(QString::fromUtf8("EmulatorDlg"));
        EmulatorDlg->resize(400, 300);
        verticalLayout = new QVBoxLayout(EmulatorDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stack = new QStackedWidget(EmulatorDlg);
        stack->setObjectName(QString::fromUtf8("stack"));

        verticalLayout->addWidget(stack);


        retranslateUi(EmulatorDlg);

        QMetaObject::connectSlotsByName(EmulatorDlg);
    } // setupUi

    void retranslateUi(QFrame *EmulatorDlg)
    {
        EmulatorDlg->setWindowTitle(QApplication::translate("EmulatorDlg", "EmulatorDlg", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EmulatorDlg: public Ui_EmulatorDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMULATORDLG_H
