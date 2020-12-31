#include "friendbutton.h"

FriendButton::FriendButton(unsigned int t_id, QString t_icon, QString t_uname, QString t_cname)
    : id(t_id), icon(t_icon),user_name(t_uname), comment_name(t_cname)
{
    //创建buttton
    if (NULL == toolButton)
    {
        toolButton = new QToolButton();
    }
    if (NULL != toolButton)
    {
        QString text = "";
        //设置信息
        if ("" != comment_name)
        {
            //有备注,优先备注
            text = QString("%1<%2>").arg(comment_name).arg(user_name);
        }
        else
        {
            //无备注，直接用户名
            text = user_name;
        }
        toolButton->setText(text);

        toolButton->setIcon(QPixmap(icon)); //设置头像
        toolButton->setIconSize(FRIEND_BUTTON_SIZE); //设置按钮尺寸
        toolButton->setAutoRaise(true);   //当鼠标离开时，按钮恢复为弹起状态
        toolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); //设置按钮文字显示在图标旁边
    }
}

FriendButton::~FriendButton()
{
    //释放内存
    if (NULL != toolButton)
    {
        delete toolButton;
        toolButton = NULL;
    }
}
