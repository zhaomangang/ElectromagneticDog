#include "login.h"
#include "ui_login.h"

Login::Login(ChatSocket* c,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login),
    cs(c),
    server_info(NULL)
{
    ui->setupUi(this);
    ui->input_user->setValidator(new QIntValidator(10001, 9999999999, this));
    if (NULL == server_info)
    {
        server_info = new ServerInfo();
    }
}

Login::~Login()
{
    delete ui;
}

void Login::on_button_login_clicked()
{
    //点击登录
    if ("" == ui->input_user->text() || "" == ui->input_password->text())
    {
        QMessageBox::warning(this,"error","请输入用户名&&密码");
    }
    else {
        cs->sendLogin(ui->input_user->text().toInt(),"",ui->input_password->text());
    }
}


void Login::on_button_set_clicked()
{
    if (NULL != server_info)
    {
        server_info->show();
    }
}
