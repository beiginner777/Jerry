#ifndef CLASS_HPP
#define CLASS_HPP

#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <iostream>
#include <queue>
#include <atomic>
#include <mutex>
#include "json.hpp"

#define RECVSIZE 1024             // 可以接收消息的最大长度
#define HEAD_LENGTH 2             // 头部字段的长度
#define RECV_MAX_LENGTH 1024 << 1 // 消息字段的最大长度

using namespace std;


// ---------------------------04.cpp-----------------------------------------------

// class MsgNode
// {
// public:
//     // 构造函数
//     MsgNode(int total_len) :_total(total_len), _cur(0)
//     {
//         _msg = new char[total_len];
//     }
//     ~MsgNode()
//     {
//         delete[] _msg;
//     }
//     // 消息的首地址
//     const char* _msg;
//     // 消息的总长度
//     int _total;
//     // 已经发送/接收的长度
//     int _cur;
// };

// class Session
// {
// public:
//     boost::asio::ip::tcp::socket _writeSock;
//     boost::asio::ip::tcp::socket _readSock;

//     std::shared_ptr<MsgNode> _send_data;
//     std::shared_ptr<MsgNode> _recv_data;

//     std::atomic<bool> _is_writing = false; // 是否正在写数据
//     std::atomic<bool> _is_reading = false; // 是否正在读取数据

//     std::queue<std::shared_ptr<MsgNode>> que;

//     bool _send_pedding; // 上一个结点发送完成就是 false 未发送完成就是true

//     // 会产生错误的异步发送流程 (没有队列的版本)
//     void writeToSocketErr(std::string str){}
//     void writeToSocketErrCallBack(boost::system::error_code ec,int transferred){}
//     // 正确异步发送流程
//     void writeToSocket(std::string str);
//     void writeToSocketCallBack(boost::system::error_code ec,int transferred);
//     // 正确的并且不需要反复调用回调函数的写流程
//     void writeAllToSocket(std::string str);
//     void writeAllToSocketCallBack(boost::system::error_code ec,int transferred);

//     // 正确的异步接收流程
//     void readFromSocket();
//     void readFromSocketCallBack(boost::system::error_code ec, int transferred);
//     // 正确的并且不需要反复调用回调函数的接收流程
//     void readAllFromSocket();
//     void readAllFromSocketCallBack(boost::system::error_code ec, int transferred);
// };

// ---------------------------05.cpp-----------------------------------------------

// class MsgNode
// {
// public:
//     // 构造函数
//     MsgNode() {}
//     MsgNode(char *msg, short max_len) : _total(max_len + HEAD_LENGTH), _cur(0)
//     {
//         _data = new char[_total + 1]();
//         memcpy(_data, &max_len, HEAD_LENGTH);
//         memcpy(_data + HEAD_LENGTH, msg, max_len);
//         _data[_total] = '\0';
//     }

//     MsgNode(int total_len) : _total(total_len), _cur(0)
//     {
//         _data = new char[total_len + 1];
//         _data[total_len] = '\0';
//     }
//     ~MsgNode()
//     {
//         delete[] _data;
//     }
//     // 清除消息
//     void Clear()
//     {
//         ::memset(_data, 0, _total);
//         _cur = 0;
//     }
//     // 消息的首地址
//     char *_data;
//     // 消息的总长度
//     int _total;
//     // 已经发送/接收的长度
//     int _cur;
// };

// class Session
// {
// public:
//     Session(boost::asio::io_context &ioc) : _ioc(ioc), _sock(ioc)
//     {
//     }
//     // 返回当前会话的Socket
//     boost::asio::ip::tcp::socket &getSocket()
//     {
//         return _sock;
//     }
//     ~Session()
//     {
//         std::cout << "Session is destory..." << std::endl;
//     }
//     // 发送函数
//     void Send(char *data, std::size_t len);
//     // 启动当前会话的读写流程
//     void start();
//     // 异步写函数的回调函数
//     void handleWrite(const boost::system::error_code &ec, std::size_t bytes_transferred);
//     // 异步读函数的回调函数
//     void handleRead(const boost::system::error_code &ec, std::size_t bytes_transferred);
//     // 与客户端进行通讯的socket
//     boost::asio::ip::tcp::socket _sock;
//     // 相当于一个epoll模型
//     boost::asio::io_context &_ioc;
//     // 存储读到的数据
//     char _data[RECVSIZE];
// };

