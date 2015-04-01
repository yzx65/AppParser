/********************************************************************************
** Form generated from reading UI file 'parsedlg.ui'
**
** Created: Wed Apr 1 13:49:51 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARSEDLG_H
#define UI_PARSEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ParseDlg
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lbStatus;
    QProgressBar *progress;

    void setupUi(QFrame *ParseDlg)
    {
        if (ParseDlg->objectName().isEmpty())
            ParseDlg->setObjectName(QString::fromUtf8("ParseDlg"));
        ParseDlg->resize(400, 55);
        verticalLayout = new QVBoxLayout(ParseDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lbStatus = new QLabel(ParseDlg);
        lbStatus->setObjectName(QString::fromUtf8("lbStatus"));

        verticalLayout->addWidget(lbStatus);

        progress = new QProgressBar(ParseDlg);
        progress->setObjectName(QString::fromUtf8("progress"));
        progress->setMaximumSize(QSize(16777215, 5));
        progress->setValue(24);
        progress->setTextVisible(false);

        verticalLayout->addWidget(progress);


        retranslateUi(ParseDlg);

        QMetaObject::connectSlotsByName(ParseDlg);
    } // setupUi

    void retranslateUi(QFrame *ParseDlg)
    {
        ParseDlg->setWindowTitle(QApplication::translate("ParseDlg", "ParseDlg", 0, QApplication::UnicodeUTF8));
        lbStatus->setText(QApplication::translate("ParseDlg", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ParseDlg: public Ui_ParseDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARSEDLG_H
