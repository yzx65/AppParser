/********************************************************************************
** Form generated from reading UI file 'mapinfodlg.ui'
**
** Created: Wed Apr 1 13:49:51 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPINFODLG_H
#define UI_MAPINFODLG_H

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

class Ui_MapInfoDlg
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame_titlebar;
    QHBoxLayout *horizontalLayout;
    QRadioButton *btnRoute;
    QRadioButton *btnPos;
    QSpacerItem *horizontalSpacer;
    QListView *lstMapData;

    void setupUi(QFrame *MapInfoDlg)
    {
        if (MapInfoDlg->objectName().isEmpty())
            MapInfoDlg->setObjectName(QString::fromUtf8("MapInfoDlg"));
        MapInfoDlg->resize(737, 300);
        verticalLayout = new QVBoxLayout(MapInfoDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_titlebar = new QFrame(MapInfoDlg);
        frame_titlebar->setObjectName(QString::fromUtf8("frame_titlebar"));
        frame_titlebar->setMinimumSize(QSize(0, 34));
        frame_titlebar->setMaximumSize(QSize(16777215, 34));
        frame_titlebar->setFrameShape(QFrame::StyledPanel);
        frame_titlebar->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_titlebar);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 0, 0, 0);
        btnRoute = new QRadioButton(frame_titlebar);
        btnRoute->setObjectName(QString::fromUtf8("btnRoute"));
        btnRoute->setMinimumSize(QSize(120, 0));
        btnRoute->setChecked(true);

        horizontalLayout->addWidget(btnRoute);

        btnPos = new QRadioButton(frame_titlebar);
        btnPos->setObjectName(QString::fromUtf8("btnPos"));
        btnPos->setMinimumSize(QSize(120, 0));

        horizontalLayout->addWidget(btnPos);

        horizontalSpacer = new QSpacerItem(411, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(frame_titlebar);

        lstMapData = new QListView(MapInfoDlg);
        lstMapData->setObjectName(QString::fromUtf8("lstMapData"));
        lstMapData->setFocusPolicy(Qt::NoFocus);
        lstMapData->setFrameShape(QFrame::NoFrame);
        lstMapData->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(lstMapData);


        retranslateUi(MapInfoDlg);

        QMetaObject::connectSlotsByName(MapInfoDlg);
    } // setupUi

    void retranslateUi(QFrame *MapInfoDlg)
    {
        MapInfoDlg->setWindowTitle(QApplication::translate("MapInfoDlg", "MapInfoDlg", 0, QApplication::UnicodeUTF8));
        btnRoute->setText(QApplication::translate("MapInfoDlg", "\346\220\234\347\264\242\350\267\257\347\272\277", 0, QApplication::UnicodeUTF8));
        btnPos->setText(QApplication::translate("MapInfoDlg", "\346\220\234\347\264\242\345\234\260\347\202\271", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MapInfoDlg: public Ui_MapInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPINFODLG_H
