#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/un.h>
#include <iostream>
#include <ctime>

#include "UnixDomainSocketInterface.h"
#include "Common.h"
#include "LedControl.h"
#include "Logging.h"

int UnixDomainSocketInterface::bindToPath(std::string path) {

    int sockfd;
    struct sockaddr_un server_address;

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd < 0) {
       LOG_ERROR << "Unix Domain Socket ERROR opening socket";
    }

    bzero((char *) &server_address, sizeof(server_address));
    server_address.sun_family = AF_UNIX;
    strncpy(server_address.sun_path, path.c_str(), path.length());

    if (bind(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        LOG_ERROR << "Unix Domain Socket ERROR binding to path: " << path;
    }
    return sockfd;
}

void UnixDomainSocketInterface::listenForConnection(int sockfd) {
    listen(sockfd,5);
    LOG_DEBUG << "Unix Domain Socket listening";
}

int UnixDomainSocketInterface::acceptConnection(int sockfd) {
    LOG_DEBUG << "Unix Domain Socket waiting for client connection...";
    int newsockfd = accept(sockfd, NULL, NULL);
    if (newsockfd < 0) {
        LOG_ERROR << "Unix Domain Socket ERROR when accepting client connection";
    }
    LOG_DEBUG << "Unix Domain Socket accepted client connection";
    return newsockfd;
}

void UnixDomainSocketInterface::run() {
    int sockfd = -1, n;
    char buffer[256];
    std::string incoming_message;
    _shouldExit = false;

    sockfd = bindToPath("/ledcontrol_files/ledcontrol_socket_file");
	while(!_shouldExit) {
        listenForConnection(sockfd);
        _connectedSocketFd = acceptConnection(sockfd);
        _connected = true;
        incoming_message = "";
        bzero(buffer,256);
        n = read(_connectedSocketFd,buffer,255);
        if (n < 0) {
            LOG_ERROR << "Unix Domain Socket ERROR reading from socket, closing socket";
            continue;
        }
        incoming_message = buffer;
        if (incoming_message.size() > 0) {
            LOG_DEBUG << "Recieved UNIX socket message: " << incoming_message;
            if (incoming_message == "stop") {
                _shouldExit = true;
            }
            _messageQueue.push_back(incoming_message);
        }
        close(_connectedSocketFd);
	}
    LOG_INFO << "Closing Unix socket connection...";
	
    close(sockfd);
}

std::vector<std::string> UnixDomainSocketInterface::getMessages() {
    std::vector<std::string> temp_message_queue = _messageQueue;
    _messageQueue.clear();
    return temp_message_queue;
}