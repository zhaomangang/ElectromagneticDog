/********************************************************************************
** Form generated from reading UI file 'serverinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERINFO_H
#define UI_SERVERINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerInfo
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_port;
    QLabel *label;
    QLineEdit *lineEdit_ip;
    QPushButton *pushButton_ensure;

    void setupUi(QWidget *ServerInfo)
    {
        if (ServerInfo->objectName().isEmpty())
            ServerInfo->setObjectName(QStringLiteral("ServerInfo"));
        ServerInfo->resize(285, 142);
        gridLayout = new QGridLayout(ServerInfo);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(ServerInfo);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_port = new QLineEdit(ServerInfo);
        lineEdit_port->setObjectName(QStringLiteral("lineEdit_port"));

        gridLayout->addWidget(lineEdit_port, 1, 1, 1, 1);

        label = new QLabel(ServerInfo);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit_ip = new QLineEdit(ServerInfo);
        lineEdit_ip->setObjectName(QStringLiteral("lineEdit_ip"));

        gridLayout->addWidget(lineEdit_ip, 0, 1, 1, 1);

        pushButton_ensure = new QPushButton(ServerInfo);
        pushButton_ensure->setObjectName(QStringLiteral("pushButton_ensure"));

        gridLayout->addWidget(pushButton_ensure, 2, 1, 1, 1);


        retranslateUi(ServerInfo);

        QMetaObject::connectSlotsByName(ServerInfo);
    } // setupUi

    void retranslateUi(QWidget *ServerInfo)
    {
        ServerInfo->setWindowTitle(QApplication::translate("ServerInfo", "serverInfo", Q_NULLPTR));
        label_2->setText(QApplication::translate("ServerInfo", "port", Q_NULLPTR));
        lineEdit_port->setText(QApplication::translate("ServerInfo", "61521", Q_NULLPTR));
        label->setText(QApplication::translate("ServerInfo", "ip", Q_NULLPTR));
        lineEdit_ip->setText(QApplication::translate("ServerInfo", "192.168.43.2", Q_NULLPTR));
        pushButton_ensure->setText(QApplication::translate("ServerInfo", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ServerInfo: public Ui_ServerInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERINFO_H
