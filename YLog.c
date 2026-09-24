//
// Created by yxl on 2026/9/23.
//

#include "YLog.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>


////////// YLog 日志相关静态全局变量 //////////
static YLog_Config s_ylog_config;
static char* s_one_log_string_buffer = NULL;

static FILE* s_fp_ylog_file = NULL;
////////// YLog 日志相关静态全局变量 //////////


////////// 静态工具函数声明 //////////
static long long get_current_time_string(char time_string[64], const int is_split);
////////// 静态工具函数声明 //////////


////////// 静态工具函数实现 //////////
static long long get_current_time_string(char time_string[64], const int is_split)
{
    time_t current_second;
    time(&current_second);

    struct tm* p_time = NULL;
    p_time = localtime(&current_second);
    if (!p_time)
        return 0;

    if (is_split)
    {
        sprintf(time_string, "%04d/%02d/%02d %02d:%02d:%02d",
            p_time->tm_year + 1900, p_time->tm_mon + 1, p_time->tm_mday,
            p_time->tm_hour, p_time->tm_min, p_time->tm_sec);
    }
    else
    {
        sprintf(time_string, "%04d%02d%02d%02d%02d%02d",
            p_time->tm_year + 1900, p_time->tm_mon + 1, p_time->tm_mday,
            p_time->tm_hour, p_time->tm_min, p_time->tm_sec);
    }

    return current_second;
}

////////// 静态工具函数实现 //////////

int ylog_main(int argc, char** argv)
{
    printf("%s\n", __FUNCTION__);

    // YLog 初始化
    static YLog_Config ylog_config;
    sprintf(ylog_config.project_name, "%s", "YLog");
    ylog_config.is_only_print_on_console = 0;
    ylog_config.min_log_level = YLog_Trace;
    ylog_config.one_line_log_string_max_len = 1024;

    ylog_init(&ylog_config);

    // 打印日志
    for (int i = 0; i < 10 * 1; i++)
    {
        YLOG_TRACE("test ylog, i :%d\n", i);
        YLOG_DEBUG("test ylog, i :%d\n", i);
        YLOG_INFO("test ylog, i :%d\n", i);
        YLOG_WARNING("test ylog, i :%d\n", i);
        YLOG_ERROR("test ylog, i :%d\n", i);
        YLOG_CRITICAL("test ylog, i :%d\n", i);

        YLOG_INFO("\n", 0);
    }

    // YLog 退出
    ylog_exit();

    return 0;
}

// 日志初始化（必须执行）
int ylog_init(const YLog_Config* ylog_config)
{
    s_ylog_config = *ylog_config;

    sprintf(s_ylog_config.project_name, "%s", ylog_config->project_name);

    s_one_log_string_buffer = (char*)malloc(ylog_config->one_line_log_string_max_len);

    char ylog_file_path[4096] = { 0 };
    sprintf(ylog_file_path, "./YLog_%d.log", 1);
    s_fp_ylog_file = fopen(ylog_file_path, "a+");
    if (s_fp_ylog_file == NULL)
        return -1;

    char time_string[64] = { 0 };
    get_current_time_string(time_string, 1);

    char init_string[256] = { 0 };
    sprintf(init_string, "\ntime :%s, YLog init path :%s, YLog init successfully.\n\n", time_string, ylog_file_path);
    printf("%s", init_string);
    fprintf(s_fp_ylog_file, "%s", init_string);

    return 0;
}

// 日志退出（必须执行）
int ylog_exit()
{
    if (s_one_log_string_buffer != NULL)
    {
        free(s_one_log_string_buffer);
        s_one_log_string_buffer = NULL;
    }

    if (s_fp_ylog_file != NULL)
    {
        fclose(s_fp_ylog_file);

        free(s_one_log_string_buffer);
        s_one_log_string_buffer = NULL;
    }

    return 0;
}

// 追加一条日志到文件
int ylog_push(const int level, const char* filepath, const char* functionName, const int line, const char* format, ...)
{
    if (s_one_log_string_buffer == NULL)
        return -1;

    if (level < YLog_Trace || level > YLog_Critical)
        return -2;

    if (level < s_ylog_config.min_log_level)
        return 0;

    // 清除一行日志的缓存
    memset(s_one_log_string_buffer, 0, s_ylog_config.one_line_log_string_max_len);

    // 获取当前时间戳
    char current_time[64] = { 0 };
    get_current_time_string(current_time, 1);

    // 计算文件名称
    char* filename = strrchr(filepath, '/') + 1;

    // 拼接YLog日志格式
    int log_string_len = 0;
    log_string_len = sprintf(s_one_log_string_buffer, "[%s][%s][%d-%s][%s::%s:%d]-->",
                        s_ylog_config.project_name, current_time,
                        level, g_ylog_level_string[level],
                        filename, functionName, line);

    // 拼接YLog日志内容
    va_list argument_list;
    va_start(argument_list, format);
    log_string_len = vsprintf(s_one_log_string_buffer + log_string_len, format, argument_list) + log_string_len;
    va_end(argument_list);

    // 字符串数组末尾追加字符串结束符
    s_one_log_string_buffer[log_string_len] = '\0';

    // 将日志输出到控制台
    if (s_ylog_config.is_only_print_on_console)
    {
        printf("%s", s_one_log_string_buffer);
        return 0;
    }

    // 将日志输出到日志文件
    fprintf(s_fp_ylog_file, "%s", s_one_log_string_buffer);
    fflush(s_fp_ylog_file);

    return 0;
}