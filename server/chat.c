#include "chat.h"
#include "cJSON.h"
#include "write_log.h"
void demo_json(char *data)
{
    //从data中解析json结构
    cJSON *json = cJSON_Parse(data);
    cJSON *node = NULL;

    //cJSON_GetObjectItem 根据key来查找json节点，如果有返回非空
    node = cJSON_GetObjectItem(json,"id");
    if (NULL == node)
    {
        write_log(LOG_WARNING,"json node id is null");
    }
    else
    {
        if (node->type == cJSON_Number)
        {
            write_log(LOG_INFO,"id:%d",node->valueint);
        }
    }
}

