#include <cmath>

#include "HSVColor.h"

void HSVColor::setColor(double hue, double saturation, double value) {
    _hue = hue;
    _saturation = saturation;
    _value = value;
}

void HSVColor::convertToRGB(RGBColor& rgb) {
    double c = _value * _saturation;
    double x = c * (1 - std::abs(std::fmod((_hue / 60), 2) - 1));
    double m = _value - c;

    double r_prime = 0;
    double g_prime = 0;
    double b_prime = 0;

    if ((_hue >= 0) && (_hue < 60)) {
        r_prime = c;
        g_prime = x;
        b_prime = 0;
    } else if ((_hue >= 60) && (_hue < 120)) {
        r_prime = x;
        g_prime = c;
        b_prime = 0;
    } else if ((_hue >= 120) && (_hue < 180)) {
        r_prime = 0;
        g_prime = c;
        b_prime = x;
    } else if ((_hue >= 180) && (_hue < 240)) {
        r_prime = 0;
        g_prime = x;
        b_prime = c;
    } else if ((_hue >= 240) && (_hue < 300)) {
        r_prime = x;
        g_prime = 0;
        b_prime = c;
    } else if ((_hue >= 300) && (_hue < 360)) {
        r_prime = c;
        g_prime = 0;
        b_prime = x;
    }
    
    rgb._red = unsigned((r_prime + m) * 255);
    rgb._green = unsigned((g_prime + m) * 255);
    rgb._blue = unsigned((b_prime + m) * 255);
}

std::string HSVColor::toString() {
    return std::to_string(_hue) + " " + std::to_string(_saturation) + " " + std::to_string(_value);
}