/********************************************************************************
** Form generated from reading UI file 'imageextractor.ui'
**
** Created: Wed Apr 1 09:13:22 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEEXTRACTOR_H
#define UI_IMAGEEXTRACTOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
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
#include <QtGui/QStackedWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageExtractorClass
{
public:
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout;
    QLabel *info_3;
    QHBoxLayout *horizontalLayout_5;
    QComboBox *cmbTask;
    QLabel *info_1;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *btnDefaultOutputPath;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *btnCustomOutputPath;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *edtOutputPath;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnBrowseOutputPath;
    QSpacerItem *horizontalSpacer_6;
    QLabel *info_2;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *btnExtractFile;
    QCheckBox *btnMergeImage;
    QCheckBox *btnExtractImageFile;
    QSpacerItem *horizontalSpacer_5;
    QFrame *frame_bottom_bar;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *lbStatus;
    QProgressBar *progressBar;
    QPushButton *btnStart;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *edtLog;
    QProgressBar *progress;

    void setupUi(QFrame *ImageExtractorClass)
    {
        if (ImageExtractorClass->objectName().isEmpty())
            ImageExtractorClass->setObjectName(QString::fromUtf8("ImageExtractorClass"));
        ImageExtractorClass->resize(422, 338);
        ImageExtractorClass->setStyleSheet(QString::fromUtf8("QFrame#ImageExtractorClass\n"
"{\n"
"	background-color:white;\n"
"}"));
        horizontalLayout = new QHBoxLayout(ImageExtractorClass);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        stackedWidget = new QStackedWidget(ImageExtractorClass);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setStyleSheet(QString::fromUtf8("QFrame#stackedWidget\n"
"{\n"
"	background-color:white;\n"
"}"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout = new QVBoxLayout(page);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 0);
        info_3 = new QLabel(page);
        info_3->setObjectName(QString::fromUtf8("info_3"));
        info_3->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(info_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(20, 0, -1, -1);
        cmbTask = new QComboBox(page);
        cmbTask->setObjectName(QString::fromUtf8("cmbTask"));
        cmbTask->setMinimumSize(QSize(0, 25));

        horizontalLayout_5->addWidget(cmbTask);


        verticalLayout->addLayout(horizontalLayout_5);

        info_1 = new QLabel(page);
        info_1->setObjectName(QString::fromUtf8("info_1"));
        info_1->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(info_1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(20, 0, -1, -1);
        btnDefaultOutputPath = new QRadioButton(page);
        btnDefaultOutputPath->setObjectName(QString::fromUtf8("btnDefaultOutputPath"));
        btnDefaultOutputPath->setMinimumSize(QSize(0, 25));
        btnDefaultOutputPath->setChecked(true);

        horizontalLayout_4->addWidget(btnDefaultOutputPath);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(20, -1, -1, -1);
        btnCustomOutputPath = new QRadioButton(page);
        btnCustomOutputPath->setObjectName(QString::fromUtf8("btnCustomOutputPath"));
        btnCustomOutputPath->setMinimumSize(QSize(0, 25));

        horizontalLayout_2->addWidget(btnCustomOutputPath);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        edtOutputPath = new QLineEdit(page);
        edtOutputPath->setObjectName(QString::fromUtf8("edtOutputPath"));
        edtOutputPath->setMinimumSize(QSize(0, 25));
        edtOutputPath->setReadOnly(true);

        horizontalLayout_2->addWidget(edtOutputPath);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        btnBrowseOutputPath = new QPushButton(page);
        btnBrowseOutputPath->setObjectName(QString::fromUtf8("btnBrowseOutputPath"));
        btnBrowseOutputPath->setMinimumSize(QSize(70, 25));
        btnBrowseOutputPath->setMaximumSize(QSize(50, 25));

        horizontalLayout_2->addWidget(btnBrowseOutputPath);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_2);

        info_2 = new QLabel(page);
        info_2->setObjectName(QString::fromUtf8("info_2"));
        info_2->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(info_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(20, -1, -1, 10);
        btnExtractFile = new QCheckBox(page);
        btnExtractFile->setObjectName(QString::fromUtf8("btnExtractFile"));

        horizontalLayout_6->addWidget(btnExtractFile);

        btnMergeImage = new QCheckBox(page);
        btnMergeImage->setObjectName(QString::fromUtf8("btnMergeImage"));

        horizontalLayout_6->addWidget(btnMergeImage);

        btnExtractImageFile = new QCheckBox(page);
        btnExtractImageFile->setObjectName(QString::fromUtf8("btnExtractImageFile"));

        horizontalLayout_6->addWidget(btnExtractImageFile);

        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_6);

        frame_bottom_bar = new QFrame(page);
        frame_bottom_bar->setObjectName(QString::fromUtf8("frame_bottom_bar"));
        horizontalLayout_3 = new QHBoxLayout(frame_bottom_bar);
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, -1, -1, 5);
        lbStatus = new QLabel(frame_bottom_bar);
        lbStatus->setObjectName(QString::fromUtf8("lbStatus"));

        verticalLayout_3->addWidget(lbStatus);

        progressBar = new QProgressBar(frame_bottom_bar);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimumSize(QSize(0, 5));
        progressBar->setMaximumSize(QSize(16777215, 5));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        verticalLayout_3->addWidget(progressBar);


        horizontalLayout_3->addLayout(verticalLayout_3);

        btnStart = new QPushButton(frame_bottom_bar);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setMinimumSize(QSize(100, 40));

        horizontalLayout_3->addWidget(btnStart);


        verticalLayout->addWidget(frame_bottom_bar);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_2 = new QVBoxLayout(page_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        edtLog = new QTextEdit(page_2);
        edtLog->setObjectName(QString::fromUtf8("edtLog"));

        verticalLayout_2->addWidget(edtLog);

        progress = new QProgressBar(page_2);
        progress->setObjectName(QString::fromUtf8("progress"));
        progress->setMinimumSize(QSize(0, 10));
        progress->setMaximumSize(QSize(16777215, 10));
        progress->setValue(24);
        progress->setTextVisible(false);

        verticalLayout_2->addWidget(progress);

        stackedWidget->addWidget(page_2);

        horizontalLayout->addWidget(stackedWidget);


        retranslateUi(ImageExtractorClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ImageExtractorClass);
    } // setupUi

    void retranslateUi(QFrame *ImageExtractorClass)
    {
        ImageExtractorClass->setWindowTitle(QApplication::translate("ImageExtractorClass", "ImageExtractor", 0, QApplication::UnicodeUTF8));
        info_3->setText(QApplication::translate("ImageExtractorClass", "\351\200\211\346\213\251\344\273\273\345\212\241", 0, QApplication::UnicodeUTF8));
        info_1->setText(QApplication::translate("ImageExtractorClass", "\351\207\212\346\224\276\344\275\215\347\275\256", 0, QApplication::UnicodeUTF8));
        btnDefaultOutputPath->setText(QApplication::translate("ImageExtractorClass", "\351\273\230\350\256\244\347\233\256\345\275\225", 0, QApplication::UnicodeUTF8));
        btnCustomOutputPath->setText(QApplication::translate("ImageExtractorClass", "\350\207\252\345\256\232\344\271\211\347\233\256\345\275\225", 0, QApplication::UnicodeUTF8));
        btnBrowseOutputPath->setText(QApplication::translate("ImageExtractorClass", "\346\265\217\350\247\210", 0, QApplication::UnicodeUTF8));
        info_2->setText(QApplication::translate("ImageExtractorClass", "\351\200\211\346\213\251\346\223\215\344\275\234", 0, QApplication::UnicodeUTF8));
        btnExtractFile->setText(QApplication::translate("ImageExtractorClass", "\351\207\212\346\224\276\345\277\253\351\200\237\345\217\226\350\257\201\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        btnMergeImage->setText(QApplication::translate("ImageExtractorClass", "\345\210\206\347\211\207\351\225\234\345\203\217\345\220\210\345\271\266", 0, QApplication::UnicodeUTF8));
        btnExtractImageFile->setText(QApplication::translate("ImageExtractorClass", "\351\225\234\345\203\217\345\220\210\345\271\266\345\220\216\345\257\274\345\207\272\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        lbStatus->setText(QString());
        btnStart->setText(QApplication::translate("ImageExtractorClass", "\345\274\200\345\247\213", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImageExtractorClass: public Ui_ImageExtractorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEEXTRACTOR_H
