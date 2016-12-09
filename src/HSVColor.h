#pragma once

#include <string>

#include "RGBColor.h"
class RGBColor;

class HSVColor{
public:
    HSVColor() {}
    HSVColor(double hue, double saturation, double value) : _hue(hue), _saturation(saturation), _value(value) {}
    void setColor(double hue, double saturation, double value);
    void setIntensity(unsigned intensity);
    void convertToRGB(RGBColor& rgb);
    std::string toString();

    double _hue = 0;
    double _saturation = 0;
    double _value = 0;
};