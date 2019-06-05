#ifndef _LOG_UTIL_H_
#define _LOG_UTIL_H_

#include <sstream>

namespace GxLog
{
enum LogLevel
{
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
    NUM_LEVELS
};

void log_raw(const char * module, const char * fmt, ...);
void log_level(const char * module, LogLevel level, const char * file, int line, const char * func, const char * fmt, ...);

class LogStream:public std::stringstream
{
public:
    LogStream(const char * module);
    LogStream(const char * module, LogLevel level, const char * file, int line, const char * func);
    ~LogStream();
private:
    const char * module_;
    LogLevel level_;
    const char * file_;
    int line_;
    const char * func_;
    bool raw_;
};

}

#define LOG_RAW(module, fmt, args...)   GxLog::log_raw(module, fmt, ##args);
#define LOG_TRACE(module, fmt, args...) GxLog::log_level(module, GxLog::LogLevel::TRACE, __FILE__, __LINE__, __FUNCTION__, fmt, ##args);
#define LOG_DEBUG(module, fmt, args...) GxLog::log_level(module, GxLog::LogLevel::DEBUG, __FILE__, __LINE__, __FUNCTION__, fmt, ##args);
#define LOG_INFO(module, fmt, args...)  GxLog::log_level(module, GxLog::LogLevel::INFO, __FILE__, __LINE__, __FUNCTION__, fmt, ##args);
#define LOG_WARN(module, fmt, args...)  GxLog::log_level(module, GxLog::LogLevel::WARN, __FILE__, __LINE__, __FUNCTION__, fmt, ##args);
#define LOG_ERROR(module, fmt, args...) GxLog::log_level(module, GxLog::LogLevel::ERROR, __FILE__, __LINE__, __FUNCTION__, fmt, ##args);
#define LOG_FATAL(module, fmt, args...) GxLog::log_level(module,  GxLog::LogLevel::FATAL, __FILE__, __LINE__, __FUNCTION__, fmt, ##args);

#define SLOG_RAW(module) GxLog::LogStream(module)
#define SLOG_TRACE(module) GxLog::LogStream(module, GxLog::LogLevel::TRACE, __FILE__, __LINE__, __FUNCTION__)
#define SLOG_DEBUG(module) GxLog::LogStream(module, GxLog::LogLevel::DEBUG, __FILE__, __LINE__, __FUNCTION__)
#define SLOG_INFO(module) GxLog::LogStream(module, GxLog::LogLevel::INFO, __FILE__, __LINE__, __FUNCTION__)
#define SLOG_WARN(module) GxLog::LogStream(module, GxLog::LogLevel::WARN, __FILE__, __LINE__, __FUNCTION__)
#define SLOG_ERROR(module) GxLog::LogStream(module, GxLog::LogLevel::ERROR, __FILE__, __LINE__, __FUNCTION__)
#define SLOG_FATAL(module) GxLog::LogStream(module, GxLog::LogLevel::FATAL, __FILE__, __LINE__, __FUNCTION__)

#endif // _LOG_UTIL_H_

