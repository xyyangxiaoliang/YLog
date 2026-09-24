# YLog

## 关于YLog

### 基于C语言的日志库。

## YLog 的优势

1. CMake编译，支持**Windows/Linux**；
2. 支持**控制台带颜色打印**；
3. 支持**日志轮转**；
4. 支持**日志级别过滤**；
5. 宽松的开源协议（**Apache 2.0**）；
6. YLog库**单文件**代码，便于集成；
7. **统一日志配置**，只需配置一个结构体，字段含义参考数据结构定义的注释；

## YLog 日志打印格式预览

```text
[YLog][2026/09/24 10:06:49][0-TRACE][YLog.c::ylog_main:72]-->test ylog, i :9
[YLog][2026/09/24 10:06:49][1-DEBUG][YLog.c::ylog_main:73]-->test ylog, i :9
[YLog][2026/09/24 10:06:49][2-INFO][YLog.c::ylog_main:74]-->test ylog, i :9
[YLog][2026/09/24 10:06:49][3-WARNING][YLog.c::ylog_main:75]-->test ylog, i :9
[YLog][2026/09/24 10:06:49][4-ERROR][YLog.c::ylog_main:76]-->test ylog, i :9
[YLog][2026/09/24 10:06:49][5-CRITICAL][YLog.c::ylog_main:77]-->test ylog, i :9
```

## 怎么克隆仓库

```shell
# 从github克隆
git clone https://github.com/xyyangxiaoliang/YLog.git

```

## 怎么编译

```text

Windows 系统下
    使用CLion或者Visual Studio 2022，打开CMake直接编译；

Linux Ubuntu 系统下
    1. 克隆仓库代码；
    2. 在YLog目录下创建build目录；
    3. 进入编译目录，执行命令 ：cd build
    4. 使用cmake构建项目代码，执行命令 ：cmake ../
    5. 使用make编译项目代码，执行命令：make -j6
    6. 生成可执行文件：YLog
    7. 运行后，默认执行测试函数YLog_test_example();

```

## 怎么应用到你的项目中

1. 直接集成源码；（单文件项目，易于集成）
2. 编译成动态库/静态库；

### 示例代码

```c
// 日志测试示例函数
int ylog_test_example(int argc, char** argv)
{
    printf("%s\n", __FUNCTION__);

    // YLog 配置日志打印功能
    static YLog_Config ylog_config;
    sprintf(ylog_config.project_name, "%s", "YLog");

    ylog_config.is_print_on_console = 1;
    ylog_config.is_only_print_on_console = 0;
    ylog_config.is_print_on_console_with_color = 1;

    ylog_config.min_log_level = YLog_Trace;
    ylog_config.one_line_log_string_max_len = 1024;

    // YLog 初始化
    ylog_init(&ylog_config);

    // 打印日志
    for (int i = 0; i < 2 * 1; i++)
    {
        YLOG_TRACE("test ylog, i :%d", i);
        YLOG_DEBUG("test ylog, i :%d", i);
        YLOG_INFO("test ylog, i :%d", i);
        YLOG_WARNING("test ylog, i :%d", i);
        YLOG_ERROR("test ylog, i :%d", i);
        YLOG_CRITICAL("test ylog, i :%d", i);

        YLOG_INFO("");
    }

    // YLog 退出
    ylog_exit();

    return 0;
}
```

## License 说明

### Apache 2.0