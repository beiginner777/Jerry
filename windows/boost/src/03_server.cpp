#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <memory>

#define HOST "127.0.0.1"
#define PORT 8000
#define MAX_LENGTH 1024

/*

    同步模式的服务端
    1) 接收来自服务器的数据 但是不做处理 直接返回
    2) 在控制台打印客户端的相关信息

*/

void connectClient(boost::asio::ip::tcp::socket sock)
{
    try
    {
        for (;;)
        {
            // 接收来自客户端的消息
            char data[MAX_LENGTH] = {0};
            boost::system::error_code ec;
            // 表示接收的最大长度是 MAX_LENGTH
            size_t readLength = sock.read_some(boost::asio::buffer(data, MAX_LENGTH), ec);
            if (ec == boost::asio::error::eof)
            {
                // 客户端主动关闭连接（ctrl + D）
                std::cout << "connecton closed by peer." << std::endl;
            }
            else if (ec.value())
            {
                // 发生了其它的异常
                throw boost::system::error_code(ec);
                break;
            }

            // 没有发生异常 那么就正常处理逻辑
            // 将接收的消息打印到控制台
            std::cout << "receive " << data << " from " << sock.remote_endpoint().address().to_string() << ":" << sock.remote_endpoint().port() << std::endl;

            // 将数据返回给客户端
            boost::asio::write(sock, boost::asio::buffer(data, readLength));
        }
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Exception in handle_client: " << ex.what() << std::endl;
    }
}

int main()
{
    boost::asio::io_context ioc;
    boost::system::error_code ec;
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::make_address(HOST, ec), PORT);
    if (ec.value())
    {
        std::cout << "error code: " << ec.value() << std::endl;
        std::cout << "error message: " << ec.message() << std::endl;
        return ec.value();
    }
    // 创建 打开 绑定
    boost::asio::ip::tcp::acceptor acceptor(ioc, ep);
    // 监听
    acceptor.listen();
    std::cout << "server is ready." << std::endl;
    // 循环接收客户端的连接
    for (;;)
    {
        // 只需要创建 不需要打开
        boost::asio::ip::tcp::socket sock(ioc);
        acceptor.accept(sock, ec);
        if (ec.value())
        {
            std::cout << "error code: " << ec.value() << std::endl;
            std::cout << "error message: " << ec.message() << std::endl;
            return ec.value();
        }
        std::cout << sock.remote_endpoint().address().to_string() << ":" << sock.remote_endpoint().port() << "  client connect." << std::endl;
        /*
        这里你将 boost::asio::ip::tcp::socket（不可复制）传给了一个以值传递的线程函数参数，而 socket 是 不可拷贝（non-copyable） 的对象，因此会导致编译失败或未定义行为。

            std::thread(connectClient, sock).detach();
        */
        std::thread(connectClient, std::move(sock)).detach();
    }

    return 0;
}