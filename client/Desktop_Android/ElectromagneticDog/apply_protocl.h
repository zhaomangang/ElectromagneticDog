/**************************************************************
 * filename: apply_protocl.h
 * time: 2020.12.31 22:38
 * author: mason
 * email: zhaomangang@qq.com
 * describe: Definition of the application layer protocol.
 * ************************************************************/

#ifndef APPLY_PROTOCL_H
#define APPLY_PROTOCL_H


#define USER_NAME_MAX_LEN   256   //the max len of username
#define ENCRYPT_PASSWORD_MAX_LEN    256   //加密后密码最大长度
#define ICON_MAX_LEN    256 //头像路径最大长度
#define CHAT_TEXT_LEN   2048    //聊天消息最大长度
/********************消息类型******************************/


#define TYPE_ERROR  0X00   //错误
#define TYPE_LOGIN 0X01  //登录
#define TYPE_LOGON_SUCCESS 0X02 //登录成功
#define TYPE_CHAT_PRIVATE 0X03  //私聊消息
/***********************end****************************/


/*********************错误码/错误信息***************************/

#define ERROR_CODE_CONNECT  0x0 //连接服务器失败
#define ERROR_CODE_LOGON_USER    0x01    //用户名错误
#define ERROR_CODE_LOGON_PASSWORD   0X02   //密码错误


#define ERROR_MESSAGE_LOGON_USER "Login fail,username/id error"
#define ERROR_MESSAGE_LOGON_PASSWORD    "Login fail,password error"
#define ERROR_MESSAGE_CONNECT   "Connect to server fail"

/**********************end*************************/
//消息头
typedef struct _MESSAGE_ {
    unsigned char type; //消息类型
    unsigned int send;  //发送方id
    unsigned int recv;  //接收方id
    void* message_data;  //真实消息数据，由type决定
    unsigned int message_data_len;  //消息数据长度
    unsigned int message_len;   //消息总长
}MESSAGE;


//登录消息
/*
 * 初步构想，密码加密为des，用时间作为原始密钥，并根据用户设置的方式计算后对明文密码进行des加密，将des结果进行base64
 * */

typedef struct _LOGON_ {
    unsigned int id;    //id
    char username[USER_NAME_MAX_LEN];   //用户名
    char encrypt_password[ENCRYPT_PASSWORD_MAX_LEN];    //加密后密码
}LOGON;


//登录成功消息
typedef struct _LOGON_SUCCESS_{
    unsigned int id;    //id
    char username[USER_NAME_MAX_LEN];   //用户名
    char icon[ICON_MAX_LEN];    //头像
}LOGON_SUCCESS;

//错误消息

typedef struct _ERROR_ {
    unsigned int error_code;    //错误码
}ERROR;


//私聊/群聊消息
typedef struct _CHAT_TEXT_ {
    char data[CHAT_TEXT_LEN];   //聊天消息内容
}CHAT_TEXT;



#endif // APPLY_PROTOCL_H
