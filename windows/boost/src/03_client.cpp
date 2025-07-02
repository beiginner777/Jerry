#include <iostream>
#include <boost/asio.hpp>
#include <string>

#define HOST "127.0.0.1"
#define PORT 8000
#define MAX_LENGTH 1024

/*

    同步模式的客户端
    1) 从控制台获取数据 并 向服务器发送
    2) 接收来自服务器的数据 并 在控制台打印服务器的相关信息

*/
int main()
{
    // 创建sock并且打开
    boost::asio::io_context ioc;
    boost::system::error_code ec;
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::make_address(HOST,ec),PORT);
    if(ec.value()){
        std::cout << "error code: " << ec.value() << std::endl;
        std::cout << "error message " << ec.message() << std::endl;
        return ec.value();
    }
    // 创建sock并且以ipV4的形式打开
    boost::asio::ip::tcp::socket sock(ioc,boost::asio::ip::tcp::v4());
    // 连接服务器
    sock.connect(ep,ec);
    if(ec.value()){
        std::cout << "error code: " << ec.value() << std::endl;
        std::cout << "error message " << ec.message() << std::endl;
        return ec.value();
    }
    std::cout << "connect server success !"<< std::endl;

    for(;;){
        char buf[MAX_LENGTH] = {0};
        int read_num = read(STDIN_FILENO,buf,MAX_LENGTH);
        if(std::string(buf,read_num) == std::string("exit")){
            sock.shutdown(boost::asio::ip::tcp::socket::shutdown_send); // 向服务器发出 EOF
            std::cout << "Sent EOF to server. Waiting for response..." << std::endl;
            continue;
        }
        size_t writeLength = sock.write_some(boost::asio::buffer(buf,read_num),ec);
        if(ec.value()){
            std::cout << "error code: " << ec.value() << std::endl;
            std::cout << "error message " << ec.message() << std::endl;
            return ec.value();
        }
        // 接收服务器返回的消息
        char reply[MAX_LENGTH] = {0};
        size_t reply_len = sock.read_some(boost::asio::buffer(reply), ec);
        if (ec == boost::asio::error::eof){
            std::cout << "Server closed the connection." << std::endl;
            break;
        }
        else if (ec){
            std::cerr << "Read failed: " << ec.message() << std::endl;
            break;
        }
        std::cout << "Reply from server: " << std::string(reply, reply_len) << std::endl;
    }
    return 0;
}