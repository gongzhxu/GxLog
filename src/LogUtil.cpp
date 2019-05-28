#include "LogUtil.h"

#include <stdarg.h>

#include "AsyncLogging.h"

static AsyncLogging log("log.conf");

void GxLog::log_raw(const char * fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);
    log.append(MakeLoggerPtr(fmt, arglist));
    va_end(arglist);
}

void GxLog::log_trace(const char * file, int line, const char * func, const char * fmt, ...)
{
    if(log.getLogLevel() <= Logger::TRACE)
    {
        va_list arglist;
        va_start(arglist, fmt);
        log.append(MakeLoggerPtr(Logger::TRACE, file, line, func, fmt, arglist));
        va_end(arglist);
    }
}

void GxLog::log_debug(const char * file, int line, const char * func, const char * fmt, ...)
{
    if(log.getLogLevel() <= Logger::DEBUG)
    {
        va_list arglist;
        va_start(arglist, fmt);
        log.append(MakeLoggerPtr(Logger::DEBUG, file, line, func, fmt, arglist));
        va_end(arglist);
    }
}

void GxLog::log_info(const char * file, int line, const char * func, const char * fmt, ...)
{
    if(log.getLogLevel() <= Logger::INFO)
    {
        va_list arglist;
        va_start(arglist, fmt);
        log.append(MakeLoggerPtr(Logger::INFO, file, line, func, fmt, arglist));
        va_end(arglist);
    }
}

void GxLog::log_warn(const char * file, int line, const char * func, const char * fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);
    log.append(MakeLoggerPtr(Logger::WARN, file, line, func, fmt, arglist));
    va_end(arglist);
}

void GxLog::log_error(const char * file, int line, const char * func, const char * fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);
    log.append(MakeLoggerPtr(Logger::ERROR, file, line, func, fmt, arglist));
    va_end(arglist);
}

void GxLog::log_fatal(const char * file, int line, const char * func, const char * fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);
    log.append(MakeLoggerPtr(Logger::FATAL, file, line, func, fmt, arglist));
    va_end(arglist);
}

