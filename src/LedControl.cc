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
#include "erostamas/Logging.h"
#include "RedisHandler.h"
#include "StringCommandAdapter.h"
#include "erostamas/UdpMessageReceiver.h"

//#include <wiringPi.h>
//#include <softPwm.h>

LedControl::LedControl() {
    std::unique_ptr<StringCommandAdapter> adapter(new StringCommandAdapter(_outputControl));
    std::unique_ptr<UdpMessageReceiver> receiver(new UdpMessageReceiver(50001));
    adapter->registerMessageReceiver(std::move(receiver));
    _commandProcessor.registerCommandAdapter(std::move(adapter));
    _commandProcessor.processCommands();
}

LedControl::~LedControl() {
    
}

void LedControl::run() {
    //wiringPiSetup();
    //softPwmCreate(7, 0, 255);
    //softPwmCreate(8, 0, 255);
    //softPwmCreate(9, 0, 255);
    //pinMode (8, OUTPUT);

    while (!_stopControlRequested) {
        //digitalWrite (8, HIGH) ; delay (500) ;
        //digitalWrite (8,  LOW) ; delay (500) ;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        _commandProcessor.processCommands();
        //printState();
        //writeXML();
    }
    LOG_DEBUG << "Stopping ledcontrol" << std::endl;
}

void LedControl::writeXML() {
    //std::ofstream dataxmlfile;
    //dataxmlfile.open ("/var/www/html/data.xml");
    //dataxmlfile << "<?xml version=\"1.0\"?>";
    //dataxmlfile << "<colordata>\n";
    //dataxmlfile << "<red>" << _rgbColor._red << "</red>\n";
    //dataxmlfile << "<green>" << _rgbColor._green << "</green>\n";
    //dataxmlfile << "<blue>" << _rgbColor._blue << "</blue>\n";
    //dataxmlfile << "</colordata>\n";
    //dataxmlfile.close();
}

void LedControl::printState() {
    //std::system("clear");
    //std::cout << "RED:        " << _rgbColor._red << "\n"
    //          << "GREEN:      " << _rgbColor._green << "\n"
    //          << "BLUE:       " << _rgbColor._blue << "\n\n"
    //          << "HUE:        " << _hsvColor._hue << "\n"
    //          << "SATURATION: " << _hsvColor._saturation << "\n"
    //          << "VALUE:      " << _hsvColor._value << std::endl;
}