// class Server
// {
// public:
//     Server(boost::asio::io_context &ioc, unsigned int port);
//     // 启动异步接收
//     void start_accept();
//     // 异步接收的回调函数
//     void handleAccept(Session* new_session, const boost::system::error_code &ec);
//     // 服务端的监听套接字
//     boost::asio::ip::tcp::acceptor _acceptor;
//     // 服务端的io_context
//     boost::asio::io_context &_ioc;
// };

// -----------------------06.cpp------------------------------------

// class MsgNode
// {
//     friend class Session;

// public:
//     // 构造函数
//     MsgNode() {}
//     MsgNode(char *msg, short max_len) : _total(max_len + HEAD_LENGTH), _cur(0)
//     {
//         _data = new char[_total + 1]();
//         memcpy(_data, &max_len, HEAD_LENGTH);
//         memcpy(_data + HEAD_LENGTH, msg, max_len);
//         _data[_total] = '\0';
//     }

//     MsgNode(int total_len) : _total(total_len), _cur(0)
//     {
//         _data = new char[total_len + 1];
//         _data[total_len] = '\0';
//     }
//     ~MsgNode()
//     {
//         delete[] _data;
//     }
//     // 清除消息
//     void Clear()
//     {
//         ::memset(_data, 0, _total);
//         _cur = 0;
//     }
//     // 消息的首地址
//     char *_data;
//     // 消息的总长度
//     int _total;
//     // 已经发送/接收的长度
//     int _cur;
// };

// // Session类 继承enbled_shared_from_this是为了使用 shared_from_this()函数 ：
// // 生成的智能指针 可以与 管理当前地址的智能指针 同步引用计数（同样是为了规避多重析构的问题）

// class Session : public std::enable_shared_from_this<Session>
// {
// public:
//     Session(boost::asio::io_context &ioc) : _ioc(ioc), _sock(ioc)
//     {
//     }
//     // 返回当前会话的Socket
//     boost::asio::ip::tcp::socket &getSocket()
//     {
//         return _sock;
//     }
//     ~Session()
//     {
//         std::cout << "Session is destory..." << std::endl;
//     }
//     // 发送函数
//     void Send(char *data, std::size_t len);
//     // 启动当前会话的读写流程
//     void start();
//     // 异步写函数的回调函数
//     void handleWrite(const boost::system::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<Session> session);
//     // 异步读函数的回调函数
//     void handleRead(const boost::system::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<Session> session);
//     // 与客户端进行通讯的socket
//     boost::asio::ip::tcp::socket _sock;
//     // 相当于一个epoll模型
//     boost::asio::io_context &_ioc;
//     // 存储读到的数据
//     char _data[RECVSIZE];
// };

// class Server
// {
// public:
//     Server(boost::asio::io_context &ioc, unsigned int port);
//     // 启动异步接收
//     void start_accept();
//     // 异步接收的回调函数
//     void handleAccept(std::shared_ptr<Session> new_session, const boost::system::error_code &ec);
//     //
//     boost::asio::ip::tcp::acceptor _acceptor;
//     //
//     boost::asio::io_context &_ioc;
// };


// -----------------------07.cpp------------------------------------

// class MsgNode
// {
//     friend class Session;

// public:
//     // 构造函数
//     MsgNode() {}
//     MsgNode(char *msg, short max_len) : _total(max_len + HEAD_LENGTH), _cur(0)
//     {
//         _data = new char[_total + 1]();
//         memcpy(_data, &max_len, HEAD_LENGTH);
//         memcpy(_data + HEAD_LENGTH, msg, max_len);
//         _data[_total] = '\0';
//     }

