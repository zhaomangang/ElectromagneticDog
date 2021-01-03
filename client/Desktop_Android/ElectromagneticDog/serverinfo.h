#ifndef SERVERINFO_H
#define SERVERINFO_H

#include <QWidget>

namespace Ui {
class ServerInfo;
}

class ServerInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ServerInfo(QWidget *parent = 0);
    ~ServerInfo();
    QString getIp() const { return ip; }
    unsigned int getPort() const{ return port; }

private slots:
    void on_pushButton_ensure_clicked();

private:
    Ui::ServerInfo *ui;
    QString ip; //ip
    unsigned int port;  //端口

signals:
    void setInfoSuccess(QString ip,unsigned int port);
};

#endif // SERVERINFO_H
