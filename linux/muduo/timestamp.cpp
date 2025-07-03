#include "timestamp.hpp"

TimeStamp::TimeStamp() : microSecondsSinceEpoch_(0)
{
}
TimeStamp::TimeStamp(int64_t microSecondsSinceEpoch) : 
    microSecondsSinceEpoch_(microSecondsSinceEpoch)
{
}

TimeStamp TimeStamp::now()
{
    return TimeStamp(time(nullptr));
}

std::string TimeStamp::toString() const
{
    char buf[32] = {0};
    tm* currentTime = localtime(&microSecondsSinceEpoch_);
    snprintf(buf,32,"%04d/%02d/%02d %02d:%02d:%02d",
        currentTime->tm_year + 1900,
        currentTime->tm_mon + 1,
        currentTime->tm_mday,
        currentTime->tm_hour,
        currentTime->tm_min,
        currentTime->tm_sec);
    return std::string(buf);
}