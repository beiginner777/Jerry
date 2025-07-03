#include "log.hpp"

// 获取单例对象
Logger* Logger::instance()
{
    static Logger logger;
    return &logger;
}
// 设置当前的日志等级
void Logger::setLogLevel(int level)
{
    this->level_ = level;
}
// 日志输出
void Logger::log(std::string msg)
{
    switch (level_)
    {
    case DEBUG:
        std::cout << " [DEBUG] ";
        break;
    case INFO:
        std::cout << " [INFO] ";
        break;
    case WARN:
        std::cout << " [WARN] ";
        break;
    case ERROR:
        std::cout << " [ERROR] ";
        break;
    case FATAL:
        std::cout << " [FATAL] ";
        break;
    default:
        break;
    }
    std::cout << "time:"<< TimeStamp().now().toString() << std::endl;
    std::cout << "msg: " << msg << std::endl;
}