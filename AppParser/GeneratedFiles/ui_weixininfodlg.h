/********************************************************************************
** Form generated from reading UI file 'weixininfodlg.ui'
**
** Created: Wed Apr 1 16:19:39 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEIXININFODLG_H
#define UI_WEIXININFODLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "chatcontainer.h"

QT_BEGIN_NAMESPACE

class Ui_WeixinInfoDlg
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *weixin_frame_1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QComboBox *cmbWeixinFriends;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnFront;
    QPushButton *btnBack;
    QHBoxLayout *horizontalLayout;
    QListView *lstWeixinFriends;
    ChatContainer *edtWeixinChat;

    void setupUi(QFrame *WeixinInfoDlg)
    {
        if (WeixinInfoDlg->objectName().isEmpty())
            WeixinInfoDlg->setObjectName(QString::fromUtf8("WeixinInfoDlg"));
        WeixinInfoDlg->resize(767, 557);
        verticalLayout = new QVBoxLayout(WeixinInfoDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        weixin_frame_1 = new QFrame(WeixinInfoDlg);
        weixin_frame_1->setObjectName(QString::fromUtf8("weixin_frame_1"));
        weixin_frame_1->setMinimumSize(QSize(0, 35));
        weixin_frame_1->setMaximumSize(QSize(16777215, 35));
        horizontalLayout_2 = new QHBoxLayout(weixin_frame_1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, 0, 10, 0);
        label_3 = new QLabel(weixin_frame_1);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 20));
        label_3->setMaximumSize(QSize(16777215, 20));
        label_3->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(label_3);

        cmbWeixinFriends = new QComboBox(weixin_frame_1);
        cmbWeixinFriends->setObjectName(QString::fromUtf8("cmbWeixinFriends"));
        cmbWeixinFriends->setMinimumSize(QSize(250, 20));
        cmbWeixinFriends->setMaximumSize(QSize(250, 20));

        horizontalLayout_2->addWidget(cmbWeixinFriends);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnFront = new QPushButton(weixin_frame_1);
        btnFront->setObjectName(QString::fromUtf8("btnFront"));
        btnFront->setMinimumSize(QSize(25, 25));
        btnFront->setMaximumSize(QSize(25, 16777215));

        horizontalLayout_2->addWidget(btnFront);

        btnBack = new QPushButton(weixin_frame_1);
        btnBack->setObjectName(QString::fromUtf8("btnBack"));
        btnBack->setMinimumSize(QSize(25, 25));
        btnBack->setMaximumSize(QSize(25, 16777215));

        horizontalLayout_2->addWidget(btnBack);


        verticalLayout->addWidget(weixin_frame_1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lstWeixinFriends = new QListView(WeixinInfoDlg);
        lstWeixinFriends->setObjectName(QString::fromUtf8("lstWeixinFriends"));
        lstWeixinFriends->setMaximumSize(QSize(200, 16777215));
        lstWeixinFriends->setFocusPolicy(Qt::NoFocus);
        lstWeixinFriends->setStyleSheet(QString::fromUtf8(""));
        lstWeixinFriends->setFrameShape(QFrame::NoFrame);
        lstWeixinFriends->setEditTriggers(QAbstractItemView::NoEditTriggers);
        lstWeixinFriends->setAlternatingRowColors(true);
        lstWeixinFriends->setSelectionBehavior(QAbstractItemView::SelectItems);
        lstWeixinFriends->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(lstWeixinFriends);

        edtWeixinChat = new ChatContainer(WeixinInfoDlg);
        edtWeixinChat->setObjectName(QString::fromUtf8("edtWeixinChat"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(edtWeixinChat->sizePolicy().hasHeightForWidth());
        edtWeixinChat->setSizePolicy(sizePolicy);
        edtWeixinChat->setFrameShape(QFrame::StyledPanel);
        edtWeixinChat->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(edtWeixinChat);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(WeixinInfoDlg);

        QMetaObject::connectSlotsByName(WeixinInfoDlg);
    } // setupUi

    void retranslateUi(QFrame *WeixinInfoDlg)
    {
        WeixinInfoDlg->setWindowTitle(QApplication::translate("WeixinInfoDlg", "WeixinInfoDlg", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("WeixinInfoDlg", "\345\275\223\345\211\215\350\264\246\345\217\267", 0, QApplication::UnicodeUTF8));
        cmbWeixinFriends->clear();
        cmbWeixinFriends->insertItems(0, QStringList()
         << QApplication::translate("WeixinInfoDlg", "New Item", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("WeixinInfoDlg", "New Item", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("WeixinInfoDlg", "New Item", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("WeixinInfoDlg", "New Item", 0, QApplication::UnicodeUTF8)
        );
        btnFront->setText(QApplication::translate("WeixinInfoDlg", "<", 0, QApplication::UnicodeUTF8));
        btnBack->setText(QApplication::translate("WeixinInfoDlg", ">", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WeixinInfoDlg: public Ui_WeixinInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEIXININFODLG_H
