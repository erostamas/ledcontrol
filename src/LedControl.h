#pragma once

#include "UdpInterface.h"
#include "UnixDomainSocketInterface.h"
#include "RGBColor.h"
#include "HSVColor.h"

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
    void setRed(unsigned red);
    void setGreen(unsigned green);
    void setBlue(unsigned blue);
    void setIntensity(unsigned intensity);

private:
    UdpInterface* _udpInterface;
    UnixDomainSocketInterface* _unixInterface;
    bool stopControlRequested = false;
    RGBColor _rgbColor;
    HSVColor _hsvColor;
};