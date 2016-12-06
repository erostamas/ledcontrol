#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>

#include "UdpInterface.h"
#include "Common.h"
#include "Logging.h"

int UdpInterface::bindToPort(int portno) {
    struct sockaddr_in serv_addr;
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
       LOG_ERROR << "UDP ERROR opening socket";
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    struct ifreq ifr;
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);
    ioctl(sockfd, SIOCGIFADDR, &ifr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = (((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr).s_addr;
    _wireIpAddress = std::string(inet_ntoa(serv_addr.sin_addr));
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
             LOG_ERROR << "UDP ERROR binding to port: " << portno;
    }
    LOG_INFO << "UDP bound to " << _wireIpAddress << ":" << portno;
    return sockfd;
}

void UdpInterface::run() {
    int sockfd;
    char buffer[256] = {0};
    struct sockaddr cli_addr;
    socklen_t clilen = sizeof(cli_addr);

    sockfd = bindToPort(50001);
    std::string incoming_message;
    while(1){
        memset(buffer, 0, sizeof(buffer));
        recvfrom(sockfd, buffer, 255, 0, &cli_addr, &clilen);
        LOG_DEBUG << "Recieved UDP message: " << buffer;
        incoming_message = buffer;
        if (incoming_message.size() > 0) {
            _messageQueue.push_back(incoming_message);
        }
    }
}

std::vector<std::string> UdpInterface::getMessages() {
    std::vector<std::string> temp_message_queue = _messageQueue;
    _messageQueue.clear();
    return temp_message_queue;
}