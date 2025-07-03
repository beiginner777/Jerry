#ifndef LOH_HPP
#define LOH_HPP
// #define MUDUO_DEBUG 如果没有定义MUDUO_DEBUG,那么会忽略 LOG_DEBUG 信息
#include <iostream>
#include <string>
#include <chrono>
#include "noncopyable.hpp" 

#define BUFFER_SIZE 1024

enum LogLevel
{
    DEBUG, // 调试信息
    INFO, // 普通信息
    WARN, // 警告信息
    ERROR, // 错误信息
    FATAL, // 致命错误
};

class Logger;

#ifdef MUDUO_DEBUG
// 注意这里并不需要写 char* format
#define LOG_DEBUG(format,...) \
do{ \  
    Logger* logger = Logger::instance(); \
    logger->setLogLevel(LogLevel::DEBUG); \
    char buf[BUFFER_SIZE] = {0}; \ 
    snprintf(buf,BUFFER_SIZE,format,##__VA_ARGS__); \
    std::cout << __FILE__ << ":" << __LINE__; \ 
    logger->log(std::string(buf)); \ 
}while(0);
#else
#define LOG_DEBUG(format,...)
#endif

#define LOG_INFO(format,...) \
do{ \  
    Logger* logger = Logger::instance(); \
    logger->setLogLevel(LogLevel::INFO); \
    char buf[BUFFER_SIZE] = {0}; \ 
    snprintf(buf,BUFFER_SIZE,format,##__VA_ARGS__); \
    std::cout << __FILE__ << ":" << __LINE__; \ 
    logger->log(std::string(buf)); \ 
}while(0);

#define LOG_WARN(format,...) \
do{ \  
    Logger* logger = Logger::instance(); \
    logger->setLogLevel(LogLevel::WARN); \
    char buf[BUFFER_SIZE] = {0}; \ 
    snprintf(buf,BUFFER_SIZE,format,##__VA_ARGS__); \
    std::cout << __FILE__ << ":" << __LINE__; \ 
    logger->log(std::string(buf)); \ 
}while(0);

#define LOG_ERROR(format,...) \
do{ \  
    Logger* logger = Logger::instance(); \
    logger->setLogLevel(LogLevel::ERROR); \
    char buf[BUFFER_SIZE] = {0}; \ 
    snprintf(buf,BUFFER_SIZE,format,##__VA_ARGS__); \
    std::cout << __FILE__ << ":" << __LINE__; \ 
    logger->log(std::string(buf)); \ 
}while(0);

#define LOG_FATAL(format,...) \
do{ \  
    Logger* logger = Logger::instance(); \
    logger->setLogLevel(LogLevel::FATAL); \
    char buf[BUFFER_SIZE] = {0}; \ 
    snprintf(buf,BUFFER_SIZE,format,##__VA_ARGS__); \
    std::cout << __FILE__ << ":" << __LINE__; \ 
    logger->log(std::string(buf)); \ 
}while(0);

// 继承noncopyable类，防止被拷贝
class Logger : public noncopyable
{
public:
    // 获取单例对象
    static Logger* instance();
    // 设置当前的日志等级
    void setLogLevel(int level);
    // 日志输出
    void log(std::string);
private:
    // 当前的日志等级
    int level_; 
};

#endif