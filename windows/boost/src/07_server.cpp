#include "class.hpp"

/*

与06_server.cpp不同的是：   
    
    增加了发送队列来实现全双工通讯 而不是应答式服务

*/

void Session::start()
{
    memset(_data,0,RECVSIZE);
    // 开始异步读
    _sock.async_read_some(boost::asio::buffer(_data,RECVSIZE),std::bind(&Session::handleRead,this,std::placeholders::_1,std::placeholders::_2,shared_from_this()));
}

void Session::handleRead(const boost::system::error_code& ec,std::size_t bytes_transferred,std::shared_ptr<Session> session)
{
    if(ec.value()){
        std::cout << "error code: " << ec.value() << std::endl;
        std::cout << "error message: " << ec.message() << std::endl;

        // delete this 是不安全的操作
        // delete this;

        return;
    }
    // 输出读到的数据
    std::cout << "read data: " << _data << std::endl;

    Send(_data,bytes_transferred);
    
    memset(_data,0,RECVSIZE);

    // 再次注册一个 读事件
    _sock.async_read_some(boost::asio::buffer(_data,RECVSIZE),std::bind(&Session::handleRead,this,std::placeholders::_1,std::placeholders::_2,session));
}

void Session::handleWrite(const boost::system::error_code& ec,std::size_t bytes_transferred,std::shared_ptr<Session> session)
{
    if(ec.value()){
        std::cout << "error code: " << ec.value() << std::endl;
        std::cout << "error message: " << ec.message() << std::endl;
        
        // delete this 是不安全的操作
        // delete this;

        return;
    }

    // 回调函数操作共享的发送队列 加锁
    lock_guard<mutex> _locker(_mutex);
    // 正确的发送逻辑
    que.pop();
    if(que.size() > 0){
        auto msgNode = que.front();
        boost::asio::async_write(_sock,boost::asio::buffer(msgNode->_data,msgNode->_total),std::bind(&Session::handleWrite,this,std::placeholders::_1,std::placeholders::_2,session));
    }
}

void Session::Send(char* data,std::size_t len)
{
    // 因为要将数据加入队列当中，而队列是共享资源，因此加锁
    lock_guard<mutex> _locker(_mutex);
    // 将待发送的数据加入队列当中
    que.push(make_shared<MsgNode>(data,len));
    if(que.size() > 1){
        // 如果队列中有数据，就说明当前由数据在发送
        return;
    }

    // 否则就说明当前没有数据在发送

    // 异步发送数据
    boost::asio::async_write(_sock,boost::asio::buffer(data,len),std::bind(&Session::handleWrite,this,std::placeholders::_1,std::placeholders::_2,shared_from_this()));
}

Server::Server(boost::asio::io_context& ioc,unsigned int port) : _ioc(ioc),_acceptor(
    ioc,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),port))
{
    std::cout << "====== Server start =======" << std::endl;
    start_accept();
}

void Server::start_accept()
{
    auto new_session = std::make_shared<Session>(_ioc);

    // 因为要在异步接收的回调函数 里面 启动 当前Session的读写流程 因此要吧Session传进去回调函数
    _acceptor.async_accept(new_session->getSocket(),std::bind(&Server::handleAccept,this,new_session,std::placeholders::_1));

}

void Server::handleAccept(std::shared_ptr<Session> new_session,const boost::system::error_code& ec)
{
    if(ec.value()){
        std::cout << "error code: " << ec.value() << std::endl;
        std::cout << "error message: " << ec.message() << std::endl;

    }else{
        std::cout << "new client connected." << std::endl;
        // 启动Session的读写流程
        new_session->start();
    }

    // 开始下一个异步接收
    start_accept();
}