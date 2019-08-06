#ifndef _ASYNC_LOGGING_H_
#define _ASYNC_LOGGING_H_

#include <string>
#include <list>
#include <thread>
#include <mutex>
#include <memory>
#include <map>
#include <condition_variable>

#include "Logger.h"
class LogFile;

class AsyncLogging
{
public:
    typedef std::map<std::string, std::list<LoggerPtr>> LoggerMap;
    typedef std::map<std::string, std::unique_ptr<LogFile>> LogFileMap;

    AsyncLogging(const char * fileName);
    ~AsyncLogging();
public:
    void loadConfig(const char * fileName);
    void append(const char * module, LoggerPtr && logger);
    int getLogLevel() const { return level_; }

private:
    void threadFunc();

private:
    int32_t         flushInterval_;
    int32_t         level_; // log level
    bool            print_; // print or not
    std::string     logFolder_;
    std::string     baseName_;
    int64_t         rollSize_;
    int32_t         autoRm_;

    bool            running_; // just a flag indicate the thread is running

    std::thread thread_;
    std::mutex mutex_;
    std::condition_variable cond_;

    LoggerMap         loggers_; // logger list
    LogFileMap        logFiles_;
};

#endif // _ASYNC_LOGGING_H
