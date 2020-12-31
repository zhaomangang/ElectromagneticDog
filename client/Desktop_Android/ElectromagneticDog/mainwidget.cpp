#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    if (NULL == login)
    {
        //创建登录对象
        login = new Login();
    }
    if (NULL != login)
    {
        this->hide();   //隐藏主界面
        login->show();  //显示登录界面

    }
}

MainWidget::~MainWidget()
{
    delete ui;
}
