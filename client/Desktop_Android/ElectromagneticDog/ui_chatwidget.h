/********************************************************************************
** Form generated from reading UI file 'chatwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWIDGET_H
#define UI_CHATWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_2;
    QTextBrowser *textBrowser_2;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *ChatWidget)
    {
        if (ChatWidget->objectName().isEmpty())
            ChatWidget->setObjectName(QStringLiteral("ChatWidget"));
        ChatWidget->resize(764, 469);
        verticalLayout = new QVBoxLayout(ChatWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textBrowser = new QTextBrowser(ChatWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        frame = new QFrame(ChatWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_2->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(frame);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout_2->addWidget(pushButton_5);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);


        verticalLayout->addWidget(frame);

        textBrowser_2 = new QTextBrowser(ChatWidget);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));

        verticalLayout->addWidget(textBrowser_2);

        frame_2 = new QFrame(ChatWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(frame_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addWidget(frame_2);


        retranslateUi(ChatWidget);

        QMetaObject::connectSlotsByName(ChatWidget);
    } // setupUi

    void retranslateUi(QWidget *ChatWidget)
    {
        ChatWidget->setWindowTitle(QApplication::translate("ChatWidget", "Form", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("ChatWidget", "PushButton", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("ChatWidget", "PushButton", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("ChatWidget", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("ChatWidget", "PushButton", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ChatWidget", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChatWidget: public Ui_ChatWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWIDGET_H
