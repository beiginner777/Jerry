#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <thread>
#include <chrono>

#define HOST "127.0.0.1"
#define PORT 8000
#define MAX_LENGTH 1024
#define HEAD_LENGTH 2

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

// /*

//     同步模式的客户端
//     1) 从控制台获取数据 并 向服务器发送
//     2) 接收来自服务器的数据 并 在控制台打印服务器的相关信息
//     3) 不同的是 还需要向服务器传达每次发送的消息的长度
// */

#if 0
int main()
{
    // 创建sock并且打开
    boost::asio::io_context ioc;
    boost::system::error_code ec;
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::make_address(HOST, ec), PORT);
    if (ec.value())
    {
        std::cout << __FILE__ << " : " << __LINE__ << std::endl;
        std::cout << "error code: " << ec.value() << std::endl;
        std::cout << "error message " << ec.message() << std::endl;
        return ec.value();
    }
    // 创建sock并且以ipV4的形式打开
    boost::asio::ip::tcp::socket sock(ioc, boost::asio::ip::tcp::v4());
    // 连接服务器
    sock.connect(ep, ec);
    if (ec.value())
    {
        std::cout << __FILE__ << " : " << __LINE__ << std::endl;
        std::cout << "error code: " << ec.value() << std::endl;
        std::cout << "error message " << ec.message() << std::endl;
        return ec.value();
    }
    std::cout << "connect server success !" << std::endl;

    for (;;)
    {
        char buf[MAX_LENGTH - 2] = {0};
        short read_num = read(STDIN_FILENO, buf, MAX_LENGTH - 2);
        char send_data[MAX_LENGTH] = {0};
        // 头部字段 存放 消息的长度
        ::memcpy(send_data, &read_num, HEAD_LENGTH);
        std::cout << "send_data: " << send_data << std::endl;
        // 存放消息主体
        ::memcpy(send_data + HEAD_LENGTH, buf, read_num);
        std::cout << "send_data: " << send_data << std::endl;
        // 发送消息
        boost::asio::write(sock, boost::asio::buffer(send_data, read_num + HEAD_LENGTH), ec);

        if (ec.value())
        {
            std::cout << __FILE__ << " : " << __LINE__ << std::endl;
            std::cout << "error code: " << ec.value() << std::endl;
            std::cout << "error message: " << ec.message() << std::endl;
            return 0;
        }
        // // 接收服务器返回的消息
        // char reply[MAX_LENGTH] = {0};
        // // 首先接收消息的长度信息
        // boost::asio::read(sock, boost::asio::buffer(reply, HEAD_LENGTH), ec);
        // if (ec.value())
        // {
        //     std::cout << __FILE__ << " : " << __LINE__ << std::endl;
        //     std::cout << "error code: " << ec.value() << std::endl;
        //     std::cout << "error message: " << ec.message() << std::endl;
        //     return 0;
        // }
        // std::cout << "reply len = " << reply << std::endl;
        // // 消息的长度
        // short reply_len = 0;
        // ::memcpy(&reply_len, reply, HEAD_LENGTH);
        // // 接受消息的主体
        // boost::asio::read(sock, boost::asio::buffer(reply + HEAD_LENGTH, reply_len), ec);
        // if (ec.value())
        // {
        //     std::cout << __FILE__ << " : " << __LINE__ << std::endl;
        //     std::cout << "error code: " << ec.value() << std::endl;
        //     std::cout << "error message: " << ec.message() << std::endl;
        //     return 0;
        // }
        // std::cout << "reply = " << reply << std::endl;
    }
    return 0;
}

#else
int main()
{
    try
    {
        // 创建上下文服务
        boost::asio::io_context ioc;
        // 构造endpoint
        tcp::endpoint remote_ep(boost::asio::ip::make_address("127.0.0.1"), 8000);
        tcp::socket sock(ioc);
        boost::system::error_code error = boost::asio::error::host_not_found;
        ;
        sock.connect(remote_ep, error);
        if (error)
        {
            cout << "connect failed, code is " << error.value() << " error msg is " << error.message();
            return 0;
        }

        char request[MAX_LENGTH] = "Hello,world!";
        while (1)
        {
            this_thread::sleep_for(std::chrono::milliseconds(1));
            cout << "request = " << request << endl;
            size_t request_length = strlen(request);
            char send_data[MAX_LENGTH] = {0};
            memcpy(send_data, &request_length, 2);
            memcpy(send_data + 2, request, request_length);
            boost::asio::write(sock, boost::asio::buffer(send_data, request_length + 2));
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << endl;
    }
    return 0;
}
#endif