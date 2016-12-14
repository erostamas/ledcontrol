#define _GLIBCXX_USE_NANOSLEEP

#include <algorithm>
#include <thread>
#include <iostream>
#include <tgmath.h>
#include <fstream>
#include <iomanip>

#include "LedControl.h"
#include "Common.h"
#include "Utils.h"
#include "Logging.h"

#include <wiringPi.h>

LedControl::LedControl(UdpInterface* udpInterface, UnixDomainSocketInterface* unixInterface) :
    _udpInterface(udpInterface),
    _unixInterface(unixInterface) {
}

LedControl::~LedControl() {
    
}

void LedControl::run() {
    //wiringPiSetup ();
    //pinMode (0, OUTPUT);
    while (!_stopControlRequested) {
        //digitalWrite (0, HIGH) ; delay (500) ;
        //digitalWrite (0,  LOW) ; delay (500) ;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        processCommands();
        printState();
        writeXML();
    }
}

void LedControl::processCommands() {
    std::vector<std::string> commandqueue = _udpInterface->getMessages();
    while (commandqueue.size()) {
        processCommand(commandqueue[0]);
        commandqueue.erase(commandqueue.begin());
    }
    commandqueue = _unixInterface->getMessages();
    while (commandqueue.size()) {
        processCommand(commandqueue[0]);
        commandqueue.erase(commandqueue.begin());
    }
}

void LedControl::processCommand(std::string message) {
    const char sep = ' ';
    std::vector<std::string> split_message = Utils::split(message, sep);
    if (split_message[0] == "setcolor") {
        setColor(split_message[1], split_message[2], split_message[3]);
    } else if (split_message[0] == "setred") {
        setRed(split_message[1]);
    } else if (split_message[0] == "setgreen") {
        setGreen(split_message[1]);
    } else if (split_message[0] == "setblue") {
        setBlue(split_message[1]);
    } else if (split_message[0] == "setintensity") {
        setIntensity(split_message[1]);
    } else if (split_message[0] == "setloglevel") {
        set_loglevel(split_message[1]);
    }
}

void LedControl::writeXML() {
    std::ofstream dataxmlfile;
    dataxmlfile.open ("/var/www/html/data.xml");
    dataxmlfile << "<?xml version=\"1.0\"?>";
    dataxmlfile << "<colordata>\n";
    dataxmlfile << "<red>" << _rgbColor._red << "</red>\n";
    dataxmlfile << "<green>" << _rgbColor._green << "</green>\n";
    dataxmlfile << "<blue>" << _rgbColor._blue << "</blue>\n";
    dataxmlfile << "</colordata>\n";
    dataxmlfile.close();
}

void LedControl::printState() {
    std::system("clear");
    std::cout << "RED:        " << _rgbColor._red << "\n"
              << "GREEN:      " << _rgbColor._green << "\n"
              << "BLUE:       " << _rgbColor._blue << "\n\n"
              << "HUE:        " << _hsvColor._hue << "\n"
              << "SATURATION: " << _hsvColor._saturation << "\n"
              << "VALUE:      " << _hsvColor._value << std::endl;
}

bool LedControl::setColor(unsigned red, unsigned green, unsigned blue) {
    if ((red < 256) && (green < 256) && (blue < 256)) {
        _rgbColor.setColor(red, green, blue);
        _rgbColor.convertToHSV(_hsvColor);
        return true;
    }
    return false;
}

bool LedControl::setRed(unsigned red) {
    if (red < 256) {
        _rgbColor.setRed(red);
        _rgbColor.convertToHSV(_hsvColor);
        return true;
    }
    return false;
}

bool LedControl::setGreen(unsigned green) {
    if (green < 256) {
        _rgbColor.setGreen(green);
        _rgbColor.convertToHSV(_hsvColor);
        return true;
    }
    return false;
}

bool LedControl::setBlue(unsigned blue) {
    if (blue < 256) {
        _rgbColor.setBlue(blue);
        _rgbColor.convertToHSV(_hsvColor);
        return true;
    }
    return false;
}

bool LedControl::setIntensity(unsigned intensity) {
    if (intensity < 101) {
        _hsvColor.setIntensity(intensity);
        _hsvColor.convertToRGB(_rgbColor);
        return true;
    }
    return false;
}

bool LedControl::setColor(std::string red, std::string green, std::string blue) {
    try {
        return setColor(std::stoul(red), std::stoul(green), std::stoul(blue));
    } catch (...) {
        LOG_ERROR << "Exception during setting color: " << red << " " << green  << " " << blue;
        return false;
    }
}

bool LedControl::setRed(std::string red) {
    try {
        return setRed(std::stoul(red));
    } catch (...) {
        LOG_ERROR << "Exception during setting red: " << red;
        return false;
    }
}

bool LedControl::setGreen(std::string green) {
    try {
        return setGreen(std::stoul(green));
    } catch (...) {
        LOG_ERROR << "Exception during setting green: " << green;
        return false;
    }
}

bool LedControl::setBlue(std::string blue) {
    try {
        return setBlue(std::stoul(blue));
    } catch (...) {
        LOG_ERROR << "Exception during setting blue: " << blue;
        return false;
    }
}

bool LedControl::setIntensity(std::string intensity) {
    try {
        return setIntensity(std::stoul(intensity));
    } catch (...) {
        LOG_ERROR << "Exception during setting intensity: " << intensity;
        return false;
    }
}
