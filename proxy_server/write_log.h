/**
 * \filename write_log.h
 * \author mason
 * \time 2020-1-10
 * \describe 打印调试信息相关接口
 */

#ifndef __WRITE_LOG_H__
#define __WRITE_LOG_H__
#include <stdio.h>

#define     MAX_DEBUG_MSG_SIZE      8096    /** 单条调试信息的最大长度 */

#define     MAX_TIME_STR    64

typedef enum
{
    LOG_ERROR = 0,
    LOG_WARNING,
    LOG_INFO,
    LOG_DEBUG,
    LOG_MAX
} debug_level_em;

/**
 * \brief 设置日志级别
 * 
 * \param [in]	level 日志级别
 */
void debug_level_set(debug_level_em level);

void debug_output(debug_level_em type, const char *file, int lineno, const char *fmt, ...);

/**
* @调试日志
*/
#undef LOGDEBUG
#define LOGDEBUG(level, fmt, ...) do { \
            debug_output(level,  __FILE__, __LINE__, fmt "\n", ##__VA_ARGS__); \
            fflush(stdout); \
        } while(0)

#ifndef UNLOGDEBUG
#define write_log  LOGDEBUG
#else
#define write_log
#endif



#endif
