#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMessageBox>
#include "chatsocket.h"
#include "apply_protocl.h"
#include "serverinfo.h"
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(ChatSocket* c,QWidget *parent = 0);
    ServerInfo* getServerInfo() const { return server_info; }
    ~Login();

private slots:

    void on_button_login_clicked();

    void on_button_set_clicked();
public slots:


private:
    Ui::Login *ui;
    ServerInfo* server_info;
    ChatSocket *cs;
};

#endif // LOGIN_H
