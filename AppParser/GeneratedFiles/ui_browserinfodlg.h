/********************************************************************************
** Form generated from reading UI file 'browserinfodlg.ui'
**
** Created: Wed Apr 1 13:49:51 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BROWSERINFODLG_H
#define UI_BROWSERINFODLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BrowserInfoDlg
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QRadioButton *btnHistory;
    QRadioButton *btnBookmark;
    QSpacerItem *horizontalSpacer;
    QListView *lstBrowserData;

    void setupUi(QFrame *BrowserInfoDlg)
    {
        if (BrowserInfoDlg->objectName().isEmpty())
            BrowserInfoDlg->setObjectName(QString::fromUtf8("BrowserInfoDlg"));
        BrowserInfoDlg->resize(666, 300);
        verticalLayout = new QVBoxLayout(BrowserInfoDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(BrowserInfoDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 34));
        frame->setMaximumSize(QSize(16777215, 34));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 0, 0, 0);
        btnHistory = new QRadioButton(frame);
        btnHistory->setObjectName(QString::fromUtf8("btnHistory"));
        btnHistory->setMinimumSize(QSize(120, 0));
        btnHistory->setChecked(true);

        horizontalLayout->addWidget(btnHistory);

        btnBookmark = new QRadioButton(frame);
        btnBookmark->setObjectName(QString::fromUtf8("btnBookmark"));
        btnBookmark->setMinimumSize(QSize(120, 0));

        horizontalLayout->addWidget(btnBookmark);

        horizontalSpacer = new QSpacerItem(411, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(frame);

        lstBrowserData = new QListView(BrowserInfoDlg);
        lstBrowserData->setObjectName(QString::fromUtf8("lstBrowserData"));
        lstBrowserData->setFocusPolicy(Qt::NoFocus);
        lstBrowserData->setFrameShape(QFrame::NoFrame);
        lstBrowserData->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(lstBrowserData);


        retranslateUi(BrowserInfoDlg);

        QMetaObject::connectSlotsByName(BrowserInfoDlg);
    } // setupUi

    void retranslateUi(QFrame *BrowserInfoDlg)
    {
        BrowserInfoDlg->setWindowTitle(QApplication::translate("BrowserInfoDlg", "BrowserInfoDlg", 0, QApplication::UnicodeUTF8));
        btnHistory->setText(QApplication::translate("BrowserInfoDlg", "\345\216\206\345\217\262\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        btnBookmark->setText(QApplication::translate("BrowserInfoDlg", "\344\271\246\347\255\276", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BrowserInfoDlg: public Ui_BrowserInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BROWSERINFODLG_H
