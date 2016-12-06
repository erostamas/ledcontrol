#include <iostream>
#include <math.h>

#include "RGBColor.h"
#include "HSVColor.h"

void RGBColor::setColor(unsigned red, unsigned green, unsigned blue) {
    _red = red;
    _green = green;
    _blue = blue;
}

std::shared_ptr<HSVColor> RGBColor::convertToHSV() {
    
    double hue = 0;
    double saturation = 0;
    double value = 0;

    double r_prime = _red / 255.0;
    double g_prime = _green / 255.0;
    double b_prime = _blue / 255.0;
    
    double c_max = std::max(std::max(r_prime, g_prime), b_prime);
    double c_min = std::min(std::min(r_prime, g_prime), b_prime);
    double delta = c_max - c_min;

    std::cout << r_prime << std::endl;
    std::cout << g_prime << std::endl;
    std::cout << b_prime << std::endl;
    
    std::cout << c_max << std::endl;
    std::cout << c_min << std::endl;
    std::cout << delta << std::endl;

    if (delta == 0) {
        hue = 0;
    } else if (c_max == r_prime) {
        hue = 60 * fmod(((g_prime - b_prime) / delta), 6);
    } else if (c_max == g_prime) {
        hue = 60 * (((b_prime - r_prime) / delta) + 2);
    } else if (c_max == b_prime) {
        hue = 60 * (((r_prime - g_prime) / delta) + 4);
    }
    
    if (hue < 0) {
        hue = 360 + hue;
    }
    
    if (c_max == 0) {
        saturation = 0;
    } else {
        saturation = delta / c_max;
    }
    
    value = c_max;
    
    return std::make_shared<HSVColor>(hue, saturation, value);
}

std::string RGBColor::toString() {
    return std::to_string(_red) + " " + std::to_string(_green) + " " + std::to_string(_blue);
}