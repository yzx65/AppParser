/********************************************************************************
** Form generated from reading UI file 'delinfodlg.ui'
**
** Created: Wed Apr 1 16:19:40 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELINFODLG_H
#define UI_DELINFODLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DelInfoDlg
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *content;

    void setupUi(QFrame *DelInfoDlg)
    {
        if (DelInfoDlg->objectName().isEmpty())
            DelInfoDlg->setObjectName(QString::fromUtf8("DelInfoDlg"));
        DelInfoDlg->resize(400, 300);
        DelInfoDlg->setStyleSheet(QString::fromUtf8("QFrame#DelInfoDlg\n"
"{\n"
"	background-color:white;\n"
"}"));
        verticalLayout = new QVBoxLayout(DelInfoDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        content = new QTextEdit(DelInfoDlg);
        content->setObjectName(QString::fromUtf8("content"));
        content->setFrameShape(QFrame::NoFrame);
        content->setReadOnly(true);

        verticalLayout->addWidget(content);


        retranslateUi(DelInfoDlg);

        QMetaObject::connectSlotsByName(DelInfoDlg);
    } // setupUi

    void retranslateUi(QFrame *DelInfoDlg)
    {
        DelInfoDlg->setWindowTitle(QApplication::translate("DelInfoDlg", "DelInfoDlg", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DelInfoDlg: public Ui_DelInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELINFODLG_H
