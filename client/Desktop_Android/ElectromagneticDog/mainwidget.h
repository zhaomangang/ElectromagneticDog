#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "login.h"
#include "chatsocket.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    Login* login;   //登录界面
    ChatSocket *socket;



};

#endif // MAINWIDGET_H
