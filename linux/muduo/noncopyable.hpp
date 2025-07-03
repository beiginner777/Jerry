#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

/*
* 是为了让继承类不能被拷贝
*/

class noncopyable
{
public:
    // 因为子类进行拷贝构造和赋值操作时，会调用父类的拷贝构造和赋值操作，
    // 所以父类的拷贝构造和赋值操作应该被删除，就组织了子类对象被拷贝

    // 删除拷贝构造函数
    noncopyable(const noncopyable&) = delete;
    // 删除赋值运算符
    void operator=(const noncopyable&) = delete;
protected:
    // 让子类对象可以访问默认的构造函数 和 析构函数，子类可以正常地创建
    
    // 保护构造函数，防止直接实例化
    noncopyable() = default;
    // 保护析构函数，防止直接删除
    ~noncopyable() = default;
};

#endif