#include "OutputControl.h"

#include "erostamas/Logging.h"
#include "erostamas/Config.h"
#include "RedisHandler.h"

#include <wiringPi.h>
#include <softPwm.h>

OutputControl::OutputControl() {
    Config config("/ledcontrol_files/config.json");
    _redisIpAddress = config.get<std::string>("redis_ip_address", "192.168.1.246");
    _redPin = config.get<unsigned>("red_pin", DEFAULT_RED_PIN);
    _greenPin = config.get<unsigned>("green_pin", DEFAULT_GREEN_PIN);
    _bluePin = config.get<unsigned>("blue_pin", DEFAULT_BLUE_PIN);

    wiringPiSetup();
    pinMode (_redPin, OUTPUT);
    pinMode (_greenPin, OUTPUT);
    pinMode (_bluePin, OUTPUT);
    softPwmCreate(_redPin, 0, 100);
    softPwmCreate(_greenPin, 0, 100);
    softPwmCreate(_bluePin, 0, 100);
}

bool OutputControl::setColor(unsigned red, unsigned green, unsigned blue) {
    if ((red < 256) && (green < 256) && (blue < 256)) {
        _rgbColor.setColor(red, green, blue);
        _rgbColor.convertToHSV(_hsvColor);
        try {
            RedisHandler redis(_redisIpAddress);
            redis.updateColor(red, green, blue);
        } catch (...) {
            LOG_ERROR << "[OutputControl] Failed to write to redis";
        }
        LOG_DEBUG << "[OutputControl] Setting color to " << _rgbColor._red << " " << _rgbColor._green << " " << _rgbColor._blue;
        softPwmWrite(_redPin, int(_rgbColor._red / 255.0 * 100));
        softPwmWrite(_greenPin, int(_rgbColor._green / 255.0 * 100));
        softPwmWrite(_bluePin, int(_rgbColor._blue / 255.0 * 100));
        return true;
    }
    return false;
}

bool OutputControl::setIntensity(unsigned intensity) {
    if (intensity < 101) {
        _hsvColor.setIntensity(intensity);
        _hsvColor.convertToRGB(_rgbColor);
        try {
            RedisHandler redis(_redisIpAddress);
            redis.updateColor(_rgbColor._red, _rgbColor._green, _rgbColor._blue);
        } catch (...) {
            LOG_ERROR << "[OutputControl] Failed to write to redis";
        }
        LOG_DEBUG << "[OutputControl] Setting color to " << _rgbColor._red << " " << _rgbColor._green << " " << _rgbColor._blue;
        softPwmWrite(_redPin, int(_rgbColor._red / 255.0 * 100));
        softPwmWrite(_greenPin, int(_rgbColor._green / 255.0 * 100));
        softPwmWrite(_bluePin, int(_rgbColor._blue / 255.0 * 100));
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
