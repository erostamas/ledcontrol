#pragma once

#include "erostamas/CommandProcessor.h"
#include "OutputControl.h"

enum class MODE {
    MANUAL,
    ANIMATION
};

class LedControl {
public:
    LedControl();
    ~LedControl();

	void run();
    void writeXML();
    void printState();

protected:
    MODE _mode = MODE::MANUAL;
    CommandProcessor _commandProcessor;
    bool _stopControlRequested = false;
    OutputControl _outputControl;
    
};