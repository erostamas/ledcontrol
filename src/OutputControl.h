#pragma once

#include "RGBColor.h"
#include "HSVColor.h"

class OutputControl {
public:
    OutputControl();

    bool setColor(unsigned red, unsigned green, unsigned blue);
    bool setIntensity(unsigned intensity);

    bool setColor(std::string red, std::string green, std::string blue);
    bool setIntensity(std::string intensity);

private:
    RGBColor _rgbColor;
    HSVColor _hsvColor;
    std::string _redisIpAddress = "192.168.1.247";
};
