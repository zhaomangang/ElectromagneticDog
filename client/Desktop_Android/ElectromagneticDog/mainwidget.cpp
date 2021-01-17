#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    login(NULL),
    socket(NULL)
{
    ui->setupUi(this);
    this->hide();   //隐藏主界面
    if (NULL == socket)
    {
        socket = new ChatSocket;
    }
    if (NULL == login)
    {
        //创建登录对象
        qDebug()<<"login is null";
        login = new Login(socket);
    }
    if (NULL != login)
    {
        qDebug()<<"login not null";
        login->show();  //显示登录界面
    }

    connect(login->getServerInfo(),SIGNAL(setInfoSuccess(QString,uint)),
           socket,SLOT(slotConnectToServer(QString,uint)));
    connect(socket,SIGNAL(logonSuccess(int,QString,QString)),this,SLOT(slotLogonSuccess(int,QString,QString)));
}

void MainWidget::slotLogonSuccess(int id, QString username, QString icon)
{
    this->show();
    if (NULL != login)
    {
        login->hide();
        delete login;
    }
    ui->label_username->setText(username);
    ui->label_3->setText(QString("id:%1").arg(id));

}

MainWidget::~MainWidget()
{
    delete ui;
}
