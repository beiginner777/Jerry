#include "class.hpp"

/*

    官方实例的 Server，但是存在Sesion对象重复析构的隐患
    
*/

void Session::start()
{
    memset(_data,0,RECVSIZE);
    // 开始异步读
    _sock.async_read_some(boost::asio::buffer(_data,RECVSIZE),std::bind(&Session::handleRead,this,std::placeholders::_1,std::placeholders::_2));
}

void Session::handleRead(const boost::system::error_code& ec,std::size_t bytes_transferred)
{
    if(ec.value()){
        std::cout << "error code: " << ec.value() << std::endl;
        std::cout << "error message: " << ec.message() << std::endl;

        // delete this 是不安全的操作
        delete this;

        return;
    }

    // 输出读到的数据
    std::cout << "read data: " << _data << std::endl;

    // 将读到的数据 返回给客户端
    boost::asio::async_write(_sock,boost::asio::buffer(_data,bytes_transferred),std::bind(&Session::handleWrite,this,std::placeholders::_1,std::placeholders::_2));

}

void Session::handleWrite(const boost::system::error_code& ec,std::size_t bytes_transferred)
{
    if(ec.value()){
        std::cout << "error code: " << ec.value() << std::endl;
        std::cout << "error message: " << ec.message() << std::endl;
        
        // delete this 是不安全的操作
        delete this;

        return;
    }

    memset(_data,0,RECVSIZE);
    // 开始异步读
    _sock.async_read_some(boost::asio::buffer(_data,RECVSIZE),std::bind(&Session::handleRead,this,std::placeholders::_1,std::placeholders::_2));
}

Server::Server(boost::asio::io_context& ioc,unsigned int port) : _ioc(ioc),_acceptor(
    ioc,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),port))
{
    std::cout << "====== Server start =======" << std::endl;
    start_accept();
}

void Server::start_accept()
{
    Session* new_session = new Session(_ioc);

    // 因为要在异步接收的回调函数 里面 启动 当前Session的读写流程 因此要吧Session传进去回调函数
    _acceptor.async_accept(new_session->getSocket(),std::bind(&Server::handleAccept,this,new_session,std::placeholders::_1));

}

void Server::handleAccept(Session* new_session,const boost::system::error_code& ec)
{
    if(ec.value()){
        std::cout << "error code: " << ec.value() << std::endl;
        std::cout << "error message: " << ec.message() << std::endl;
        delete new_session;
    }else{
        std::cout << "new client connected." << std::endl;
        // 启动Session的读写流程
        new_session->start();
    }

    // 开始下一个异步接收
    start_accept();
}