#pragma once

#include "TcpInterface.h"
#include "UnixDomainSocketInterface.h"

enum class MODE {
    MANUAL,
    AUTO
};

class LedControl {
public:
    LedControl(TcpInterface*, UnixDomainSocketInterface*);
    ~LedControl();

	void run();
    void processCommands();
    void processCommand(std::string message);
    void writeXML();
    void printState();

private:
    TcpInterface* _tcpInterface;
    UnixDomainSocketInterface* _unixInterface;
    bool stopControlRequested = false;
    unsigned _red = 0;
    unsigned _green = 0;
    unsigned _blue = 0;
};