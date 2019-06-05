#include "LogUtil.h"

#include <stdarg.h>

#include "StringOps.h"
#include "AsyncLogging.h"

using namespace GxLog;

static AsyncLogging log("log.conf");

void GxLog::log_raw(const char * module, const char * fmt, ...)
{
    std::string content;
    va_list arglist;
    va_start(arglist, fmt);
    GxLog::vsprintfex(content, fmt, arglist);
    va_end(arglist);

    log.append(module, MakeLoggerPtr(content));
}

void GxLog::log_level(const char * module, GxLog::LogLevel level, const char * file, int line, const char * func, const char * fmt, ...)
{
    if(level <= GxLog::LogLevel::INFO && level < log.getLogLevel())
    {
        return;
    }

    std::string content;
    va_list arglist;
    va_start(arglist, fmt);
    GxLog::vsprintfex(content, fmt, arglist);
    va_end(arglist);

    log.append(module, MakeLoggerPtr((Logger::LogLevel)level, file, line, func, content));
}

LogStream::LogStream(const char * module):module_(module), raw_(true)
{
}

LogStream::LogStream(const char * module, LogLevel level, const char * file, int line, const char * func):
    module_(module), level_(level), file_(file), line_(line), func_(func), raw_(false)
{
}

LogStream::~LogStream()
{
    if(raw_)
    {
        log.append(module_, MakeLoggerPtr(str()));
    }
    else
    {
        if(level_ <= GxLog::LogLevel::INFO && level_ < log.getLogLevel())
        {
            return;
        }

        log.append(module_, MakeLoggerPtr((Logger::LogLevel)level_, file_, line_, func_, str()));
    }
}
