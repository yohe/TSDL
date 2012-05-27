
#include <iostream>
#include <string>

#include <boost/asio.hpp>

using namespace boost::asio;

int main(int argc, char const* argv[])
{
    io_service io;
    ip::tcp::acceptor acc(io, ip::tcp::endpoint(ip::tcp::v4(), 30000));

    for(;;) {
        ip::tcp::iostream s;
        acc.accept(*s.rdbuf());

        std::string str;
        while(getline(s, str)) {
            s << str << std::endl;
            s.flush();
        }
    }
    return 0;
}
