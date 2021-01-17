/**************************************************************
 * filename: apply_protocl.h
 * time: 2020.12.31 22:38
 * author: mason
 * email: zhaomangang@qq.com
 * describe: Definition of the application layer protocol.
 * ************************************************************/

#ifndef APPLY_PROTOCL_H
#define APPLY_PROTOCL_H


/********************消息类型******************************/

#define TYPE_LOGON_ERROR -1    //登录错误消息
#define TYPE_ERROR 0   //错误
#define TYPE_LOGIN 1  //登录
#define TYPE_LOGON_SUCCESS 2 //登录成功
#define TYPE_CHAT_PRIVATE 3  //私聊消息
/***********************end****************************/


/*********************错误码/错误信息***************************/

#define ERROR_CODE_CONNECT  0x0 //连接服务器失败
#define ERROR_CODE_LOGON_USER    0x01    //用户名错误
#define ERROR_CODE_LOGON_PASSWORD   0X02   //密码错误


#define ERROR_MESSAGE_LOGON_USER "Login fail,username/id error"
#define ERROR_MESSAGE_LOGON_PASSWORD    "Login fail,password error"
#define ERROR_MESSAGE_CONNECT   "Connect to server fail"


/*********nodename*******/
#define NODE_TYPE "type"
#define NODE_ID "id"
#define NODE_USERNAME "username"
#define NODE_PASSWORD "password"
#define NODE_ICON "icon"

#endif // APPLY_PROTOCL_H
