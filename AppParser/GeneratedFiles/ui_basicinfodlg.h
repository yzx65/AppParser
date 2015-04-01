/********************************************************************************
** Form generated from reading UI file 'basicinfodlg.ui'
**
** Created: Wed Apr 1 16:19:40 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASICINFODLG_H
#define UI_BASICINFODLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BasicInfoDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLabel *picture;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *info_1;
    QLabel *lbDevType;
    QHBoxLayout *horizontalLayout_3;
    QLabel *info_2;
    QLabel *lbDevName;
    QHBoxLayout *horizontalLayout_4;
    QLabel *info_3;
    QLabel *lbDevModel;
    QHBoxLayout *horizontalLayout_12;
    QLabel *info_11;
    QLabel *lbExtraInfo;
    QHBoxLayout *horizontalLayout_5;
    QLabel *info_4;
    QLabel *lbDevNumber;
    QHBoxLayout *horizontalLayout_6;
    QLabel *info_5;
    QLabel *lbOsVersion;
    QHBoxLayout *horizontalLayout_7;
    QLabel *info_6;
    QLabel *lbSerialNum;
    QHBoxLayout *horizontalLayout_8;
    QLabel *info_7;
    QLabel *lbRoot;
    QHBoxLayout *horizontalLayout_9;
    QLabel *info_8;
    QLabel *lbCpuArc;
    QHBoxLayout *horizontalLayout_10;
    QLabel *info_9;
    QProgressBar *prgSystemUsage;
    QLabel *lbSysUsage;
    QHBoxLayout *horizontalLayout_11;
    QLabel *info_10;
    QProgressBar *prgUserUsage;
    QLabel *lbUserUsage;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QFrame *BasicInfoDlg)
    {
        if (BasicInfoDlg->objectName().isEmpty())
            BasicInfoDlg->setObjectName(QString::fromUtf8("BasicInfoDlg"));
        BasicInfoDlg->resize(688, 462);
        horizontalLayout = new QHBoxLayout(BasicInfoDlg);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        frame = new QFrame(BasicInfoDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        picture = new QLabel(frame);
        picture->setObjectName(QString::fromUtf8("picture"));
        picture->setMinimumSize(QSize(250, 350));
        picture->setMaximumSize(QSize(250, 350));
        picture->setPixmap(QPixmap(QString::fromUtf8(":/Image/iphone_5s_gold.png")));

        verticalLayout->addWidget(picture);


        horizontalLayout->addWidget(frame);

        frame_2 = new QFrame(BasicInfoDlg);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(30);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        info_1 = new QLabel(frame_2);
        info_1->setObjectName(QString::fromUtf8("info_1"));
        info_1->setMinimumSize(QSize(80, 30));
        info_1->setMaximumSize(QSize(80, 30));
        info_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(info_1);

        lbDevType = new QLabel(frame_2);
        lbDevType->setObjectName(QString::fromUtf8("lbDevType"));
        lbDevType->setMinimumSize(QSize(250, 30));
        lbDevType->setMaximumSize(QSize(250, 30));

        horizontalLayout_2->addWidget(lbDevType);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(30);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        info_2 = new QLabel(frame_2);
        info_2->setObjectName(QString::fromUtf8("info_2"));
        info_2->setMinimumSize(QSize(80, 30));
        info_2->setMaximumSize(QSize(80, 30));
        info_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(info_2);

        lbDevName = new QLabel(frame_2);
        lbDevName->setObjectName(QString::fromUtf8("lbDevName"));
        lbDevName->setMinimumSize(QSize(250, 30));
        lbDevName->setMaximumSize(QSize(250, 30));

        horizontalLayout_3->addWidget(lbDevName);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(30);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        info_3 = new QLabel(frame_2);
        info_3->setObjectName(QString::fromUtf8("info_3"));
        info_3->setMinimumSize(QSize(80, 30));
        info_3->setMaximumSize(QSize(80, 30));
        info_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(info_3);

        lbDevModel = new QLabel(frame_2);
        lbDevModel->setObjectName(QString::fromUtf8("lbDevModel"));
        lbDevModel->setMinimumSize(QSize(250, 30));
        lbDevModel->setMaximumSize(QSize(250, 30));

        horizontalLayout_4->addWidget(lbDevModel);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(30);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        info_11 = new QLabel(frame_2);
        info_11->setObjectName(QString::fromUtf8("info_11"));
        info_11->setMinimumSize(QSize(80, 30));
        info_11->setMaximumSize(QSize(80, 30));
        info_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_12->addWidget(info_11);

        lbExtraInfo = new QLabel(frame_2);
        lbExtraInfo->setObjectName(QString::fromUtf8("lbExtraInfo"));
        lbExtraInfo->setMinimumSize(QSize(250, 30));
        lbExtraInfo->setMaximumSize(QSize(250, 30));

        horizontalLayout_12->addWidget(lbExtraInfo);


        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(30);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        info_4 = new QLabel(frame_2);
        info_4->setObjectName(QString::fromUtf8("info_4"));
        info_4->setMinimumSize(QSize(80, 30));
        info_4->setMaximumSize(QSize(80, 30));
        info_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(info_4);

        lbDevNumber = new QLabel(frame_2);
        lbDevNumber->setObjectName(QString::fromUtf8("lbDevNumber"));
        lbDevNumber->setMinimumSize(QSize(250, 30));
        lbDevNumber->setMaximumSize(QSize(250, 30));

        horizontalLayout_5->addWidget(lbDevNumber);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(30);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        info_5 = new QLabel(frame_2);
        info_5->setObjectName(QString::fromUtf8("info_5"));
        info_5->setMinimumSize(QSize(80, 30));
        info_5->setMaximumSize(QSize(80, 30));
        info_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(info_5);

        lbOsVersion = new QLabel(frame_2);
        lbOsVersion->setObjectName(QString::fromUtf8("lbOsVersion"));
        lbOsVersion->setMinimumSize(QSize(250, 0));
        lbOsVersion->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_6->addWidget(lbOsVersion);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(30);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        info_6 = new QLabel(frame_2);
        info_6->setObjectName(QString::fromUtf8("info_6"));
        info_6->setMinimumSize(QSize(80, 30));
        info_6->setMaximumSize(QSize(80, 30));
        info_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(info_6);

        lbSerialNum = new QLabel(frame_2);
        lbSerialNum->setObjectName(QString::fromUtf8("lbSerialNum"));
        lbSerialNum->setMinimumSize(QSize(250, 30));
        lbSerialNum->setMaximumSize(QSize(250, 30));

        horizontalLayout_7->addWidget(lbSerialNum);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(30);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        info_7 = new QLabel(frame_2);
        info_7->setObjectName(QString::fromUtf8("info_7"));
        info_7->setMinimumSize(QSize(80, 30));
        info_7->setMaximumSize(QSize(80, 30));
        info_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(info_7);

        lbRoot = new QLabel(frame_2);
        lbRoot->setObjectName(QString::fromUtf8("lbRoot"));
        lbRoot->setMinimumSize(QSize(250, 30));
        lbRoot->setMaximumSize(QSize(250, 30));

        horizontalLayout_8->addWidget(lbRoot);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(30);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        info_8 = new QLabel(frame_2);
        info_8->setObjectName(QString::fromUtf8("info_8"));
        info_8->setMinimumSize(QSize(80, 30));
        info_8->setMaximumSize(QSize(80, 30));
        info_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(info_8);

        lbCpuArc = new QLabel(frame_2);
        lbCpuArc->setObjectName(QString::fromUtf8("lbCpuArc"));
        lbCpuArc->setMinimumSize(QSize(250, 30));
        lbCpuArc->setMaximumSize(QSize(250, 30));

        horizontalLayout_9->addWidget(lbCpuArc);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(30);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        info_9 = new QLabel(frame_2);
        info_9->setObjectName(QString::fromUtf8("info_9"));
        info_9->setMinimumSize(QSize(80, 30));
        info_9->setMaximumSize(QSize(80, 30));
        info_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(info_9);

        prgSystemUsage = new QProgressBar(frame_2);
        prgSystemUsage->setObjectName(QString::fromUtf8("prgSystemUsage"));
        prgSystemUsage->setMinimumSize(QSize(0, 5));
        prgSystemUsage->setMaximumSize(QSize(16777215, 5));
        prgSystemUsage->setValue(100);
        prgSystemUsage->setTextVisible(false);

        horizontalLayout_10->addWidget(prgSystemUsage);

        lbSysUsage = new QLabel(frame_2);
        lbSysUsage->setObjectName(QString::fromUtf8("lbSysUsage"));
        lbSysUsage->setMinimumSize(QSize(100, 30));
        lbSysUsage->setMaximumSize(QSize(100, 30));

        horizontalLayout_10->addWidget(lbSysUsage);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(30);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        info_10 = new QLabel(frame_2);
        info_10->setObjectName(QString::fromUtf8("info_10"));
        info_10->setMinimumSize(QSize(80, 30));
        info_10->setMaximumSize(QSize(80, 30));
        info_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(info_10);

        prgUserUsage = new QProgressBar(frame_2);
        prgUserUsage->setObjectName(QString::fromUtf8("prgUserUsage"));
        prgUserUsage->setMinimumSize(QSize(0, 5));
        prgUserUsage->setMaximumSize(QSize(16777215, 5));
        prgUserUsage->setValue(100);
        prgUserUsage->setTextVisible(false);

        horizontalLayout_11->addWidget(prgUserUsage);

        lbUserUsage = new QLabel(frame_2);
        lbUserUsage->setObjectName(QString::fromUtf8("lbUserUsage"));
        lbUserUsage->setMinimumSize(QSize(100, 30));
        lbUserUsage->setMaximumSize(QSize(100, 30));

        horizontalLayout_11->addWidget(lbUserUsage);


        verticalLayout_2->addLayout(horizontalLayout_11);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addWidget(frame_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(BasicInfoDlg);

        QMetaObject::connectSlotsByName(BasicInfoDlg);
    } // setupUi

    void retranslateUi(QFrame *BasicInfoDlg)
    {
        BasicInfoDlg->setWindowTitle(QApplication::translate("BasicInfoDlg", "BasicInfoDlg", 0, QApplication::UnicodeUTF8));
        picture->setText(QString());
        info_1->setText(QApplication::translate("BasicInfoDlg", "\350\256\276\345\244\207\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        lbDevType->setText(QApplication::translate("BasicInfoDlg", "\346\234\252\347\237\245", 0, QApplication::UnicodeUTF8));
        info_2->setText(QApplication::translate("BasicInfoDlg", "\350\256\276\345\244\207\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        lbDevName->setText(QApplication::translate("BasicInfoDlg", "\346\234\252\347\237\245", 0, QApplication::UnicodeUTF8));
        info_3->setText(QApplication::translate("BasicInfoDlg", "\350\256\276\345\244\207\345\236\213\345\217\267", 0, QApplication::UnicodeUTF8));
        lbDevModel->setText(QApplication::translate("BasicInfoDlg", "\346\234\252\347\237\245", 0, QApplication::UnicodeUTF8));
        info_11->setText(QApplication::translate("BasicInfoDlg", "\350\256\276\345\244\207\351\242\234\350\211\262", 0, QApplication::UnicodeUTF8));
        lbExtraInfo->setText(QApplication::translate("BasicInfoDlg", "\346\234\252\347\237\245", 0, QApplication::UnicodeUTF8));
        info_4->setText(QApplication::translate("BasicInfoDlg", "\350\256\276\345\244\207\345\217\267\347\240\201", 0, QApplication::UnicodeUTF8));
        lbDevNumber->setText(QApplication::translate("BasicInfoDlg", "\346\234\252\347\237\245", 0, QApplication::UnicodeUTF8));
        info_5->setText(QApplication::translate("BasicInfoDlg", "\347\263\273\347\273\237\347\211\210\346\234\254", 0, QApplication::UnicodeUTF8));
        lbOsVersion->setText(QApplication::translate("BasicInfoDlg", "\346\234\252\347\237\245", 0, QApplication::UnicodeUTF8));
        info_6->setText(QApplication::translate("BasicInfoDlg", "\350\256\276\345\244\207\345\272\217\345\210\227\345\217\267", 0, QApplication::UnicodeUTF8));
        lbSerialNum->setText(QApplication::translate("BasicInfoDlg", "\346\234\252\347\237\245", 0, QApplication::UnicodeUTF8));
        info_7->setText(QApplication::translate("BasicInfoDlg", "\346\230\257\345\220\246\350\266\212\347\213\261", 0, QApplication::UnicodeUTF8));
        lbRoot->setText(QApplication::translate("BasicInfoDlg", "\346\234\252\347\237\245", 0, QApplication::UnicodeUTF8));
        info_8->setText(QApplication::translate("BasicInfoDlg", "CPU \346\236\266\346\236\204", 0, QApplication::UnicodeUTF8));
        lbCpuArc->setText(QApplication::translate("BasicInfoDlg", "\346\234\252\347\237\245", 0, QApplication::UnicodeUTF8));
        info_9->setText(QApplication::translate("BasicInfoDlg", "\347\263\273\347\273\237\345\210\206\345\214\272", 0, QApplication::UnicodeUTF8));
        lbSysUsage->setText(QApplication::translate("BasicInfoDlg", "\346\234\252\347\237\245", 0, QApplication::UnicodeUTF8));
        info_10->setText(QApplication::translate("BasicInfoDlg", "\347\224\250\346\210\267\345\210\206\345\214\272", 0, QApplication::UnicodeUTF8));
        lbUserUsage->setText(QApplication::translate("BasicInfoDlg", "\346\234\252\347\237\245", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BasicInfoDlg: public Ui_BasicInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASICINFODLG_H
