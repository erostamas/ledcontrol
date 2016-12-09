#pragma once

#include <string>

#include "HSVColor.h"
class HSVColor;

class RGBColor {
public:
    RGBColor() {}
    RGBColor(unsigned red, unsigned green, unsigned blue) : _red(red), _green(green), _blue(blue) {}
    void setColor(unsigned red, unsigned green, unsigned blue);
    void setRed(unsigned red);
    void setGreen(unsigned green);
    void setBlue(unsigned blue);
    void convertToHSV(HSVColor& hsv);
    std::string toString();

    unsigned _red = 0;
    unsigned _green = 0;
    unsigned _blue = 0;
};