#include <iostream>
#include "class.hpp"

int main()
{
    boost::asio::io_context ioc;
    Server _server(ioc,8000);
    ioc.run();
    return 0;
}