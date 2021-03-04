/*
 *filename:message_type.h
 *time:2020/1/16
 *author:MasonZhao
 *email:zhaomangang@qq.com
 */

#ifndef _MESSAGE_TYPE_H_
#define _MESSAGE_TYPE_H_



#define MAX_LEN_PASSWORD 256
#define MAX_LEN_USERNAME 128
#define MAX_LEN_ICON     256



#define STR_TYPE "type"
#define STR_ID  "id"
#define STR_PASSWORD "password"
#define STR_USERNAME "username"
#define STR_ICON    "icon"
#define STR_ERROR_CODE   "error_code"
#define STR_ERROR_MSG   "error_msg"
#define STR_FRIEND_ID "friend_id"
#define STR_FRIEND_NAME "friend_name"
#define STR_REMARK  "remark"
#define STR_NUM "num"
#define STR_RECV_ID "recv_id"
#define STR_SEND_ID "send_id"
#define STR_TIME "time"
#define STR_MESSAGE_DATA "data"
#define STR_SORT_TEXT "sort_text"

#define MESSAGE_LOGON_ERROR -1    //登录错误消息
#define MESSAGE_LOGON 1 //登录请求
#define MESSAGE_USERINFO   2   //用户信息
#define MESSAGE_FRIEND_LIST 3   //好友列表请求
#define MESSAGE_GROUP_LIST  4   //群组列表请求
#define MESSAGE_FRIEND_LIST_RESPONSE 5  //好友列表响应
#define MESSAGE_CHAT_DATE   6       //聊天消息



#define MESSAGE_MUSIC_SORT  10  //搜索音乐

#endif
