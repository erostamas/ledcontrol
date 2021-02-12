#define _GLIBCXX_USE_NANOSLEEP

#include <algorithm>
#include <thread>
#include <iostream>
#include <tgmath.h>
#include <fstream>
#include <iomanip>

#include "LedControl.h"
#include "Utils.h"
#include "erostamas/Logging.h"
#include "StringCommandAdapter.h"
#include "erostamas/UdpMessageReceiver.h"

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
    while (!_stopControlRequested) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        _commandProcessor.processCommands();
    }
    LOG_DEBUG << "Stopping ledcontrol" << std::endl;
}
