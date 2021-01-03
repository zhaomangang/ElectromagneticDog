#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login),
    server_info(NULL)
{
    ui->setupUi(this);
    if (NULL == server_info)
    {
        server_info = new ServerInfo();
    }
    if (NULL != server_info)
    {
        //开辟成功
        server_info->show();
    }
}

Login::~Login()
{
    delete ui;
}

void Login::on_button_login_clicked()
{
    //点击登录

}

void Login::on_button_set_clicked()
{
    if (NULL != server_info)
    {
        server_info->show();
    }
}
