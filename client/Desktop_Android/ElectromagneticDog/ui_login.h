/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QPushButton *button_login;
    QLabel *label;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox_remberpwd;
    QCheckBox *checkBox;
    QLineEdit *input_password;
    QLineEdit *input_user;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *button_regsiter;
    QPushButton *button_set;
    QPushButton *button_find;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(339, 399);
        verticalLayout = new QVBoxLayout(Login);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame_3 = new QFrame(Login);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_4 = new QLabel(frame_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/resource/ed.png")));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_4);


        verticalLayout->addWidget(frame_3);

        frame = new QFrame(Login);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/resource/password.png")));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        button_login = new QPushButton(frame);
        button_login->setObjectName(QStringLiteral("button_login"));
        sizePolicy.setHeightForWidth(button_login->sizePolicy().hasHeightForWidth());
        button_login->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/resource/login.png"), QSize(), QIcon::Normal, QIcon::Off);
        button_login->setIcon(icon);

        gridLayout->addWidget(button_login, 4, 0, 1, 4);

        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setPixmap(QPixmap(QString::fromUtf8(":/resource/user.png")));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        widget = new QWidget(frame);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        checkBox_remberpwd = new QCheckBox(widget);
        checkBox_remberpwd->setObjectName(QStringLiteral("checkBox_remberpwd"));

        horizontalLayout_2->addWidget(checkBox_remberpwd);

        checkBox = new QCheckBox(widget);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout_2->addWidget(checkBox);


        gridLayout->addWidget(widget, 3, 1, 1, 3);

        input_password = new QLineEdit(frame);
        input_password->setObjectName(QStringLiteral("input_password"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(input_password->sizePolicy().hasHeightForWidth());
        input_password->setSizePolicy(sizePolicy2);
        input_password->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(input_password, 2, 1, 1, 3);

        input_user = new QLineEdit(frame);
        input_user->setObjectName(QStringLiteral("input_user"));
        sizePolicy2.setHeightForWidth(input_user->sizePolicy().hasHeightForWidth());
        input_user->setSizePolicy(sizePolicy2);
        input_user->setInputMethodHints(Qt::ImhNone);
        input_user->setMaxLength(10);
        input_user->setEchoMode(QLineEdit::Normal);
        input_user->setClearButtonEnabled(false);

        gridLayout->addWidget(input_user, 1, 1, 1, 3);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(Login);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        button_regsiter = new QPushButton(frame_2);
        button_regsiter->setObjectName(QStringLiteral("button_regsiter"));

        horizontalLayout->addWidget(button_regsiter);

        button_set = new QPushButton(frame_2);
        button_set->setObjectName(QStringLiteral("button_set"));

        horizontalLayout->addWidget(button_set);

        button_find = new QPushButton(frame_2);
        button_find->setObjectName(QStringLiteral("button_find"));

        horizontalLayout->addWidget(button_find);


        verticalLayout->addWidget(frame_2);

        frame->raise();
        frame_2->raise();
        frame_3->raise();

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Login", Q_NULLPTR));
        label_4->setText(QString());
        label_2->setText(QString());
        button_login->setText(QApplication::translate("Login", "\347\231\273\345\275\225", Q_NULLPTR));
        label->setText(QString());
        checkBox_remberpwd->setText(QApplication::translate("Login", "\350\256\260\344\275\217\345\257\206\347\240\201", Q_NULLPTR));
        checkBox->setText(QApplication::translate("Login", "\350\256\260\344\275\217\350\264\246\345\217\267", Q_NULLPTR));
        input_password->setInputMask(QString());
        input_password->setText(QString());
        input_password->setPlaceholderText(QApplication::translate("Login", "\345\257\206\347\240\201", Q_NULLPTR));
        input_user->setInputMask(QString());
        input_user->setText(QString());
        input_user->setPlaceholderText(QApplication::translate("Login", "\350\264\246\345\217\267", Q_NULLPTR));
        button_regsiter->setText(QApplication::translate("Login", "\346\263\250\345\206\214\350\264\246\345\217\267", Q_NULLPTR));
        button_set->setText(QApplication::translate("Login", "\346\234\215\345\212\241\345\231\250\351\205\215\347\275\256", Q_NULLPTR));
        button_find->setText(QApplication::translate("Login", "\346\211\276\345\233\236\345\257\206\347\240\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
