/********************************************************************************
** Form generated from reading UI file 'smsinfodlg.ui'
**
** Created: Wed Apr 1 13:49:50 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMSINFODLG_H
#define UI_SMSINFODLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "chatcontainer.h"

QT_BEGIN_NAMESPACE

class Ui_SmsInfoDlg
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QFrame *frame_left;
    QVBoxLayout *verticalLayout_2;
    QListView *lstSmsFriends;
    QFrame *frame_right;
    QVBoxLayout *verticalLayout;
    ChatContainer *edtSmsRecord;
    QFrame *frame_chat_nav;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnFront;
    QPushButton *btnBack;

    void setupUi(QFrame *SmsInfoDlg)
    {
        if (SmsInfoDlg->objectName().isEmpty())
            SmsInfoDlg->setObjectName(QString::fromUtf8("SmsInfoDlg"));
        SmsInfoDlg->resize(700, 443);
        verticalLayout_3 = new QVBoxLayout(SmsInfoDlg);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame_left = new QFrame(SmsInfoDlg);
        frame_left->setObjectName(QString::fromUtf8("frame_left"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_left->sizePolicy().hasHeightForWidth());
        frame_left->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(frame_left);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lstSmsFriends = new QListView(frame_left);
        lstSmsFriends->setObjectName(QString::fromUtf8("lstSmsFriends"));
        lstSmsFriends->setMinimumSize(QSize(200, 0));
        lstSmsFriends->setMaximumSize(QSize(200, 16777215));
        lstSmsFriends->setFocusPolicy(Qt::NoFocus);
        lstSmsFriends->setFrameShape(QFrame::NoFrame);
        lstSmsFriends->setEditTriggers(QAbstractItemView::NoEditTriggers);
        lstSmsFriends->setAlternatingRowColors(true);

        verticalLayout_2->addWidget(lstSmsFriends);


        horizontalLayout->addWidget(frame_left);

        frame_right = new QFrame(SmsInfoDlg);
        frame_right->setObjectName(QString::fromUtf8("frame_right"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_right->sizePolicy().hasHeightForWidth());
        frame_right->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(frame_right);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        edtSmsRecord = new ChatContainer(frame_right);
        edtSmsRecord->setObjectName(QString::fromUtf8("edtSmsRecord"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(edtSmsRecord->sizePolicy().hasHeightForWidth());
        edtSmsRecord->setSizePolicy(sizePolicy2);
        edtSmsRecord->setFrameShape(QFrame::StyledPanel);
        edtSmsRecord->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(edtSmsRecord);

        frame_chat_nav = new QFrame(frame_right);
        frame_chat_nav->setObjectName(QString::fromUtf8("frame_chat_nav"));
        frame_chat_nav->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_2 = new QHBoxLayout(frame_chat_nav);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 5, 10, 5);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnFront = new QPushButton(frame_chat_nav);
        btnFront->setObjectName(QString::fromUtf8("btnFront"));
        btnFront->setMinimumSize(QSize(25, 25));
        btnFront->setMaximumSize(QSize(25, 16777215));

        horizontalLayout_2->addWidget(btnFront);

        btnBack = new QPushButton(frame_chat_nav);
        btnBack->setObjectName(QString::fromUtf8("btnBack"));
        btnBack->setMinimumSize(QSize(25, 25));
        btnBack->setMaximumSize(QSize(25, 16777215));

        horizontalLayout_2->addWidget(btnBack);


        verticalLayout->addWidget(frame_chat_nav);


        horizontalLayout->addWidget(frame_right);


        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(SmsInfoDlg);

        QMetaObject::connectSlotsByName(SmsInfoDlg);
    } // setupUi

    void retranslateUi(QFrame *SmsInfoDlg)
    {
        SmsInfoDlg->setWindowTitle(QApplication::translate("SmsInfoDlg", "SmsInfoDlg", 0, QApplication::UnicodeUTF8));
        btnFront->setText(QApplication::translate("SmsInfoDlg", "<", 0, QApplication::UnicodeUTF8));
        btnBack->setText(QApplication::translate("SmsInfoDlg", ">", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SmsInfoDlg: public Ui_SmsInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMSINFODLG_H
