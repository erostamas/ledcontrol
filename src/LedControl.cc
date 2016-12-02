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

LedControl::LedControl(UdpInterface* udpInterface, UnixDomainSocketInterface* unixInterface) :
    _udpInterface(udpInterface),
    _unixInterface(unixInterface) {
}

LedControl::~LedControl() {
    
}

void LedControl::run() {
    while (!stopControlRequested) {
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
    if (message.substr(0, 8) == "setcolor") {
        // TODO: exception handling
        const char sep = ' ';
        std::vector<std::string> colors = Utils::split(message.substr(8), sep);
        _red = std::stoul(colors[0]);
        _green = std::stoul(colors[1]);
        _blue = std::stoul(colors[2]);
    }
}

void LedControl::writeXML() {
    std::ofstream dataxmlfile;
    dataxmlfile.open ("/var/www/html/data.xml");
    dataxmlfile << "<?xml version=\"1.0\"?>";
    dataxmlfile << "<colordata>\n";
    dataxmlfile << "<red>" << _red << "</red>\n";
    dataxmlfile << "<green>" << _green << "</green>\n";
    dataxmlfile << "<blue>" << _blue << "</blue>\n";
    dataxmlfile << "</colordata>\n";
    dataxmlfile.close();
}

void LedControl::printState() {
    std::system("clear");
    std::cout << "Connection state: \n";
              /* if (_tcpInterface->_connected) {
                  std::cout << "Connected" << "\n";
              } else {
                  std::cout << "Disconnected" << "\n";
              } */
    std::cout << "RED:   " << _red << "\n"
              << "GREEN: " << _green << "\n"
              << "BLUE:  " << _blue << std::endl;
}


