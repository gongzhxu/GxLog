#ifndef _LOG_UTIL_H_
#define _LOG_UTIL_H_

namespace GxLog
{
    void log_raw(const char * fmt, ...);
    void log_trace(const char * file, int line, const char * func, const char * fmt, ...);
    void log_debug(const char * file, int line, const char * func, const char * fmt, ...);
    void log_info(const char * file, int line, const char * func, const char * fmt, ...);
    void log_warn(const char * file, int line, const char * func, const char * fmt, ...);
    void log_error(const char * file, int line, const char * func, const char * fmt, ...);
    void log_fatal(const char * file, int line, const char * func, const char * fmt, ...);
}

#if 1

#define LOG_RAW(fmt, args...)   GxLog::log_raw(fmt, ##args);
#define LOG_TRACE(fmt, args...) GxLog::log_trace(__FILE__, __LINE__, __FUNCTION__, fmt, ##args);
#define LOG_DEBUG(fmt, args...) GxLog::log_debug(__FILE__, __LINE__, __FUNCTION__, fmt, ##args);
#define LOG_INFO(fmt, args...)  GxLog::log_info(__FILE__, __LINE__, __FUNCTION__, fmt, ##args);
#define LOG_WARN(fmt, args...)  GxLog::log_warn(__FILE__, __LINE__, __FUNCTION__, fmt, ##args);
#define LOG_ERROR(fmt, args...) GxLog::log_error(__FILE__, __LINE__, __FUNCTION__, fmt, ##args);
#define LOG_FATAL(fmt, args...) GxLog::log_fatal(__FILE__, __LINE__, __FUNCTION__, fmt, ##args);

#else

#define LOG_TRACE(fmt, args...)
#define LOG_DEBUG(fmt, args...)
#define LOG_INFO(fmt, args...)
#define LOG_WARN(fmt, args...)
#define LOG_ERROR(fmt, args...)
#define LOG_FATAL(fmt, args...)

#endif // 0

#endif // _LOG_UTIL_H_

