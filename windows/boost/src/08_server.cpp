#include "class.hpp"
#include <iomanip>

/*

与07_server.cpp不同的是：

    完善了 handleRead 函数来处理粘包问题:
    1) 增加了接收头部消息的结点
    2）增加了接受消息主体的结点
    3）增加了是否接收完头部结点的bool变量
*/

void Session::start()
{
    memset(_data, 0, RECVSIZE);
    // 开始异步读
    _sock.async_read_some(boost::asio::buffer(_data, RECVSIZE), std::bind(&Session::handleRead, this, std::placeholders::_1, std::placeholders::_2, shared_from_this()));
}

void Session::PrintRecvData(char* data, int length) {
    stringstream ss;
    string result = "0x";
    for (int i = 0; i < length; i++) {
        string hexstr;
        ss << hex << std::setw(2) << std::setfill('0') << int(data[i]) << endl;
        ss >> hexstr;
        result += hexstr;
    }
    std::cout << "receive raw data is : " << result << endl;;
}

void Session::handleRead(const boost::system::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<Session> session)
{
    if (ec.value())
    {
        std::cout << "error code: " << ec.value() << std::endl;
        std::cout << "error message: " << ec.message() << std::endl;
        // delete this 是不安全的操作
        // delete this;
        return;
    }

    this_thread::sleep_for(std::chrono::seconds(2));
    PrintRecvData(_data, bytes_transferred);
    // ============ 开始处理接收的消息 ==============
    
    // 已经处理的长度
    int copy_len = 0;
    // 存储此次要接收的数据长度
    short data_len = 0;

    // 将接收的数据打印
    std::cout << "data: " << _data << std::endl;

    // 当前未处理的消息的长度
    while (bytes_transferred > 0)
    {
        // 如果头部消息 还没接收完全的话
        if (!_b_read_prase)
        {
            // 如果当前未处理的消息的长度 + 头部已经有的消息长度 < 头部所需要的长度
            if (bytes_transferred + _recv_head_node->_cur < HEAD_LENGTH)
            {
                // 将当前未处理的数据全部复制到接收头部消息的结点当中
                memcpy(_recv_head_node->_data + _recv_head_node->_cur, _data, bytes_transferred);
                // 头部已经有的消息长度增加
                _recv_head_node->_cur += bytes_transferred;
                // 清空缓冲区 准备下一次读取数据
                ::memset(_data, 0, RECVSIZE);
                // 调用异步read函数
                _sock.async_read_some(boost::asio::buffer(_data, RECVSIZE), std::bind(&Session::handleRead, this, std::placeholders::_1, std::placeholders::_2, session));

                return;
            }
            // 如果当前未处理的消息的长度 + 头部已经有的消息长度 >= 头部所需要的长度

            if (bytes_transferred + _recv_head_node->_cur >= HEAD_LENGTH)
            {
                cout << "bytes_transferred = " << bytes_transferred << endl;

                // 说明头部消息可以在这一次处理中接收完

                // 将数据复制到接收消息头部的结点当中
                ::memcpy(_recv_head_node->_data + _recv_head_node->_cur, _data, HEAD_LENGTH - _recv_head_node->_cur);
                // 当前 _data缓冲区 已经处理的数据长度
                copy_len += HEAD_LENGTH - _recv_head_node->_cur;
                // 更新未处理的消息长度
                bytes_transferred -= (HEAD_LENGTH - _recv_head_node->_cur);
                // 更新接收头部消息的结点信息
                _recv_head_node->_cur = HEAD_LENGTH;

                cout << "updated bytes_transferred = " << bytes_transferred << endl;
            }

            // 如果当前接收到的消息主体的长度 > 最大可以接受的消息长度 RECV_MAX_LENGTH
            // 那么就直接返回，不做处理

            // 将存储消息长度的结点中的长度取出
            data_len = 0;
            memcpy(&data_len, _recv_head_node->_data, HEAD_LENGTH);
            cout << "data_len is " << data_len << endl;

            if (data_len > RECV_MAX_LENGTH)
            {
                // 清空head结点
                _recv_head_node->Clear();
                // 说明接收的消息长度 超过了 最大可以接收的长度
                std::cout << "Message length is too long" << std::endl;
                return;
            }

            // 开辟存储消息的结点
            _recv_msg_node = std::make_shared<MsgNode>(data_len);
        }

        // 如果未处理的消息的长度 + 消息主体已经有的长度 < 消息主体所需要的长度
        if (bytes_transferred + _recv_msg_node->_cur < data_len)
        {
            // 说明还需要再次异步接收（read）

            // 先将此次数据保存下来
            ::memcpy(_recv_msg_node->_data + _recv_msg_node->_cur, _data + copy_len, bytes_transferred);
            // 更新消息主体的结点信息
            _recv_msg_node->_cur += bytes_transferred;
            // 修改标记信息
            _b_read_prase = true;
            // 清空缓冲区 准备下一次读取数据
            ::memset(_data, 0, RECVSIZE);
            // 异步读取数据
            _sock.async_read_some(boost::asio::buffer(_data, RECVSIZE), std::bind(&Session::handleRead, this, std::placeholders::_1, std::placeholders::_2, session));
        }
        // 如果未处理的消息的长度 + 消息主体已经有的长度 >= 消息主体所需要的长度
        else
        {
            // 说明这一次发送将一条消息全部发送完，并且还有剩余 或者 是刚好将一条消息发送完
            // 将剩余的数据复制到消息主体的结点当中
            int remain_msg = _recv_msg_node->_total - _recv_msg_node->_cur;
            // 需要放在消息数据
            ::memcpy(_recv_msg_node->_data + _recv_msg_node->_cur, _data + copy_len, remain_msg);
            // 消息主体的结点信息更新
            _recv_msg_node->_cur += remain_msg;
            // 剩余的未处理的数据(其实已经是属于下一条的消息)
            bytes_transferred -= remain_msg;
            // 当前已经处理的数据长度
            copy_len += remain_msg;
            // 打印当前接收到的消息z主体的信息
            cout << "receive data is " << _recv_msg_node->_data << endl;

            // 因为这次发送已经将一条消息给处理完了 因此需要清空
            _b_read_prase = false;
            _recv_head_node->Clear();
            // 说明此次发送将一条消息处理完了
            if (bytes_transferred == 0)
            {
                ::memset(_data, 0, RECVSIZE);
                _sock.async_read_some(boost::asio::buffer(_data, RECVSIZE),
                                      std::bind(&Session::handleRead, this, std::placeholders::_1, std::placeholders::_2, session));
                return;
            }
            // 说明这一次在_data缓冲区中还有另一条消息的头部 所以需要继续处理
            else
            {
                continue;
            }
        }
    }
}

