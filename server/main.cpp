#include "server.hpp"
#include <iostream>

int main(void)
{
    char buf[1024];
    Server server(20001);
    server.listen();
    server.recv(buf, 5);
    std::cout << buf << std::endl;
    return 0;
}
