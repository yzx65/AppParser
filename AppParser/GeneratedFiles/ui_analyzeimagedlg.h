/********************************************************************************
** Form generated from reading UI file 'analyzeimagedlg.ui'
**
** Created: Wed Apr 1 13:49:51 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYZEIMAGEDLG_H
#define UI_ANALYZEIMAGEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AnalyzeImageDlg
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *image_frame_1;
    QVBoxLayout *verticalLayout_2;
    QLabel *image_sec_1;
    QHBoxLayout *horizontalLayout;
    QComboBox *cmbImage;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnBrowseImage;
    QFrame *image_frame_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *image_sec_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *edtSavePath;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnBrowseSavePath;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btnRecovery;
    QFrame *image_frame_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *image_sec_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *edtSearchStr;
    QSpacerItem *horizontalSpacer_6;
    QRadioButton *btnUtf8;
    QRadioButton *btnGb2312;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnExport;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnSearch;
    QTextEdit *edtResult;
    QProgressBar *searchProgress;

    void setupUi(QFrame *AnalyzeImageDlg)
    {
        if (AnalyzeImageDlg->objectName().isEmpty())
            AnalyzeImageDlg->setObjectName(QString::fromUtf8("AnalyzeImageDlg"));
        AnalyzeImageDlg->resize(648, 463);
        verticalLayout = new QVBoxLayout(AnalyzeImageDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        image_frame_1 = new QFrame(AnalyzeImageDlg);
        image_frame_1->setObjectName(QString::fromUtf8("image_frame_1"));
        image_frame_1->setMinimumSize(QSize(0, 70));
        image_frame_1->setMaximumSize(QSize(16777215, 70));
        image_frame_1->setFrameShape(QFrame::StyledPanel);
        image_frame_1->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(image_frame_1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        image_sec_1 = new QLabel(image_frame_1);
        image_sec_1->setObjectName(QString::fromUtf8("image_sec_1"));

        verticalLayout_2->addWidget(image_sec_1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cmbImage = new QComboBox(image_frame_1);
        cmbImage->setObjectName(QString::fromUtf8("cmbImage"));
        cmbImage->setMinimumSize(QSize(0, 25));

        horizontalLayout->addWidget(cmbImage);

        horizontalSpacer_3 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        btnBrowseImage = new QPushButton(image_frame_1);
        btnBrowseImage->setObjectName(QString::fromUtf8("btnBrowseImage"));
        btnBrowseImage->setMinimumSize(QSize(75, 25));
        btnBrowseImage->setMaximumSize(QSize(75, 25));

        horizontalLayout->addWidget(btnBrowseImage);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(image_frame_1);

        image_frame_2 = new QFrame(AnalyzeImageDlg);
        image_frame_2->setObjectName(QString::fromUtf8("image_frame_2"));
        image_frame_2->setEnabled(false);
        image_frame_2->setFrameShape(QFrame::StyledPanel);
        image_frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(image_frame_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        image_sec_2 = new QLabel(image_frame_2);
        image_sec_2->setObjectName(QString::fromUtf8("image_sec_2"));

        verticalLayout_3->addWidget(image_sec_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        edtSavePath = new QLineEdit(image_frame_2);
        edtSavePath->setObjectName(QString::fromUtf8("edtSavePath"));
        edtSavePath->setMinimumSize(QSize(0, 25));
        edtSavePath->setReadOnly(true);

        horizontalLayout_2->addWidget(edtSavePath);

        horizontalSpacer_2 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnBrowseSavePath = new QPushButton(image_frame_2);
        btnBrowseSavePath->setObjectName(QString::fromUtf8("btnBrowseSavePath"));
        btnBrowseSavePath->setMinimumSize(QSize(75, 25));

        horizontalLayout_2->addWidget(btnBrowseSavePath);

        horizontalSpacer_5 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        btnRecovery = new QPushButton(image_frame_2);
        btnRecovery->setObjectName(QString::fromUtf8("btnRecovery"));
        btnRecovery->setMinimumSize(QSize(75, 25));

        horizontalLayout_2->addWidget(btnRecovery);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(image_frame_2);

        image_frame_3 = new QFrame(AnalyzeImageDlg);
        image_frame_3->setObjectName(QString::fromUtf8("image_frame_3"));
        image_frame_3->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(image_frame_3->sizePolicy().hasHeightForWidth());
        image_frame_3->setSizePolicy(sizePolicy);
        image_frame_3->setFrameShape(QFrame::StyledPanel);
        image_frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(image_frame_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        image_sec_3 = new QLabel(image_frame_3);
        image_sec_3->setObjectName(QString::fromUtf8("image_sec_3"));

        verticalLayout_4->addWidget(image_sec_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        edtSearchStr = new QLineEdit(image_frame_3);
        edtSearchStr->setObjectName(QString::fromUtf8("edtSearchStr"));
        edtSearchStr->setMinimumSize(QSize(250, 25));

        horizontalLayout_3->addWidget(edtSearchStr);

        horizontalSpacer_6 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        btnUtf8 = new QRadioButton(image_frame_3);
        btnUtf8->setObjectName(QString::fromUtf8("btnUtf8"));
        btnUtf8->setChecked(true);

        horizontalLayout_3->addWidget(btnUtf8);

        btnGb2312 = new QRadioButton(image_frame_3);
        btnGb2312->setObjectName(QString::fromUtf8("btnGb2312"));

        horizontalLayout_3->addWidget(btnGb2312);

        horizontalSpacer = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        btnExport = new QPushButton(image_frame_3);
        btnExport->setObjectName(QString::fromUtf8("btnExport"));
        btnExport->setMinimumSize(QSize(75, 25));

        horizontalLayout_3->addWidget(btnExport);

        horizontalSpacer_4 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        btnSearch = new QPushButton(image_frame_3);
        btnSearch->setObjectName(QString::fromUtf8("btnSearch"));
        btnSearch->setMinimumSize(QSize(75, 25));

        horizontalLayout_3->addWidget(btnSearch);


        verticalLayout_4->addLayout(horizontalLayout_3);

        edtResult = new QTextEdit(image_frame_3);
        edtResult->setObjectName(QString::fromUtf8("edtResult"));
        edtResult->setFrameShape(QFrame::NoFrame);
        edtResult->setReadOnly(true);

        verticalLayout_4->addWidget(edtResult);

        searchProgress = new QProgressBar(image_frame_3);
        searchProgress->setObjectName(QString::fromUtf8("searchProgress"));
        searchProgress->setMaximumSize(QSize(16777215, 5));
        searchProgress->setValue(0);
        searchProgress->setTextVisible(false);

        verticalLayout_4->addWidget(searchProgress);


        verticalLayout->addWidget(image_frame_3);


        retranslateUi(AnalyzeImageDlg);

        QMetaObject::connectSlotsByName(AnalyzeImageDlg);
    } // setupUi

    void retranslateUi(QFrame *AnalyzeImageDlg)
    {
        AnalyzeImageDlg->setWindowTitle(QApplication::translate("AnalyzeImageDlg", "AnalyzeImageDlg", 0, QApplication::UnicodeUTF8));
        image_sec_1->setText(QApplication::translate("AnalyzeImageDlg", "\351\200\211\346\213\251\351\225\234\345\203\217\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        btnBrowseImage->setText(QApplication::translate("AnalyzeImageDlg", "\346\265\217\350\247\210", 0, QApplication::UnicodeUTF8));
        image_sec_2->setText(QApplication::translate("AnalyzeImageDlg", "\351\225\234\345\203\217\345\206\205\345\210\240\351\231\244\346\226\207\344\273\266\346\201\242\345\244\215", 0, QApplication::UnicodeUTF8));
        edtSavePath->setPlaceholderText(QApplication::translate("AnalyzeImageDlg", "\351\200\211\346\213\251\344\277\235\345\255\230\347\233\256\345\275\225", 0, QApplication::UnicodeUTF8));
        btnBrowseSavePath->setText(QApplication::translate("AnalyzeImageDlg", "\346\265\217\350\247\210", 0, QApplication::UnicodeUTF8));
        btnRecovery->setText(QApplication::translate("AnalyzeImageDlg", "\345\274\200\345\247\213\346\201\242\345\244\215", 0, QApplication::UnicodeUTF8));
        image_sec_3->setText(QApplication::translate("AnalyzeImageDlg", "\351\225\234\345\203\217\345\206\205\345\255\227\347\254\246\344\270\262\346\220\234\347\264\242", 0, QApplication::UnicodeUTF8));
        btnUtf8->setText(QApplication::translate("AnalyzeImageDlg", "UTF-8", 0, QApplication::UnicodeUTF8));
        btnGb2312->setText(QApplication::translate("AnalyzeImageDlg", "GB2312", 0, QApplication::UnicodeUTF8));
        btnExport->setText(QApplication::translate("AnalyzeImageDlg", "\345\257\274\345\207\272\347\273\223\346\236\234", 0, QApplication::UnicodeUTF8));
        btnSearch->setText(QApplication::translate("AnalyzeImageDlg", "\345\274\200\345\247\213\346\220\234\347\264\242", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AnalyzeImageDlg: public Ui_AnalyzeImageDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYZEIMAGEDLG_H
