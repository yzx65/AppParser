/********************************************************************************
** Form generated from reading UI file 'contactinfodlg.ui'
**
** Created: Wed Apr 1 16:19:40 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTACTINFODLG_H
#define UI_CONTACTINFODLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ContactInfoDlg
{
public:
    QVBoxLayout *verticalLayout;
    QTreeView *tbContactInfo;

    void setupUi(QFrame *ContactInfoDlg)
    {
        if (ContactInfoDlg->objectName().isEmpty())
            ContactInfoDlg->setObjectName(QString::fromUtf8("ContactInfoDlg"));
        ContactInfoDlg->resize(400, 300);
        verticalLayout = new QVBoxLayout(ContactInfoDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tbContactInfo = new QTreeView(ContactInfoDlg);
        tbContactInfo->setObjectName(QString::fromUtf8("tbContactInfo"));
        tbContactInfo->setFocusPolicy(Qt::NoFocus);
        tbContactInfo->setFrameShape(QFrame::NoFrame);
        tbContactInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbContactInfo->setAlternatingRowColors(true);
        tbContactInfo->setIndentation(0);

        verticalLayout->addWidget(tbContactInfo);


        retranslateUi(ContactInfoDlg);

        QMetaObject::connectSlotsByName(ContactInfoDlg);
    } // setupUi

    void retranslateUi(QFrame *ContactInfoDlg)
    {
        ContactInfoDlg->setWindowTitle(QApplication::translate("ContactInfoDlg", "ContactInfoDlg", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ContactInfoDlg: public Ui_ContactInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTACTINFODLG_H
