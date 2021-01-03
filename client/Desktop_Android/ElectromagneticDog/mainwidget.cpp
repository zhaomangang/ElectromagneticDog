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
}



MainWidget::~MainWidget()
{
    delete ui;
}
