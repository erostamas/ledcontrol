#include "OutputControl.h"

#include "erostamas/Logging.h"
#include "RedisHandler.h"

OutputControl::OutputControl() {}

bool OutputControl::setColor(unsigned red, unsigned green, unsigned blue) {
    if ((red < 256) && (green < 256) && (blue < 256)) {
        _rgbColor.setColor(red, green, blue);
        _rgbColor.convertToHSV(_hsvColor);
        try {
            RedisHandler redis;
            redis.updateColor(red, green, blue);
        } catch (...) {
            LOG_ERROR << "[OutputControl] Failed to write to redis";
        }
        //softPwmWrite(7, _rgbColor._red);
        //softPwmWrite(8, _rgbColor._green);
        //softPwmWrite(9, _rgbColor._blue);
        return true;
    }
    return false;
}

bool OutputControl::setIntensity(unsigned intensity) {
    if (intensity < 101) {
        _hsvColor.setIntensity(intensity);
        _hsvColor.convertToRGB(_rgbColor);
        try {
            RedisHandler redis;
            redis.updateColor(_rgbColor._red, _rgbColor._green, _rgbColor._blue);
        } catch (...) {
            LOG_ERROR << "[OutputControl] Failed to write to redis";
        }
        //softPwmWrite(7, _rgbColor._red);
        //softPwmWrite(8, _rgbColor._green);
        //softPwmWrite(9, _rgbColor._blue);
        return true;
    }
    return false;
}

bool OutputControl::setColor(std::string red, std::string green, std::string blue) {
    try {
        return setColor(std::stoul(red), std::stoul(green), std::stoul(blue));
    } catch (...) {
        LOG_ERROR << "Exception during setting color: " << red << " " << green  << " " << blue;
        return false;
    }
}

bool OutputControl::setIntensity(std::string intensity) {
    try {
        return setIntensity(std::stoul(intensity));
    } catch (...) {
        LOG_ERROR << "Exception during setting intensity: " << intensity;
        return false;
    }
}