#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "login.h"
#include "chatsocket.h"
#include "frilist.h"
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
    FriList *friend_list_widget;
    int id;
    QVBoxLayout *layout_friend;
    QVBoxLayout *layout_group;
    QNetworkAccessManager* m_networkManager;
public slots:
    void slotLogonSuccess(int id,QString username,QString icon);
    void slotReplyFinished(QNetworkReply *);


};

#endif // MAINWIDGET_H
