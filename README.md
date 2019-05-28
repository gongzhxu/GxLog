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

3.例子代码

#include "LogUtil.h"  
int main(int argc, char * argv[])  
{  
        LOG_RAW("this is log raw");  
        LOG_TRACE("this is log trace");  
        LOG_DEBUG("this is log debug");  
        LOG_INFO("this is log info");  
        LOG_WARN("this is log warn");  
        LOG_ERROR("this is log error");  
        LOG_FATAL("this is log fatal");   
}

输出：
this is log raw  
20190528 19:42:45.081697 [INFO ][39898] - this is log info -- <main.cpp,8,main>  
20190528 19:42:45.081717 [WARN ][39898] - this is log warn -- <main.cpp,9,main>  
20190528 19:42:45.081718 [ERROR][39898] - this is log error -- <main.cpp,10,main>  
20190528 19:42:45.081719 [FATAL][39898] - this is log fatal -- <main.cpp,11,main>  
log thread exit!!! 
  
