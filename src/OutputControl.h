#pragma once

#include "RGBColor.h"
#include "HSVColor.h"

class OutputControl {
    static constexpr unsigned DEFAULT_RED_PIN = 8;
    static constexpr unsigned DEFAULT_GREEN_PIN = 9;
    static constexpr unsigned DEFAULT_BLUE_PIN = 7;

public:
    OutputControl();

    bool setColor(unsigned red, unsigned green, unsigned blue);
    bool setIntensity(unsigned intensity);

    bool setColor(std::string red, std::string green, std::string blue);
    bool setIntensity(std::string intensity);

private:
    unsigned _redPin = DEFAULT_RED_PIN;
    unsigned _greenPin = DEFAULT_GREEN_PIN;
    unsigned _bluePin = DEFAULT_BLUE_PIN;
    RGBColor _rgbColor;
    HSVColor _hsvColor;
    std::string _redisIpAddress;
};
