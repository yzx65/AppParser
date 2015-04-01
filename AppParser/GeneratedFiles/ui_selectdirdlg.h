/********************************************************************************
** Form generated from reading UI file 'selectdirdlg.ui'
**
** Created: Wed Apr 1 16:19:40 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTDIRDLG_H
#define UI_SELECTDIRDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectDirDlg
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame_analyze;
    QHBoxLayout *horizontalLayout;
    QLineEdit *edtPath;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnBrowse;
    QStackedWidget *stack;
    QWidget *page;
    QVBoxLayout *verticalLayout_2;
    QListWidget *lstDevices;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_3;
    QListWidget *lstForensicsType;

    void setupUi(QFrame *SelectDirDlg)
    {
        if (SelectDirDlg->objectName().isEmpty())
            SelectDirDlg->setObjectName(QString::fromUtf8("SelectDirDlg"));
        SelectDirDlg->resize(400, 178);
        verticalLayout = new QVBoxLayout(SelectDirDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_analyze = new QFrame(SelectDirDlg);
        frame_analyze->setObjectName(QString::fromUtf8("frame_analyze"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_analyze->sizePolicy().hasHeightForWidth());
        frame_analyze->setSizePolicy(sizePolicy);
        frame_analyze->setMaximumSize(QSize(16777215, 50));
        frame_analyze->setFrameShape(QFrame::NoFrame);
        frame_analyze->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_analyze);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        edtPath = new QLineEdit(frame_analyze);
        edtPath->setObjectName(QString::fromUtf8("edtPath"));
        edtPath->setMinimumSize(QSize(0, 30));
        edtPath->setReadOnly(true);

        horizontalLayout->addWidget(edtPath);

        horizontalSpacer_3 = new QSpacerItem(8, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        btnBrowse = new QPushButton(frame_analyze);
        btnBrowse->setObjectName(QString::fromUtf8("btnBrowse"));
        btnBrowse->setMinimumSize(QSize(60, 30));

        horizontalLayout->addWidget(btnBrowse);


        verticalLayout->addWidget(frame_analyze);

        stack = new QStackedWidget(SelectDirDlg);
        stack->setObjectName(QString::fromUtf8("stack"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout_2 = new QVBoxLayout(page);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lstDevices = new QListWidget(page);
        lstDevices->setObjectName(QString::fromUtf8("lstDevices"));
        lstDevices->setFocusPolicy(Qt::NoFocus);
        lstDevices->setFrameShape(QFrame::NoFrame);
        lstDevices->setAlternatingRowColors(true);
        lstDevices->setIconSize(QSize(24, 24));

        verticalLayout_2->addWidget(lstDevices);

        stack->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_3 = new QVBoxLayout(page_2);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        lstForensicsType = new QListWidget(page_2);
        lstForensicsType->setObjectName(QString::fromUtf8("lstForensicsType"));
        lstForensicsType->setFocusPolicy(Qt::NoFocus);
        lstForensicsType->setFrameShape(QFrame::NoFrame);
        lstForensicsType->setAlternatingRowColors(true);

        verticalLayout_3->addWidget(lstForensicsType);

        stack->addWidget(page_2);

        verticalLayout->addWidget(stack);


        retranslateUi(SelectDirDlg);

        stack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SelectDirDlg);
    } // setupUi

    void retranslateUi(QFrame *SelectDirDlg)
    {
        SelectDirDlg->setWindowTitle(QApplication::translate("SelectDirDlg", "SelectDirDlg", 0, QApplication::UnicodeUTF8));
        btnBrowse->setText(QApplication::translate("SelectDirDlg", "\346\265\217\350\247\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SelectDirDlg: public Ui_SelectDirDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTDIRDLG_H
