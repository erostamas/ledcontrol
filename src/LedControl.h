#pragma once

#include "UdpInterface.h"
#include "UnixDomainSocketInterface.h"

enum class MODE {
    MANUAL,
    AUTO
};

class LedControl {
public:
    LedControl(UdpInterface*, UnixDomainSocketInterface*);
    ~LedControl();

	void run();
    void processCommands();
    void processCommand(std::string message);
    void writeXML();
    void printState();
    void setColor(unsigned red, unsigned green, unsigned blue);

private:
    UdpInterface* _udpInterface;
    UnixDomainSocketInterface* _unixInterface;
    bool stopControlRequested = false;
    unsigned _red = 0;
    unsigned _green = 0;
    unsigned _blue = 0;
    unsigned _hue = 0;
    unsigned _saturation = 0;
    unsigned _value = 0;
};