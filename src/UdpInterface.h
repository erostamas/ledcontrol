#pragma once

#include <vector>

class UdpInterface {
public:
    void run();
    int bindToPort(int portno);
    std::vector<std::string> getMessages();

    std::vector<std::string> _messageQueue;
private:
    std::string _wireIpAddress;
}; 