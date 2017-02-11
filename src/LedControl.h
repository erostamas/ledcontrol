#pragma once

#include "UdpInterface.h"
#include "UnixDomainSocketInterface.h"
#include "RGBColor.h"
#include "HSVColor.h"

enum class MODE {
    MANUAL,
    ANIMATION
};

class LedControl {
public:
    LedControl();
    LedControl(UdpInterface*);
    LedControl(UdpInterface*, UnixDomainSocketInterface*);
    ~LedControl();

	void run();
    void processCommands();
    void processCommand(std::string message);
    void writeXML();
    void printState();
    bool setColor(unsigned red, unsigned green, unsigned blue);
    bool setRed(unsigned red);
    bool setGreen(unsigned green);
    bool setBlue(unsigned blue);
    bool setIntensity(unsigned intensity);
    bool setColor(std::string red, std::string green, std::string blue);
    bool setRed(std::string red);
    bool setGreen(std::string green);
    bool setBlue(std::string blue);
    bool setIntensity(std::string intensity);

protected:
    MODE _mode = MODE::MANUAL;
    UdpInterface* _udpInterface = nullptr;
    UnixDomainSocketInterface* _unixInterface = nullptr;
    bool _stopControlRequested = false;
    RGBColor _rgbColor;
    HSVColor _hsvColor;
};