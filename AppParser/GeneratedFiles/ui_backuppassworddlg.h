/********************************************************************************
** Form generated from reading UI file 'backuppassworddlg.ui'
**
** Created: Wed Apr 1 13:49:51 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACKUPPASSWORDDLG_H
#define UI_BACKUPPASSWORDDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BackupPasswordDlg
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame_1;
    QHBoxLayout *horizontalLayout;
    QLineEdit *edtPassword;
    QFrame *frame_backup;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOK;

    void setupUi(QFrame *BackupPasswordDlg)
    {
        if (BackupPasswordDlg->objectName().isEmpty())
            BackupPasswordDlg->setObjectName(QString::fromUtf8("BackupPasswordDlg"));
        BackupPasswordDlg->resize(391, 119);
        BackupPasswordDlg->setStyleSheet(QString::fromUtf8("QFrame#BackupPasswordDlg\n"
"{\n"
"	background-color:white;\n"
"}"));
        verticalLayout = new QVBoxLayout(BackupPasswordDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_1 = new QFrame(BackupPasswordDlg);
        frame_1->setObjectName(QString::fromUtf8("frame_1"));
        frame_1->setMinimumSize(QSize(0, 69));
        frame_1->setMaximumSize(QSize(16777215, 69));
        frame_1->setStyleSheet(QString::fromUtf8("QFrame#frame_1\n"
"{\n"
"	background-color:white;\n"
"}"));
        horizontalLayout = new QHBoxLayout(frame_1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, -1, 10, -1);
        edtPassword = new QLineEdit(frame_1);
        edtPassword->setObjectName(QString::fromUtf8("edtPassword"));
        edtPassword->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(edtPassword);


        verticalLayout->addWidget(frame_1);

        frame_backup = new QFrame(BackupPasswordDlg);
        frame_backup->setObjectName(QString::fromUtf8("frame_backup"));
        frame_backup->setMinimumSize(QSize(0, 50));
        frame_backup->setMaximumSize(QSize(16777215, 50));
        frame_backup->setStyleSheet(QString::fromUtf8("QFrame#frame_backup\n"
"{\n"
"	background-color:white;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(frame_backup);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(9, 0, 9, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnOK = new QPushButton(frame_backup);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setMinimumSize(QSize(70, 28));
        btnOK->setMaximumSize(QSize(70, 28));

        horizontalLayout_2->addWidget(btnOK);


        verticalLayout->addWidget(frame_backup);


        retranslateUi(BackupPasswordDlg);

        QMetaObject::connectSlotsByName(BackupPasswordDlg);
    } // setupUi

    void retranslateUi(QFrame *BackupPasswordDlg)
    {
        BackupPasswordDlg->setWindowTitle(QApplication::translate("BackupPasswordDlg", "BackupPasswordDlg", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("BackupPasswordDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BackupPasswordDlg: public Ui_BackupPasswordDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACKUPPASSWORDDLG_H
