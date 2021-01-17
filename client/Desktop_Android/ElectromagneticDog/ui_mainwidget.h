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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_userinfo;
    QGridLayout *gridLayout;
    QLabel *label_icon;
    QLabel *label_username;
    QLabel *label_3;
    QTabWidget *tabWidget;
    QWidget *tab_chat;
    QVBoxLayout *verticalLayout_2;
    QToolBox *toolBox;
    QWidget *page_friend;
    QWidget *page_group;
    QFrame *frame_menu;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *tab_music;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit;
    QPushButton *pushButton_3;
    QTableView *tableView;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_2;
    QLabel *label_4;

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
        label_icon = new QLabel(widget_userinfo);
        label_icon->setObjectName(QStringLiteral("label_icon"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_icon->sizePolicy().hasHeightForWidth());
        label_icon->setSizePolicy(sizePolicy);
        label_icon->setMaximumSize(QSize(128, 128));
        label_icon->setPixmap(QPixmap(QString::fromUtf8(":/resource/ed.png")));
        label_icon->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_icon, 0, 0, 2, 1);

        label_username = new QLabel(widget_userinfo);
        label_username->setObjectName(QStringLiteral("label_username"));
        label_username->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_username, 0, 1, 1, 1);

        label_3 = new QLabel(widget_userinfo);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 1, 1, 1, 1);


        verticalLayout->addWidget(widget_userinfo);

        tabWidget = new QTabWidget(MainWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_chat = new QWidget();
        tab_chat->setObjectName(QStringLiteral("tab_chat"));
        verticalLayout_2 = new QVBoxLayout(tab_chat);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        toolBox = new QToolBox(tab_chat);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        page_friend = new QWidget();
        page_friend->setObjectName(QStringLiteral("page_friend"));
        page_friend->setGeometry(QRect(0, 0, 260, 362));
        toolBox->addItem(page_friend, QString::fromUtf8("\345\245\275\345\217\213\345\210\227\350\241\250"));
        page_group = new QWidget();
        page_group->setObjectName(QStringLiteral("page_group"));
        page_group->setGeometry(QRect(0, 0, 260, 362));
        toolBox->addItem(page_group, QString::fromUtf8("\347\276\244\347\273\204\345\210\227\350\241\250"));

        verticalLayout_2->addWidget(toolBox);

        frame_menu = new QFrame(tab_chat);
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


        verticalLayout_2->addWidget(frame_menu);

        tabWidget->addTab(tab_chat, QString());
        tab_music = new QWidget();
        tab_music->setObjectName(QStringLiteral("tab_music"));
        verticalLayout_3 = new QVBoxLayout(tab_music);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        frame_2 = new QFrame(tab_music);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lineEdit = new QLineEdit(frame_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_3->addWidget(lineEdit);

        pushButton_3 = new QPushButton(frame_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_3->addWidget(pushButton_3);


        verticalLayout_3->addWidget(frame_2);

        tableView = new QTableView(tab_music);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout_3->addWidget(tableView);

        frame = new QFrame(tab_music);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        widget = new QWidget(frame);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 0, 1, 1, 1);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 1, 1, 1, 1);


        horizontalLayout_2->addWidget(widget);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);


        verticalLayout_3->addWidget(frame);

        tabWidget->addTab(tab_music, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(MainWidget);

        tabWidget->setCurrentIndex(0);
        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "Form", Q_NULLPTR));
        label_icon->setText(QString());
        label_username->setText(QApplication::translate("MainWidget", "TextLabel", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWidget", "TextLabel", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_friend), QApplication::translate("MainWidget", "\345\245\275\345\217\213\345\210\227\350\241\250", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_group), QApplication::translate("MainWidget", "\347\276\244\347\273\204\345\210\227\350\241\250", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWidget", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWidget", "PushButton", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_chat), QApplication::translate("MainWidget", "\350\201\212\345\244\251", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWidget", "PushButton", Q_NULLPTR));
        label->setText(QApplication::translate("MainWidget", "TextLabel", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWidget", "TextLabel", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWidget", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWidget", "TextLabel", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWidget", "TextLabel", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_music), QApplication::translate("MainWidget", "\351\237\263\344\271\220", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
