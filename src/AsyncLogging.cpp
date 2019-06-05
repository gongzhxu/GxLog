#include "AsyncLogging.h"

#include <chrono>

#include "LogFile.h"
#include "ConfigParser.h"
#include "Buffer.h"

#define MAX_LOG_BUF_SIZE 1024000

AsyncLogging::AsyncLogging(const char * fileName):
    running_(true)
{

    loadConfig(fileName);
    //start the thread
    thread_ = std::thread(std::bind(&AsyncLogging::threadFunc, this));
}

AsyncLogging::~AsyncLogging()
{
    //stop the running thread
    running_ = false;
    cond_.notify_one();
    thread_.join();
}

void AsyncLogging::loadConfig(const char * fileName)
{
    ConfigParser cfg(fileName);
    flushInterval_ = cfg["log"]["FlushInterval"].asInt32(DEF_FLUSHINTERVAL);
    if(flushInterval_ < DEF_FLUSHINTERVAL)
    {
        flushInterval_ = DEF_FLUSHINTERVAL;
    }

    level_ = cfg["log"]["Level"].asInt32(Logger::INFO);
    print_ = cfg["log"]["Print"].asInt32(true);


    logFolder_ = cfg["log"]["Folder"].asString("log");
    baseName_ = cfg["log"]["Name"].asString("default");
    rollSize_ = cfg["log"]["RollSize"].asInt32(DEF_ROLLSIZE);
    autoRm_ = cfg["log"]["AutoRm"].asInt32(DEF_AUTORM*DAYILY_SECONDS);//use second
    if(autoRm_ < 0)
    {
        autoRm_ = DEF_AUTORM*DAYILY_SECONDS;
    }
}

void AsyncLogging::append(const char * module, LoggerPtr && logger)
{
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if(module == nullptr || strcmp(module, "") == 0)
        {
            loggers_[baseName_].emplace_back(std::move(logger));
        }
        else
        {
            loggers_[module].emplace_back(std::move(logger));
        }
    }

    cond_.notify_one();
}

void AsyncLogging::threadFunc()
{
    while(true)
    {
        LoggerMap loggers;

        {
            std::unique_lock<std::mutex> lock(mutex_);

            while(loggers_.empty())
            {
                if(!running_)
                {
                    for(auto it = logFiles_.begin(); it != logFiles_.end(); ++it)
                    {
                        if(it->second)
                        {
                            it->second->append("log thread exit!!!\n");
                        }
                    }
                    return;
                }

                for(auto it = logFiles_.begin(); it != logFiles_.end(); ++it)
                {
                    if(it->second)
                    {
                        it->second->append(NULL, 0);
                    }
                }
                cond_.wait_for(lock, std::chrono::seconds(flushInterval_));
            }

            loggers.swap(loggers_);
        }


        Buffer outputBuf; // the file log buffer
        Buffer printBuf; // the screen print buffer
        std::string data;

        for(auto it = loggers.begin(); it != loggers.end(); ++it)
        {
            std::unique_ptr<LogFile> & logFile = logFiles_[it->first];
            if(logFile == nullptr)
            {
                logFile.reset(new LogFile());
                logFile->setLogFolder(logFolder_);
                logFile->setBaseName(it->first);
                logFile->setRollSize(rollSize_);
                logFile->setFlushInterval(flushInterval_);
                logFile->setAutoRm(autoRm_);
            }

            for(auto it1 = it->second.begin(); it1 != it->second.end();)
            {
                LoggerPtr pLogger = *(it1++);
                pLogger->format(data);

                outputBuf.append(data.c_str(), data.size());
                if((print_ && pLogger->level() == Logger::INFO) || pLogger->raw())
                {
                    printBuf.append(data.c_str(), data.size());
                }

                //write the log buffer to destination
                if(outputBuf.size() > MAX_LOG_BUF_SIZE || it1 == it->second.end())
                {
                    logFile->append(outputBuf.data(), outputBuf.size());
                    outputBuf.clear();
                }

                if(printBuf.size() > MAX_LOG_BUF_SIZE || it1 == it->second.end())
                {
                    ::fwrite(printBuf.data(), sizeof(char), printBuf.size(), stdout);
                    printBuf.clear();
                }
            }
        }
    }
}