//     MsgNode(int total_len) : _total(total_len), _cur(0)
//     {
//         _data = new char[total_len + 1];
//         _data[total_len] = '\0';
//     }
//     ~MsgNode()
//     {
//         delete[] _data;
//     }
//     // 清除消息
//     void Clear()
//     {
//         ::memset(_data, 0, _total);
//         _cur = 0;
//     }
//     // 消息的首地址
//     char *_data;
//     // 消息的总长度
//     int _total;
//     // 已经发送/接收的长度
//     int _cur;
// };

// class Session : public std::enable_shared_from_this<Session>
// {
// public:
//     Session(boost::asio::io_context &ioc) : _ioc(ioc), _sock(ioc)
//     {
//     }
//     // 返回当前会话的Socket
//     boost::asio::ip::tcp::socket &getSocket()
//     {
//         return _sock;
//     }
//     ~Session()
//     {
//         std::cout << "Session is destory..." << std::endl;
//     }
//     // 发送函数
//     void Send(char *data, std::size_t len);
//     // 启动当前会话的读写流程
//     void start();
//     // 异步写函数的回调函数
//     void handleWrite(const boost::system::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<Session> session);
//     // 异步读函数的回调函数
//     void handleRead(const boost::system::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<Session> session);
//     // 与客户端进行通讯的socket
//     boost::asio::ip::tcp::socket _sock;
//     // 相当于一个epoll模型
//     boost::asio::io_context &_ioc;
//     // 存储读到的数据
//     char _data[RECVSIZE];
//     // 因为如果采用异步发送的话 异步函数的回调函数所在的线程 可能与当前线程不在一个线程中，所以要加锁
//     std::mutex _mutex;
//     // 存储消息实体
//     std::queue<shared_ptr<MsgNode>> que;
// };

// class Server
// {
// public:
//     Server(boost::asio::io_context &ioc, unsigned int port);
//     // 启动异步接收
//     void start_accept();
//     // 异步接收的回调函数
//     void handleAccept(std::shared_ptr<Session> new_session, const boost::system::error_code &ec);
//     //
//     boost::asio::ip::tcp::acceptor _acceptor;
//     //
//     boost::asio::io_context &_ioc;
// };

// -----------------------08.cpp------------------------------------

// class MsgNode
// {
//     friend class Session;

// public:
//     // 构造函数
//     MsgNode() {}
//     MsgNode(char *msg, short max_len) : _total(max_len + HEAD_LENGTH), _cur(0)
//     {
//         _data = new char[_total + 1]();
//         memcpy(_data, &max_len, HEAD_LENGTH);
//         memcpy(_data + HEAD_LENGTH, msg, max_len);
//         _data[_total] = '\0';
//     }

//     MsgNode(int total_len) : _total(total_len), _cur(0)
//     {
//         _data = new char[total_len + 1];
//         _data[total_len] = '\0';
//     }
//     ~MsgNode()
//     {
//         delete[] _data;
//     }
//     // 清除消息
//     void Clear()
//     {
//         ::memset(_data, 0, _total);
//         _cur = 0;
//     }
//     // 消息的首地址
//     char *_data;
//     // 消息的总长度
//     int _total;
//     // 已经发送/接收的长度
//     int _cur;
// };

// class Session : public std::enable_shared_from_this<Session>
// {
// public:
//     Session(boost::asio::io_context &ioc) : _ioc(ioc), _sock(ioc)
//     {
//         _recv_head_node = make_shared<MsgNode>(HEAD_LENGTH);
//     }
//     // 返回当前会话的Socket
//     boost::asio::ip::tcp::socket &getSocket()
//     {
//         return _sock;
//     }
//     ~Session()
//     {
//         std::cout << "Session is destory..." << std::endl;
//     }
//     // 发送函数
//     void Send(char *data, std::size_t len);
//     // 启动当前会话的读写流程
//     void start();
//     // 异步写函数的回调函数
//     void handleWrite(const boost::system::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<Session> session);
//     // 异步读函数的回调函数
//     void handleRead(const boost::system::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<Session> session);
//     // 打印数据的十六进制形式
//     void PrintRecvData(char *data, int length);
//     // 与客户端进行通讯的socket
//     boost::asio::ip::tcp::socket _sock;
//     // 相当于一个epoll模型
//     boost::asio::io_context &_ioc;
//     // 存储读到的数据
//     char _data[RECVSIZE];
//     // 因为如果采用异步发送的话 异步函数的回调函数所在的线程 可能与当前线程不在一个线程中，所以要加锁
//     std::mutex _mutex;
//     // 存储消息实体
//     std::queue<shared_ptr<MsgNode>> que;
//     // 接收头部消息的结点
//     shared_ptr<MsgNode> _recv_head_node;
//     // 因为读流程的异步函数不一定是在一个线程中 因此需要 原子变量来保证接收消息的一致性
//     atomic<bool> _b_read_prase = false;
//     // 接收消息实体的结点
//     shared_ptr<MsgNode> _recv_msg_node;
// };

