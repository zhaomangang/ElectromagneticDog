#ifndef FRILIST_H
#define FRILIST_H
#include <QToolBox>
#include <QToolButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QList>
#include <QDebug>

class FriList : public QToolBox
{
    Q_OBJECT
public:
    FriList(QWidget *parent=0,Qt::WindowFlags f=0);
    void setLayFri();   //好友页布局
    void setLayGro();   //群组页布局
    void addFriend(QToolButton *tempButton);  //添加好友
    void addGroup(QToolButton *tempButton);   //添加群组
private:
    QList <QToolButton *>friend_list;   //好友列表
    QList <QToolButton *>group_list;    //群组列表
    QGroupBox *friendBox;   //好友页
    QGroupBox *groupBox;    //群组页
    QVBoxLayout *layout_fri;    //好友页布局
    QVBoxLayout *layout_group;  //群组页布局
public slots:

};



#endif // DRAWER_H
