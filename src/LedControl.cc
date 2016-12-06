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
    const char sep = ' ';
    std::vector<std::string> split_message = Utils::split(message, sep);
    if (split_message[0] == "setcolor") {
        // TODO: exception handling
        _red = std::stoul(split_message[1]);
        _green = std::stoul(split_message[2]);
        _blue = std::stoul(split_message[3]);
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


