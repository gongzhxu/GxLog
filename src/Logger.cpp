#include "Logger.h"

#include <sstream>
#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>
#include "CurrentThread.h"
#include "AsyncLogging.h"
#include "StringOps.h"

static __thread char ttime_[32];
static __thread time_t t_lastSecond;

const char * LogLevelName[Logger::NUM_LEVELS] =
{
    "TRACE",
    "DEBUG",
    "INFO ",
    "WARN ",
    "ERROR",
    "FATAL",
};

Logger::Logger(const std::string & content):
    file_(""),
    content_(content),
    raw_(true)
{
}

Logger::Logger(LogLevel level, const char * file, int line, const char * func, const std::string & content):
    level_(level),
    tid_(CurrentThread::tid()),
    file_(file),
    line_(line),
    func_(func),
    content_(content),
    raw_(false)
{
    formatTime();
}

Logger::~Logger()
{
}

void Logger::formatTime()
{
    TimeStamp ts(TimeStamp::now());

    time_t seconds = ts.seconds() + 8*3600;
    int microseconds = ts.microseconds()%(1000*1000);
    if(seconds != t_lastSecond)
    {
        t_lastSecond = seconds;
        struct tm tmtime_;
        gmtime_r(&seconds, &tmtime_);
        snprintf(ttime_, sizeof(ttime_), "%4d%02d%02d %02d:%02d:%02d",
                tmtime_.tm_year + 1900, tmtime_.tm_mon + 1, tmtime_.tm_mday,
                tmtime_.tm_hour, tmtime_.tm_min, tmtime_.tm_sec);
    }

    snprintf(time_, sizeof(time_), "%s.%06d", ttime_, microseconds);
}

size_t Logger::format(char * data, size_t len)
{
    if(raw_)
    {
        snprintf(data, len, "%s\n", content_.c_str());
    }
    else
    {
        snprintf(data, len, "%s [%s][%d] - %s -- <%s,%d,%s>\n",
                    time_,
                    LogLevelName[level_],
                    tid_,
                    content_.c_str(),
                    file_.data(),
                    line_,
                    func_);
    }

    return strlen(data);
}

void Logger::format(std::string & data)
{
    if(raw_)
    {
        GxLog::sprintfex(data, "%s\n", content_.c_str());
    }
    else
    {
        GxLog::sprintfex(data, "%s [%s][%d] - %s -- <%s,%d,%s>\n",
                    time_,
                    LogLevelName[level_],
                    tid_,
                    content_.c_str(),
                    file_.data(),
                    line_,
                    func_);
    }
}

size_t Logger::format(FILE * fp)
{
    if(!fp)
    {
        return 0;
    }

    if(raw_)
    {
        return fprintf(fp, "%s\n", content_.c_str());
    }
    else
    {
        return fprintf(fp, "%s [%s][%d] - %s -- <%s,%d,%s>\n",
                    time_,
                    LogLevelName[level_],
                    tid_,
                    content_.c_str(),
                    file_.data(),
                    line_,
                    func_);
    }
}
