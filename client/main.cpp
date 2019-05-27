#include "client.hpp"
#include <iostream>

int main(void)
{
    char buf[1024] = "abcdeabcdeabcdeabcde";
    int temp;
    Client client("10.10.10.123", 20001, MSG_WAITALL);
    client.connect();
    std::cin >> temp;
    client.send(buf, 20);
    return 0;
}
