# GxLog

1.linux实现高效的异步线程日志库

2.配置文件log.conf  
[log]  
Level=2  
Print=1  
Folder=log  
Name=default  
RollSize=1000000  
AutoRm=15  

3.例子代码: main.cpp

#include "LogUtil.h"  

int main(int argc, char * argv[])  
{
        LOG_RAW("Raw", "this is log raw");  
        LOG_TRACE("Trace", "this is log trace");  
        LOG_DEBUG("Debug", "this is log debug");  
        LOG_INFO("Info", "this is log info");  
        LOG_WARN("Warn", "this is log warn");  
        LOG_ERROR("Error", "this is log error");  
        LOG_FATAL("Fatal", "this is log fatal");    
        SLOG_RAW("Raw") << "this is log raw " << 1;  
        SLOG_RAW("Raw") << "this is log raw " << 456;  
        SLOG_TRACE("Trace") << "this is log trace " << 2;  
        SLOG_DEBUG("Debug") << "this is log debug " << 3;  
        SLOG_INFO("Info") << "this is log info " << 4;  
        SLOG_INFO("Info") << "this is log info " << 123;  
        SLOG_WARN("Warn") << "this is log warn " << 5;  
        SLOG_ERROR("Error") << "this is log error" << 6;  
        SLOG_FATAL("Fatal") << "this is log fatal" << 7;  
}  

gcc main.cpp -std=c++11 -I./GxLog/src -L./GxLog/src -lGxLog -lstdc++ -lpthread -o main

输出：
this is log raw  
20190605 10:36:46.595130 [INFO ][46007] - this is log info -- <main.cpp,8,main>  
20190605 10:36:46.595259 [INFO ][46007] - this is log info 4 -- <main.cpp,17,main>  
20190605 10:36:46.595261 [INFO ][46007] - this is log info 123 -- <main.cpp,18,main>  
this is log raw 1  
this is log raw 456   
  