void Session::handleWrite(const boost::system::error_code &ec, std::size_t bytes_transferred, std::shared_ptr<Session> session)
{
    if (ec.value())
    {
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
    if (que.size() > 0)
    {
        auto msgNode = que.front();
        boost::asio::async_write(_sock, boost::asio::buffer(msgNode->_data, msgNode->_total), std::bind(&Session::handleWrite, this, std::placeholders::_1, std::placeholders::_2, session));
    }
}

void Session::Send(char *data, std::size_t len)
{
    // 因为要将数据加入队列当中，而队列是共享资源，因此加锁
    lock_guard<mutex> _locker(_mutex);
    // 将待发送的数据加入队列当中
    que.push(make_shared<MsgNode>(data, len));
    if (que.size() > 1)
    {
        // 如果队列中有数据，就说明当前由数据在发送
        return;
    }

    // 否则就说明当前没有数据在发送

    // 异步发送数据
    boost::asio::async_write(_sock, boost::asio::buffer(data, len), std::bind(&Session::handleWrite, this, std::placeholders::_1, std::placeholders::_2, shared_from_this()));
}

Server::Server(boost::asio::io_context &ioc, unsigned int port) : _ioc(ioc),
                                                                  _acceptor(ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    std::cout << "====== Server start =======" << std::endl;
    start_accept();
}

void Server::start_accept()
{
    auto new_session = std::make_shared<Session>(_ioc);

    // 因为要在异步接收的回调函数 里面 启动 当前Session的读写流程 因此要吧Session传进去回调函数
    _acceptor.async_accept(new_session->getSocket(), std::bind(&Server::handleAccept, this, new_session, std::placeholders::_1));
}

void Server::handleAccept(std::shared_ptr<Session> new_session, const boost::system::error_code &ec)
{
    if (ec.value())
    {
        std::cout << "error code: " << ec.value() << std::endl;
        std::cout << "error message: " << ec.message() << std::endl;
    }
    else
    {
        std::cout << "new client connected." << std::endl;
        // 启动Session的读写流程
        new_session->start();
    }

    // 开始下一个异步接收
    start_accept();
}