// class Server
// {
// public:
//     Server(boost::asio::io_context &ioc, unsigned int port);
//     // 启动异步接收
//     void start_accept();
//     // 异步接收的回调函数
//     void handleAccept(std::shared_ptr<Session> new_session, const boost::system::error_code &ec);
//     //
//     boost::asio::ip::tcp::acceptor _acceptor;
//     //
//     boost::asio::io_context &_ioc;
// };


// --------------------------- 09.cpp ------------------------------------------
class MsgNode
{
    friend class Session;

public:
    // 构造函数
    MsgNode() {}
    MsgNode(char *msg, short max_len) : _total(max_len + HEAD_LENGTH), _cur(0)
    {
        _data = new char[_total + 1]();
        memcpy(_data, &max_len, HEAD_LENGTH);
        memcpy(_data + HEAD_LENGTH, msg, max_len);
        _data[_total] = '\0';
    }

    MsgNode(int total_len) : _total(total_len), _cur(0)
    {
        _data = new char[total_len + 1];
        _data[total_len] = '\0';
    }
    ~MsgNode()
    {
        delete[] _data;
    }
    // 清除消息
    void Clear()
    {
        ::memset(_data, 0, _total);
        _cur = 0;
    }
    // 消息的首地址
    char *_data;
    // 消息的总长度
    int _total;
    // 已经发送/接收的长度
    int _cur;
};

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::io_context &ioc) : _ioc(ioc), _sock(ioc)
    {
        _recv_head_node = make_shared<MsgNode>(HEAD_LENGTH);
    }
    // 返回当前会话的Socket
    boost::asio::ip::tcp::socket &getSocket()
    {
        return _sock;
    }
    ~Session()
    {
        std::cout << "Session is destory..." << std::endl;
    }
    // 发送函数
    void Send(char *data, std::size_t len);
    // 启动当前会话的读写流程
    void start();
    // 异步写函数的回调函数
    void handleWrite(const boost::system::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<Session> session);
    // 异步读函数的回调函数
    void handleRead(const boost::system::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<Session> session);
    // 打印数据的十六进制形式
    void PrintRecvData(char *data, int length);
    // 与客户端进行通讯的socket
    boost::asio::ip::tcp::socket _sock;
    // 相当于一个epoll模型
    boost::asio::io_context &_ioc;
    // 存储读到的数据
    char _data[RECVSIZE];
    // 因为如果采用异步发送的话 异步函数的回调函数所在的线程 可能与当前线程不在一个线程中，所以要加锁
    std::mutex _mutex;
    // 存储消息实体
    std::queue<shared_ptr<MsgNode>> que;
    // 接收头部消息的结点
    shared_ptr<MsgNode> _recv_head_node;
    // 因为读流程的异步函数不一定是在一个线程中 因此需要 原子变量来保证接收消息的一致性
    atomic<bool> _b_read_prase = false;
    // 接收消息实体的结点
    shared_ptr<MsgNode> _recv_msg_node;
};

class Server
{
public:
    Server(boost::asio::io_context &ioc, unsigned int port);
    // 启动异步接收
    void start_accept();
    // 异步接收的回调函数
    void handleAccept(std::shared_ptr<Session> new_session, const boost::system::error_code &ec);
    //
    boost::asio::ip::tcp::acceptor _acceptor;
    //
    boost::asio::io_context &_ioc;
};

#endif