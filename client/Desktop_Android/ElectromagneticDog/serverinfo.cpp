#include "serverinfo.h"
#include "ui_serverinfo.h"

ServerInfo::ServerInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerInfo)
{
    ui->setupUi(this);
    ip = "";
    port = 0;
}

ServerInfo::~ServerInfo()
{
    delete ui;
}

void ServerInfo::on_pushButton_ensure_clicked()
{
    //确认
    ip = ui->lineEdit_ip->text();
    port = ui->lineEdit_port->text().toInt();
    emit setInfoSuccess(ip,port);
    this->hide();
}
