/********************************************************************************
** Form generated from reading UI file 'lineinfodlg.ui'
**
** Created: Wed Apr 1 13:49:51 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINEINFODLG_H
#define UI_LINEINFODLG_H

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

class Ui_LineInfoDlg
{
public:
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QFrame *frame_left;
    QVBoxLayout *verticalLayout_2;
    QListView *lstLineFriends;
    QFrame *frame_right;
    QVBoxLayout *verticalLayout;
    ChatContainer *edtLineRecord;
    QFrame *frame_chat_nav;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnFront;
    QPushButton *btnBack;

    void setupUi(QFrame *LineInfoDlg)
    {
        if (LineInfoDlg->objectName().isEmpty())
            LineInfoDlg->setObjectName(QString::fromUtf8("LineInfoDlg"));
        LineInfoDlg->resize(699, 465);
        horizontalLayout_3 = new QHBoxLayout(LineInfoDlg);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame_left = new QFrame(LineInfoDlg);
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
        lstLineFriends = new QListView(frame_left);
        lstLineFriends->setObjectName(QString::fromUtf8("lstLineFriends"));
        lstLineFriends->setMinimumSize(QSize(200, 0));
        lstLineFriends->setMaximumSize(QSize(200, 16777215));
        lstLineFriends->setFocusPolicy(Qt::NoFocus);
        lstLineFriends->setFrameShape(QFrame::NoFrame);
        lstLineFriends->setEditTriggers(QAbstractItemView::NoEditTriggers);
        lstLineFriends->setAlternatingRowColors(true);

        verticalLayout_2->addWidget(lstLineFriends);


        horizontalLayout->addWidget(frame_left);

        frame_right = new QFrame(LineInfoDlg);
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
        edtLineRecord = new ChatContainer(frame_right);
        edtLineRecord->setObjectName(QString::fromUtf8("edtLineRecord"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(edtLineRecord->sizePolicy().hasHeightForWidth());
        edtLineRecord->setSizePolicy(sizePolicy2);
        edtLineRecord->setFrameShape(QFrame::StyledPanel);
        edtLineRecord->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(edtLineRecord);

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


        horizontalLayout_3->addLayout(horizontalLayout);


        retranslateUi(LineInfoDlg);

        QMetaObject::connectSlotsByName(LineInfoDlg);
    } // setupUi

    void retranslateUi(QFrame *LineInfoDlg)
    {
        LineInfoDlg->setWindowTitle(QApplication::translate("LineInfoDlg", "LineInfoDlg", 0, QApplication::UnicodeUTF8));
        btnFront->setText(QApplication::translate("LineInfoDlg", "<", 0, QApplication::UnicodeUTF8));
        btnBack->setText(QApplication::translate("LineInfoDlg", ">", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LineInfoDlg: public Ui_LineInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEINFODLG_H
