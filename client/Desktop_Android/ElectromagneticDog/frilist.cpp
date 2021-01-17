#include "frilist.h"
#include <QGroupBox>
#include <QVBoxLayout>

FriList::FriList(QWidget *parent,Qt::WindowFlags f)
    :QToolBox(parent,f)
{
    friendBox = new QGroupBox;
    groupBox = new QGroupBox;

    this->setLayFri();
    this->setLayGro();
}



void FriList::setLayFri()
{
    //好友页布局
    layout_fri = new QVBoxLayout(friendBox);
    layout_fri->setMargin(45);
    layout_fri->setAlignment(Qt::AlignLeft);
    this->addItem((QWidget*)friendBox,QStringLiteral("好友列表"));
}
void FriList::setLayGro()
{
    //群组页布局
    layout_group = new QVBoxLayout(groupBox);
    layout_fri->setMargin(45);
    layout_fri->setAlignment(Qt::AlignLeft);
    this->addItem((QWidget*)groupBox,QStringLiteral("群组列表"));
}

void FriList::addFriend(QToolButton *tempButton)
{
    layout_fri->addWidget(tempButton);
}

void FriList::addGroup(QToolButton *tempButton)
{
    layout_group->addWidget(tempButton);
}


