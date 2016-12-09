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
    while (!stopControlRequested) {
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
        // TODO: exception handling
        setColor(std::stoul(split_message[1]), std::stoul(split_message[2]), std::stoul(split_message[3]));
    } else if (split_message[0] == "setred") {
        // TODO: exception handling
        setRed(std::stoul(split_message[1]));
    } else if (split_message[0] == "setgreen") {
        // TODO: exception handling
        setGreen(std::stoul(split_message[1]));
    } else if (split_message[0] == "setblue") {
        // TODO: exception handling
        setBlue(std::stoul(split_message[1]));
    } else if (split_message[0] == "setloglevel") {
        // TODO: exception handling
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

void LedControl::setColor(unsigned red, unsigned green, unsigned blue) {
    _rgbColor.setColor(red, green, blue);
    _rgbColor.convertToHSV(_hsvColor);
}

void LedControl::setRed(unsigned red) {
    _rgbColor.setRed(red);
    _rgbColor.convertToHSV(_hsvColor);
}

void LedControl::setGreen(unsigned green) {
    _rgbColor.setGreen(green);
    _rgbColor.convertToHSV(_hsvColor);
}

void LedControl::setBlue(unsigned blue) {
    _rgbColor.setBlue(blue);
    _rgbColor.convertToHSV(_hsvColor);
}


