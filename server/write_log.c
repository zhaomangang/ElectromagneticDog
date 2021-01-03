/**
 * \copyright Copyright (c) 1999-2020,西安交大捷普网络科技有限公司
 * 
 * \file write_log.c
 * \author xiaoke
 * \version 0.1
 * \date 2020-11-23
 * 
 * \brief 日志调试接口实现
 */
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "write_log.h"


static FILE *logf = NULL;                           /** 日志文件描述符 */
static debug_level_em debug_level = PROXY_MAX;    /** 日志文件级别，默认warning */

#define STD_ERR    0x2  //stderr print

static const char *error_strs[PROXY_MAX] = {
    "[Error]",
    "[Warning]",
    "[Info]",
    "[Debug]"
};

void debug_level_set(debug_level_em level)
{
    debug_level = level;
}

void debug_output(debug_level_em type, const char *file, int lineno, const char *fmt, ...)
{
    if (type > debug_level)
        return;

    if (!fmt)
        return;

    if (!file)
        file = "no_src.c";

    char msg[MAX_DEBUG_MSG_SIZE] = {0};
    snprintf(msg, MAX_DEBUG_MSG_SIZE, "%8s[%15s:%5d]>>>> ", error_strs[type], file, lineno);
    int idx = strlen(msg);

    va_list ap;
    va_start(ap, fmt);
    vsnprintf(&msg[idx], MAX_DEBUG_MSG_SIZE - idx, fmt, ap);
    va_end(ap);

    if (logf != NULL) 
    {
        /** TODO:写入调试文件，控制文件大小 */
    }
    else 
    {
        write(STD_ERR, msg, strlen(msg));
    }
    return ;
}

