#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

#include <iostream>

/*
* microSecondsSinceEpoch 是一个表示从 Unix 时间戳（1970 年 1 月 1 日至今的微秒数）
* 以来的时间间隔的值。它通常用于记录时间或计算时间差
*/

class TimeStamp
{
public:
    TimeStamp();
    TimeStamp(int64_t microSecondsSinceEpoch);
    // 获取当前的对象 (对象是指包含 microSecondsSinceEpoch 的类)
    TimeStamp now();
    // 类的成员函数 加 const 表示这个函数无法修改当前对象
    std::string toString() const;
private:
    // 实际上是 unsigned long long
    int64_t microSecondsSinceEpoch_;
};

#endif