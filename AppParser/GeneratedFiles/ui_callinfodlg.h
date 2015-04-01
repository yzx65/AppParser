/********************************************************************************
** Form generated from reading UI file 'callinfodlg.ui'
**
** Created: Wed Apr 1 16:19:40 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALLINFODLG_H
#define UI_CALLINFODLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CallInfoDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QFrame *frame_left;
    QVBoxLayout *verticalLayout;
    QListView *lstCallFriends;
    QTreeWidget *tbCallInfo;

    void setupUi(QFrame *CallInfoDlg)
    {
        if (CallInfoDlg->objectName().isEmpty())
            CallInfoDlg->setObjectName(QString::fromUtf8("CallInfoDlg"));
        CallInfoDlg->resize(697, 444);
        verticalLayout_2 = new QVBoxLayout(CallInfoDlg);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame_left = new QFrame(CallInfoDlg);
        frame_left->setObjectName(QString::fromUtf8("frame_left"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_left->sizePolicy().hasHeightForWidth());
        frame_left->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(frame_left);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lstCallFriends = new QListView(frame_left);
        lstCallFriends->setObjectName(QString::fromUtf8("lstCallFriends"));
        lstCallFriends->setMinimumSize(QSize(200, 0));
        lstCallFriends->setMaximumSize(QSize(200, 16777215));
        lstCallFriends->setFocusPolicy(Qt::NoFocus);
        lstCallFriends->setFrameShape(QFrame::NoFrame);
        lstCallFriends->setEditTriggers(QAbstractItemView::NoEditTriggers);
        lstCallFriends->setAlternatingRowColors(true);

        verticalLayout->addWidget(lstCallFriends);


        horizontalLayout->addWidget(frame_left);

        tbCallInfo = new QTreeWidget(CallInfoDlg);
        tbCallInfo->setObjectName(QString::fromUtf8("tbCallInfo"));
        tbCallInfo->setFocusPolicy(Qt::NoFocus);
        tbCallInfo->setFrameShape(QFrame::NoFrame);
        tbCallInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbCallInfo->setAlternatingRowColors(true);
        tbCallInfo->setIndentation(0);

        horizontalLayout->addWidget(tbCallInfo);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(CallInfoDlg);

        QMetaObject::connectSlotsByName(CallInfoDlg);
    } // setupUi

    void retranslateUi(QFrame *CallInfoDlg)
    {
        CallInfoDlg->setWindowTitle(QApplication::translate("CallInfoDlg", "CallInfoDlg", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = tbCallInfo->headerItem();
        ___qtreewidgetitem->setText(3, QApplication::translate("CallInfoDlg", "\345\275\222\345\261\236\345\234\260", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(2, QApplication::translate("CallInfoDlg", "\351\200\232\350\257\235\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("CallInfoDlg", "\351\200\232\350\257\235\346\227\266\351\225\277", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("CallInfoDlg", "\351\200\232\350\257\235\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CallInfoDlg: public Ui_CallInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALLINFODLG_H
