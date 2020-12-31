/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_userinfo;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QFrame *frame_menu;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QStringLiteral("MainWidget"));
        MainWidget->resize(310, 701);
        verticalLayout = new QVBoxLayout(MainWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_userinfo = new QWidget(MainWidget);
        widget_userinfo->setObjectName(QStringLiteral("widget_userinfo"));
        gridLayout = new QGridLayout(widget_userinfo);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(widget_userinfo);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 2, 1);

        label_2 = new QLabel(widget_userinfo);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        label_3 = new QLabel(widget_userinfo);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 1, 1, 1);


        verticalLayout->addWidget(widget_userinfo);

        tabWidget = new QTabWidget(MainWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        frame_menu = new QFrame(MainWidget);
        frame_menu->setObjectName(QStringLiteral("frame_menu"));
        frame_menu->setFrameShape(QFrame::StyledPanel);
        frame_menu->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_menu);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(frame_menu);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(frame_menu);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addWidget(frame_menu);


        retranslateUi(MainWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("MainWidget", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWidget", "TextLabel", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWidget", "TextLabel", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWidget", "\350\201\212\345\244\251", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWidget", "\346\226\207\344\273\266", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWidget", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWidget", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
