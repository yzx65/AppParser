/********************************************************************************
** Form generated from reading UI file 'keychaininfodlg.ui'
**
** Created: Wed Apr 1 16:19:40 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYCHAININFODLG_H
#define UI_KEYCHAININFODLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_KeyChainInfoDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QListView *lstService;
    QTreeWidget *tbPassword;

    void setupUi(QFrame *KeyChainInfoDlg)
    {
        if (KeyChainInfoDlg->objectName().isEmpty())
            KeyChainInfoDlg->setObjectName(QString::fromUtf8("KeyChainInfoDlg"));
        KeyChainInfoDlg->resize(625, 443);
        horizontalLayout = new QHBoxLayout(KeyChainInfoDlg);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lstService = new QListView(KeyChainInfoDlg);
        lstService->setObjectName(QString::fromUtf8("lstService"));
        lstService->setMinimumSize(QSize(200, 0));
        lstService->setMaximumSize(QSize(200, 16777215));
        lstService->setFocusPolicy(Qt::NoFocus);
        lstService->setFrameShape(QFrame::NoFrame);
        lstService->setEditTriggers(QAbstractItemView::NoEditTriggers);
        lstService->setAlternatingRowColors(true);

        horizontalLayout->addWidget(lstService);

        tbPassword = new QTreeWidget(KeyChainInfoDlg);
        tbPassword->setObjectName(QString::fromUtf8("tbPassword"));
        tbPassword->setFocusPolicy(Qt::NoFocus);
        tbPassword->setFrameShape(QFrame::NoFrame);
        tbPassword->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbPassword->setAlternatingRowColors(true);
        tbPassword->setIndentation(0);

        horizontalLayout->addWidget(tbPassword);


        retranslateUi(KeyChainInfoDlg);

        QMetaObject::connectSlotsByName(KeyChainInfoDlg);
    } // setupUi

    void retranslateUi(QFrame *KeyChainInfoDlg)
    {
        KeyChainInfoDlg->setWindowTitle(QApplication::translate("KeyChainInfoDlg", "KeyChainInfoDlg", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = tbPassword->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("KeyChainInfoDlg", "\345\257\206\351\222\245", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("KeyChainInfoDlg", "\345\255\227\346\256\265", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("KeyChainInfoDlg", "\346\234\215\345\212\241\345\220\215", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class KeyChainInfoDlg: public Ui_KeyChainInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYCHAININFODLG_H
