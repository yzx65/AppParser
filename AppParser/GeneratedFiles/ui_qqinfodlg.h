/********************************************************************************
** Form generated from reading UI file 'qqinfodlg.ui'
**
** Created: Wed Apr 1 13:49:51 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QQINFODLG_H
#define UI_QQINFODLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include "chatcontainer.h"

QT_BEGIN_NAMESPACE

class Ui_QQInfoDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *qq_frame_1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *cmbQQAccount;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnFront;
    QPushButton *btnBack;
    QHBoxLayout *horizontalLayout;
    QTreeView *trQQAccounts;
    QVBoxLayout *verticalLayout;
    QFrame *frame_accountInfo;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_qq_1;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_qq_number;
    QLabel *label_qq_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_qq_nickname;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_qq_3;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_qq_remark;
    QLabel *label_qq_4;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_qq_group;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_qq_5;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_qq_signature;
    ChatContainer *edtQQChat;

    void setupUi(QFrame *QQInfoDlg)
    {
        if (QQInfoDlg->objectName().isEmpty())
            QQInfoDlg->setObjectName(QString::fromUtf8("QQInfoDlg"));
        QQInfoDlg->resize(810, 625);
        verticalLayout_2 = new QVBoxLayout(QQInfoDlg);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        qq_frame_1 = new QFrame(QQInfoDlg);
        qq_frame_1->setObjectName(QString::fromUtf8("qq_frame_1"));
        qq_frame_1->setMinimumSize(QSize(0, 34));
        qq_frame_1->setMaximumSize(QSize(16777215, 34));
        horizontalLayout_2 = new QHBoxLayout(qq_frame_1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, 0, 10, 0);
        label = new QLabel(qq_frame_1);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        cmbQQAccount = new QComboBox(qq_frame_1);
        cmbQQAccount->setObjectName(QString::fromUtf8("cmbQQAccount"));
        cmbQQAccount->setMinimumSize(QSize(250, 20));
        cmbQQAccount->setMaximumSize(QSize(250, 20));
        cmbQQAccount->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(cmbQQAccount);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnFront = new QPushButton(qq_frame_1);
        btnFront->setObjectName(QString::fromUtf8("btnFront"));
        btnFront->setMinimumSize(QSize(25, 25));
        btnFront->setMaximumSize(QSize(25, 16777215));

        horizontalLayout_2->addWidget(btnFront);

        btnBack = new QPushButton(qq_frame_1);
        btnBack->setObjectName(QString::fromUtf8("btnBack"));
        btnBack->setMinimumSize(QSize(25, 25));
        btnBack->setMaximumSize(QSize(25, 16777215));

        horizontalLayout_2->addWidget(btnBack);


        verticalLayout_2->addWidget(qq_frame_1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        trQQAccounts = new QTreeView(QQInfoDlg);
        trQQAccounts->setObjectName(QString::fromUtf8("trQQAccounts"));
        trQQAccounts->setMinimumSize(QSize(0, 250));
        trQQAccounts->setMaximumSize(QSize(250, 16777215));
        trQQAccounts->setFocusPolicy(Qt::NoFocus);
        trQQAccounts->setStyleSheet(QString::fromUtf8(""));
        trQQAccounts->setFrameShape(QFrame::NoFrame);
        trQQAccounts->setEditTriggers(QAbstractItemView::NoEditTriggers);
        trQQAccounts->setSelectionBehavior(QAbstractItemView::SelectItems);
        trQQAccounts->setIconSize(QSize(24, 24));
        trQQAccounts->setIndentation(20);
        trQQAccounts->setRootIsDecorated(true);
        trQQAccounts->setHeaderHidden(true);
        trQQAccounts->header()->setMinimumSectionSize(400);

        horizontalLayout->addWidget(trQQAccounts);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_accountInfo = new QFrame(QQInfoDlg);
        frame_accountInfo->setObjectName(QString::fromUtf8("frame_accountInfo"));
        frame_accountInfo->setMinimumSize(QSize(0, 0));
        frame_accountInfo->setMaximumSize(QSize(16777215, 90));
        frame_accountInfo->setFrameShape(QFrame::StyledPanel);
        frame_accountInfo->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_accountInfo);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_qq_1 = new QLabel(frame_accountInfo);
        label_qq_1->setObjectName(QString::fromUtf8("label_qq_1"));
        label_qq_1->setMinimumSize(QSize(35, 25));
        label_qq_1->setMaximumSize(QSize(35, 25));
        label_qq_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_qq_1);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        label_qq_number = new QLabel(frame_accountInfo);
        label_qq_number->setObjectName(QString::fromUtf8("label_qq_number"));
        label_qq_number->setMinimumSize(QSize(0, 25));
        label_qq_number->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(label_qq_number);

        label_qq_2 = new QLabel(frame_accountInfo);
        label_qq_2->setObjectName(QString::fromUtf8("label_qq_2"));
        label_qq_2->setMinimumSize(QSize(0, 25));
        label_qq_2->setMaximumSize(QSize(50, 25));
        label_qq_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_qq_2);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        label_qq_nickname = new QLabel(frame_accountInfo);
        label_qq_nickname->setObjectName(QString::fromUtf8("label_qq_nickname"));
        label_qq_nickname->setMinimumSize(QSize(0, 25));
        label_qq_nickname->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(label_qq_nickname);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_qq_3 = new QLabel(frame_accountInfo);
        label_qq_3->setObjectName(QString::fromUtf8("label_qq_3"));
        label_qq_3->setMinimumSize(QSize(35, 25));
        label_qq_3->setMaximumSize(QSize(35, 25));
        label_qq_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_qq_3);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        label_qq_remark = new QLabel(frame_accountInfo);
        label_qq_remark->setObjectName(QString::fromUtf8("label_qq_remark"));
        label_qq_remark->setMinimumSize(QSize(0, 25));
        label_qq_remark->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_5->addWidget(label_qq_remark);

        label_qq_4 = new QLabel(frame_accountInfo);
        label_qq_4->setObjectName(QString::fromUtf8("label_qq_4"));
        label_qq_4->setMinimumSize(QSize(0, 25));
        label_qq_4->setMaximumSize(QSize(50, 25));
        label_qq_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_qq_4);

        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        label_qq_group = new QLabel(frame_accountInfo);
        label_qq_group->setObjectName(QString::fromUtf8("label_qq_group"));
        label_qq_group->setMinimumSize(QSize(0, 25));
        label_qq_group->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_5->addWidget(label_qq_group);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_qq_5 = new QLabel(frame_accountInfo);
        label_qq_5->setObjectName(QString::fromUtf8("label_qq_5"));
        label_qq_5->setMinimumSize(QSize(35, 25));
        label_qq_5->setMaximumSize(QSize(35, 25));
        label_qq_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_qq_5);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);

        label_qq_signature = new QLabel(frame_accountInfo);
        label_qq_signature->setObjectName(QString::fromUtf8("label_qq_signature"));
        label_qq_signature->setMinimumSize(QSize(0, 25));
        label_qq_signature->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_7->addWidget(label_qq_signature);


        verticalLayout_3->addLayout(horizontalLayout_7);


        verticalLayout->addWidget(frame_accountInfo);

        edtQQChat = new ChatContainer(QQInfoDlg);
        edtQQChat->setObjectName(QString::fromUtf8("edtQQChat"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(edtQQChat->sizePolicy().hasHeightForWidth());
        edtQQChat->setSizePolicy(sizePolicy);
        edtQQChat->setFrameShape(QFrame::StyledPanel);
        edtQQChat->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(edtQQChat);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(QQInfoDlg);

        QMetaObject::connectSlotsByName(QQInfoDlg);
    } // setupUi

    void retranslateUi(QFrame *QQInfoDlg)
    {
        QQInfoDlg->setWindowTitle(QApplication::translate("QQInfoDlg", "QQInfoDlg", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QQInfoDlg", "\345\275\223\345\211\215\350\264\246\345\217\267", 0, QApplication::UnicodeUTF8));
        btnFront->setText(QApplication::translate("QQInfoDlg", "<", 0, QApplication::UnicodeUTF8));
        btnBack->setText(QApplication::translate("QQInfoDlg", ">", 0, QApplication::UnicodeUTF8));
        label_qq_1->setText(QApplication::translate("QQInfoDlg", "\345\217\267\347\240\201", 0, QApplication::UnicodeUTF8));
        label_qq_number->setText(QString());
        label_qq_2->setText(QApplication::translate("QQInfoDlg", "\346\230\265\347\247\260", 0, QApplication::UnicodeUTF8));
        label_qq_nickname->setText(QString());
        label_qq_3->setText(QApplication::translate("QQInfoDlg", "\345\244\207\346\263\250", 0, QApplication::UnicodeUTF8));
        label_qq_remark->setText(QString());
        label_qq_4->setText(QApplication::translate("QQInfoDlg", "\345\210\206\347\273\204", 0, QApplication::UnicodeUTF8));
        label_qq_group->setText(QString());
        label_qq_5->setText(QApplication::translate("QQInfoDlg", "\347\255\276\345\220\215", 0, QApplication::UnicodeUTF8));
        label_qq_signature->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QQInfoDlg: public Ui_QQInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QQINFODLG_H
