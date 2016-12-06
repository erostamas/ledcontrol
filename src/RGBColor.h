#pragma once

#include <string>
#include <memory>

#include "HSVColor.h"

class RGBColor {
public:
    RGBColor() {}
    RGBColor(unsigned red, unsigned green, unsigned blue) : _red(red), _green(green), _blue(blue) {}
    void setColor(unsigned red, unsigned green, unsigned blue);
    std::shared_ptr<HSVColor> convertToHSV();
    std::string toString();

    unsigned _red = 0;
    unsigned _green = 0;
    unsigned _blue = 0;
};