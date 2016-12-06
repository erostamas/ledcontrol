#include "HSVColor.h"

void HSVColor::setColor(double hue, double saturation, double value) {
    _hue = hue;
    _saturation = saturation;
    _value = value;
}

std::string HSVColor::toString() {
    return std::to_string(_hue) + " " + std::to_string(_saturation) + " " + std::to_string(_value);
}