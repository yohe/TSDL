
#include <iostream>

#include <boost/asio.hpp>
using namespace boost::asio;

int main(int argc, char const* argv[])
{
    
    io_service io;
    ip::tcp::iostream s("127.0.0.1", "30000");


    s << "Hello" << std::endl;
    s.flush();

    sleep(1);

    std::string str;
    s >> str;
    std::cout << "client: " << str << std::endl;

    return 0;
}
