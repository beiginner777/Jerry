#include "class.hpp"

/*

    异步api 的简单示例

*/

void Session::writeToSocket(std::string str)
{
    que.push(std::make_shared<MsgNode>(str.c_str(), str.length()));
    if (_is_writing)
    {
        return;
    }

    _send_data = que.front();

    this->_writeSock.async_write_some(
        boost::asio::buffer(_send_data->_msg + _send_data->_cur, _send_data->_total - _send_data->_cur),
        std::bind(&Session::writeToSocketErrCallBack, this,
                  std::placeholders::_1, std::placeholders::_2));

    _is_writing = true;
}
void Session::writeToSocketCallBack(boost::system::error_code ec, int transferred)
{
    if (ec.value())
    {
        std::cout << "error code: " << ec.message() << std::endl;
        std::cout << "error message: " << ec.message() << std::endl;
        return;
    }

    _send_data->_cur += transferred;

    if (_send_data->_cur < _send_data->_total)
    {
        this->_writeSock.async_write_some(
            boost::asio::buffer(_send_data->_msg + _send_data->_cur, _send_data->_total - _send_data->_cur),
            std::bind(&Session::writeToSocketErrCallBack, this,
                      std::placeholders::_1, std::placeholders::_2));
        return;
    }

    que.pop();

    if (que.empty())
    {
        _is_writing = false;
        return;
    }
    else
    {
        _send_data = que.front();
        this->_writeSock.async_write_some(
            boost::asio::buffer(_send_data->_msg + _send_data->_cur, _send_data->_total - _send_data->_cur),
            std::bind(&Session::writeToSocketErrCallBack, this,
                    std::placeholders::_1, std::placeholders::_2));
    }
}

void Session::writeAllToSocket(std::string str)
{
    que.push(std::make_shared<MsgNode>(str.c_str(), str.length()));
    if (_is_writing)
    {
        return;
    }

    _send_data = que.front();

    this->_writeSock.async_send(boost::asio::buffer(str.data(), str.length()),
                                std::bind(&Session::writeAllToSocketCallBack, this, std::placeholders::_1, std::placeholders::_2));

    _is_writing = true;
}
void Session::writeAllToSocketCallBack(boost::system::error_code ec, int transferred)
{
    if (ec.value())
    {
        std::cout << "error code: " << ec.value() << std::endl;
        std::cout << "error message: " << ec.message() << std::endl;
        return;
    }

    que.pop();

    if (que.empty())
    {
        _is_writing = false;
        return;
    }
    else
    {
        _send_data = que.front();
        this->_writeSock.async_send(boost::asio::buffer(_send_data->_msg, _send_data->_total),
                                    std::bind(&Session::writeAllToSocketCallBack, this, std::placeholders::_1, std::placeholders::_2));
    }
}

// 正确的异步接收流程
void Session::readFromSocket()
{
    if (_is_reading)
    {
        return;
    }
    _recv_data = std::make_shared<MsgNode>(RECVSIZE);
    this->_readSock.async_read_some(boost::asio::buffer(_recv_data->_msg, _recv_data->_total),
                                    std::bind(&Session::readFromSocketCallBack, this, std::placeholders::_1, std::placeholders::_2));
    _is_reading = true;
}

void Session::readFromSocketCallBack(boost::system::error_code ec, int transferred)
{
    if (ec.value())
    {
        std::cout << "error code: " << ec.value() << std::endl;
        std::cout << "error message: " << ec.message() << std::endl;
        return;
    }

    _recv_data->_cur += transferred;

    if (_recv_data->_cur < _recv_data->_total)
    {
        this->_readSock.async_read_some(boost::asio::buffer(_recv_data->_msg + _recv_data->_cur, _recv_data->_total - _recv_data->_cur),
                                        std::bind(&Session::readFromSocketCallBack, this, std::placeholders::_1, std::placeholders::_2));
        return;
    }

    _is_reading = false;
    std::cout << "Received data: " << std::string(_recv_data->_msg, _recv_data->_total) << std::endl;
    _recv_data = nullptr;
}

void Session::readAllFromSocket()
{
    if (_is_reading)
    {
        return;
    }
    _recv_data = std::make_shared<MsgNode>(new char[1024], 1024);
    this->_readSock.async_receive(boost::asio::buffer(_recv_data->_msg, _recv_data->_total),
                                  std::bind(&Session::readAllFromSocketCallBack, this, std::placeholders::_1, std::placeholders::_2));
    _is_reading = true;
}
void Session::readAllFromSocketCallBack(boost::system::error_code ec, int transferred)
{
    if (ec.value())
    {
        std::cout << "error code: " << ec.value() << std::endl;
        std::cout << "error message: " << ec.message() << std::endl;
        return;
    }
    _recv_data = nullptr;
    _is_reading = false;
}