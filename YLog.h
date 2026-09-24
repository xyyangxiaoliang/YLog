//
// Created by yxl on 2026/9/23.
//

#ifndef _YLOG_H_
#define _YLOG_H_

#ifdef __cplusplus
extern "C" {
#endif

////////// YLog 日志相关数据结构定义 //////////

// YLog 日志级别定义
typedef enum YLog_Level
{
    YLog_Trace = 0,
    YLog_Debug,
    YLog_Info,
    YLog_Warning,
    YLog_Error,
    YLog_Critical,
}YLog_Level;

extern const char g_ylog_level_string[][16];

// YLog 配置
typedef struct YLog_Config
{
    char project_name[64];                          // 使用该日志的项目名称

    int is_only_print_on_console;                   // 是否只在控制台打印日志
    int is_print_on_console_with_color;             // 在控制台打印，是否带颜色；前提条件：is_only_print_on_console=1；

    int min_log_level;                              // 最小日志级别；小于该日志级别的不打印；
    int one_line_log_string_max_len;                // 一行日志最大字符串长度；
}YLog_Config;

////////// YLog 日志相关数据结构定义 //////////


// 日志测试函数
int ylog_main(int argc, char** argv);

// 日志初始化（必须执行）
int ylog_init(const YLog_Config* ylog_config);

// 日志退出（必须执行）
int ylog_exit();

// 追加一条日志到文件
int ylog_push(const int level, const char* filepath, const char* functionName, const int line, const char* format, ...);


// 是否启用YLOG日志
#define ENABLE_YLOG

// YLOG日志级别宏定义
#ifdef ENABLE_YLOG

#define YLOG_TRACE(format, ...) ylog_push(YLog_Trace, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#define YLOG_DEBUG(format, ...) ylog_push(YLog_Debug, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#define YLOG_INFO(format, ...) ylog_push(YLog_Info, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#define YLOG_WARNING(format, ...) ylog_push(YLog_Warning, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#define YLOG_ERROR(format, ...) ylog_push(YLog_Error, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#define YLOG_CRITICAL(format, ...) ylog_push(YLog_Critical, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)

#else // ENABLE_YLOG

#define YLOG_TRACE(format, ...)
#define YLOG_DEBUG(format, ...)
#define YLOG_INFO(format, ...)
#define YLOG_WARNING(format, ...)
#define YLOG_ERROR(format, ...)
#define YLOG_CRITICAL(format, ...)

#endif // ENABLE_YLOG


#ifdef __cplusplus
}
#endif

#endif //_YLOG_H_
//


// 代码解释
/*
宏中的 ##__VA_ARGS__‌：
    在 YLOG_TRACE(format, ...) 等宏中，建议使用 ##__VA_ARGS__ 而不是 __VA_ARGS__。
    ‌原因‌：如果调用 YLOG_INFO("Hello") 而没有额外的参数，标准的 __VA_ARGS__ 可能会留下一个多余的逗号 ,
    ，导致某些编译器报错。## 运算符会在可变参数为空时删除前面的逗号，兼容性更好（MSVC 和 GCC/Clang 均支持）


*/
