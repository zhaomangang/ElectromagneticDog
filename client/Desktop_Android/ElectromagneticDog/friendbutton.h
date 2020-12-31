#ifndef FRIENDBUTTON_H
#define FRIENDBUTTON_H

#include <QToolButton>
#include "fixedvalue.h"
class FriendButton
{
public:
    FriendButton(unsigned int t_id = 0,QString t_icon = "",QString t_uname = "",QString t_cname = "");
    ~FriendButton();
    QToolButton* getButton() const{ return toolButton; }    //获取当前按钮
    void newMessage(QString message);   //有新消息
private:
    QToolButton* toolButton;    //用于显示好友昵称等信息
    unsigned int id;    //好友id
    QString icon;   //头像
    QString user_name;   //用户名
    QString comment_name;    //备注名


};

#endif // FRIENDBUTTON_H
