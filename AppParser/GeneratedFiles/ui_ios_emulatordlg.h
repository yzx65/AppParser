/********************************************************************************
** Form generated from reading UI file 'ios_emulatordlg.ui'
**
** Created: Wed Apr 1 16:19:40 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IOS_EMULATORDLG_H
#define UI_IOS_EMULATORDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_IOS_EmulatorDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_emulator_header;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lbApplist;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *btnInstallAll;
    QPushButton *btnExportAll;
    QTreeWidget *trEmulatorApps;
    QFrame *frame_simulator;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLabel *lbEmulatorStatus;
    QProgressBar *progress;
    QPushButton *btnRecoveryBackup;

    void setupUi(QFrame *IOS_EmulatorDlg)
    {
        if (IOS_EmulatorDlg->objectName().isEmpty())
            IOS_EmulatorDlg->setObjectName(QString::fromUtf8("IOS_EmulatorDlg"));
        IOS_EmulatorDlg->resize(703, 519);
        verticalLayout_2 = new QVBoxLayout(IOS_EmulatorDlg);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frame_emulator_header = new QFrame(IOS_EmulatorDlg);
        frame_emulator_header->setObjectName(QString::fromUtf8("frame_emulator_header"));
        frame_emulator_header->setMinimumSize(QSize(0, 35));
        frame_emulator_header->setMaximumSize(QSize(16777215, 35));
        frame_emulator_header->setFrameShape(QFrame::StyledPanel);
        frame_emulator_header->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_emulator_header);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, 0);
        lbApplist = new QLabel(frame_emulator_header);
        lbApplist->setObjectName(QString::fromUtf8("lbApplist"));
        lbApplist->setMinimumSize(QSize(0, 30));
        lbApplist->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_2->addWidget(lbApplist);

        label = new QLabel(frame_emulator_header);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        label_2 = new QLabel(frame_emulator_header);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        label_3 = new QLabel(frame_emulator_header);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        label_4 = new QLabel(frame_emulator_header);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMaximumSize(QSize(90, 16777215));

        horizontalLayout_2->addWidget(label_4);

        btnInstallAll = new QPushButton(frame_emulator_header);
        btnInstallAll->setObjectName(QString::fromUtf8("btnInstallAll"));
        btnInstallAll->setMinimumSize(QSize(75, 25));
        btnInstallAll->setMaximumSize(QSize(75, 25));

        horizontalLayout_2->addWidget(btnInstallAll);

        btnExportAll = new QPushButton(frame_emulator_header);
        btnExportAll->setObjectName(QString::fromUtf8("btnExportAll"));
        btnExportAll->setMinimumSize(QSize(75, 25));
        btnExportAll->setMaximumSize(QSize(75, 25));

        horizontalLayout_2->addWidget(btnExportAll);


        verticalLayout_2->addWidget(frame_emulator_header);

        trEmulatorApps = new QTreeWidget(IOS_EmulatorDlg);
        new QTreeWidgetItem(trEmulatorApps);
        new QTreeWidgetItem(trEmulatorApps);
        new QTreeWidgetItem(trEmulatorApps);
        new QTreeWidgetItem(trEmulatorApps);
        new QTreeWidgetItem(trEmulatorApps);
        new QTreeWidgetItem(trEmulatorApps);
        new QTreeWidgetItem(trEmulatorApps);
        new QTreeWidgetItem(trEmulatorApps);
        trEmulatorApps->setObjectName(QString::fromUtf8("trEmulatorApps"));
        trEmulatorApps->setFocusPolicy(Qt::NoFocus);
        trEmulatorApps->setFrameShape(QFrame::NoFrame);
        trEmulatorApps->setAlternatingRowColors(true);
        trEmulatorApps->setSelectionMode(QAbstractItemView::NoSelection);
        trEmulatorApps->setIndentation(0);
        trEmulatorApps->header()->setVisible(false);

        verticalLayout_2->addWidget(trEmulatorApps);

        frame_simulator = new QFrame(IOS_EmulatorDlg);
        frame_simulator->setObjectName(QString::fromUtf8("frame_simulator"));
        frame_simulator->setMinimumSize(QSize(0, 60));
        frame_simulator->setMaximumSize(QSize(16777215, 150));
        frame_simulator->setFrameShape(QFrame::StyledPanel);
        frame_simulator->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_simulator);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame = new QFrame(frame_simulator);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lbEmulatorStatus = new QLabel(frame);
        lbEmulatorStatus->setObjectName(QString::fromUtf8("lbEmulatorStatus"));
        lbEmulatorStatus->setMinimumSize(QSize(400, 0));
        lbEmulatorStatus->setMaximumSize(QSize(400, 16777215));

        verticalLayout->addWidget(lbEmulatorStatus);

        progress = new QProgressBar(frame);
        progress->setObjectName(QString::fromUtf8("progress"));
        progress->setMinimumSize(QSize(0, 5));
        progress->setMaximumSize(QSize(16777215, 5));
        progress->setMaximum(4);
        progress->setValue(-1);
        progress->setTextVisible(false);

        verticalLayout->addWidget(progress);


        horizontalLayout->addWidget(frame);

        btnRecoveryBackup = new QPushButton(frame_simulator);
        btnRecoveryBackup->setObjectName(QString::fromUtf8("btnRecoveryBackup"));
        btnRecoveryBackup->setMinimumSize(QSize(115, 40));
        btnRecoveryBackup->setMaximumSize(QSize(115, 40));

        horizontalLayout->addWidget(btnRecoveryBackup);


        verticalLayout_2->addWidget(frame_simulator);


        retranslateUi(IOS_EmulatorDlg);

        QMetaObject::connectSlotsByName(IOS_EmulatorDlg);
    } // setupUi

    void retranslateUi(QFrame *IOS_EmulatorDlg)
    {
        IOS_EmulatorDlg->setWindowTitle(QApplication::translate("IOS_EmulatorDlg", "IOS_EmulatorDlg", 0, QApplication::UnicodeUTF8));
        lbApplist->setText(QApplication::translate("IOS_EmulatorDlg", "\345\272\224\347\224\250\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("IOS_EmulatorDlg", "\345\272\224\347\224\250\346\240\207\350\257\206", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("IOS_EmulatorDlg", "\345\272\224\347\224\250\347\211\210\346\234\254", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("IOS_EmulatorDlg", "\344\273\277\347\234\237\347\275\221\347\273\234\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("IOS_EmulatorDlg", "\346\223\215\344\275\234\346\226\271\345\274\217", 0, QApplication::UnicodeUTF8));
        btnInstallAll->setText(QApplication::translate("IOS_EmulatorDlg", "\345\205\250\351\203\250\345\256\211\350\243\205", 0, QApplication::UnicodeUTF8));
        btnExportAll->setText(QApplication::translate("IOS_EmulatorDlg", "\345\205\250\351\203\250\345\257\274\345\205\245", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = trEmulatorApps->headerItem();
        ___qtreewidgetitem->setText(4, QApplication::translate("IOS_EmulatorDlg", "New Column", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(3, QApplication::translate("IOS_EmulatorDlg", "New Column", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(2, QApplication::translate("IOS_EmulatorDlg", "New Column", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("IOS_EmulatorDlg", "New Column", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("IOS_EmulatorDlg", "1", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = trEmulatorApps->isSortingEnabled();
        trEmulatorApps->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = trEmulatorApps->topLevelItem(0);
        ___qtreewidgetitem1->setText(3, QApplication::translate("IOS_EmulatorDlg", "\345\257\274\345\205\245", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(2, QApplication::translate("IOS_EmulatorDlg", "/data/data/com.tencent.mm", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(0, QApplication::translate("IOS_EmulatorDlg", "\345\276\256\344\277\241", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = trEmulatorApps->topLevelItem(1);
        ___qtreewidgetitem2->setText(0, QApplication::translate("IOS_EmulatorDlg", "New Item", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = trEmulatorApps->topLevelItem(2);
        ___qtreewidgetitem3->setText(0, QApplication::translate("IOS_EmulatorDlg", "New Item", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = trEmulatorApps->topLevelItem(3);
        ___qtreewidgetitem4->setText(0, QApplication::translate("IOS_EmulatorDlg", "New Item", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem5 = trEmulatorApps->topLevelItem(4);
        ___qtreewidgetitem5->setText(0, QApplication::translate("IOS_EmulatorDlg", "New Item", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem6 = trEmulatorApps->topLevelItem(5);
        ___qtreewidgetitem6->setText(0, QApplication::translate("IOS_EmulatorDlg", "New Item", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem7 = trEmulatorApps->topLevelItem(6);
        ___qtreewidgetitem7->setText(0, QApplication::translate("IOS_EmulatorDlg", "New Item", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem8 = trEmulatorApps->topLevelItem(7);
        ___qtreewidgetitem8->setText(0, QApplication::translate("IOS_EmulatorDlg", "New Item", 0, QApplication::UnicodeUTF8));
        trEmulatorApps->setSortingEnabled(__sortingEnabled);

        lbEmulatorStatus->setText(QApplication::translate("IOS_EmulatorDlg", "\350\257\267\346\216\245\345\205\245 iOS \344\273\277\347\234\237\346\234\272", 0, QApplication::UnicodeUTF8));
        btnRecoveryBackup->setText(QApplication::translate("IOS_EmulatorDlg", "\346\201\242\345\244\215\345\244\207\344\273\275", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IOS_EmulatorDlg: public Ui_IOS_EmulatorDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IOS_EMULATORDLG_H
