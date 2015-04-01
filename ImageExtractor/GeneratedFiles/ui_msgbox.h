/********************************************************************************
** Form generated from reading UI file 'msgbox.ui'
**
** Created: Wed Apr 1 16:21:04 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGBOX_H
#define UI_MSGBOX_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MsgBox
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *lbMsg;
    QFrame *frame_msgBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOK;

    void setupUi(QFrame *MsgBox)
    {
        if (MsgBox->objectName().isEmpty())
            MsgBox->setObjectName(QString::fromUtf8("MsgBox"));
        MsgBox->resize(400, 235);
        MsgBox->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"	background-color:white;\n"
"}"));
        verticalLayout = new QVBoxLayout(MsgBox);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame2 = new QFrame(MsgBox);
        frame2->setObjectName(QString::fromUtf8("frame2"));
        frame2->setFrameShape(QFrame::StyledPanel);
        frame2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(30, -1, -1, -1);
        label = new QLabel(frame2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(70, 16777215));
        label->setPixmap(QPixmap(QString::fromUtf8(":/Image/information.png")));

        horizontalLayout_2->addWidget(label);

        lbMsg = new QLabel(frame2);
        lbMsg->setObjectName(QString::fromUtf8("lbMsg"));

        horizontalLayout_2->addWidget(lbMsg);


        verticalLayout->addWidget(frame2);

        frame_msgBox = new QFrame(MsgBox);
        frame_msgBox->setObjectName(QString::fromUtf8("frame_msgBox"));
        frame_msgBox->setMaximumSize(QSize(16777215, 50));
        frame_msgBox->setFrameShape(QFrame::StyledPanel);
        frame_msgBox->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_msgBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOK = new QPushButton(frame_msgBox);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setMinimumSize(QSize(70, 28));
        btnOK->setMaximumSize(QSize(70, 28));
        btnOK->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(btnOK);


        verticalLayout->addWidget(frame_msgBox);


        retranslateUi(MsgBox);

        QMetaObject::connectSlotsByName(MsgBox);
    } // setupUi

    void retranslateUi(QFrame *MsgBox)
    {
        MsgBox->setWindowTitle(QApplication::translate("MsgBox", "MsgBox", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        lbMsg->setText(QApplication::translate("MsgBox", "TextLabel", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("MsgBox", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MsgBox: public Ui_MsgBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGBOX_H
