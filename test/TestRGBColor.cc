#define BOOST_LOG_DYN_LINK 1

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <thread>
#include <iostream>

#include "RGBColor.h"

class Fixture {
public:
    Fixture() {
        std::cout << std::endl << "********** " << boost::unit_test::framework::current_test_case().p_name << " **********" << std::endl;       
    }
    
    void checkRGB2HSV(unsigned red, unsigned green, unsigned blue, double hue, double saturation, double value) {
        RGBColor rgb(red, green, blue);
        HSVColor hsv;
        rgb.convertToHSV(hsv);
        BOOST_CHECK_EQUAL(hue, hsv._hue);
        BOOST_CHECK_EQUAL(saturation, hsv._saturation);
        BOOST_CHECK_EQUAL(value, hsv._value);
    }

};

BOOST_FIXTURE_TEST_SUITE(rgbcolor_test_suite, Fixture)

BOOST_AUTO_TEST_CASE(test_black) {
    checkRGB2HSV(0, 0, 0, 0, 0, 0);
}

BOOST_AUTO_TEST_CASE(test_white) {
    checkRGB2HSV(255, 255, 255, 0, 0, 1);
}

BOOST_AUTO_TEST_CASE(test_red) {
    checkRGB2HSV(255, 0, 0, 0, 1, 1);
}

BOOST_AUTO_TEST_CASE(test_lime) {
    checkRGB2HSV(0, 255, 0, 120, 1, 1);
}

BOOST_AUTO_TEST_CASE(test_blue) {
    checkRGB2HSV(0, 0, 255, 240, 1, 1);
}

BOOST_AUTO_TEST_CASE(test_yellow) {
    checkRGB2HSV(255, 255, 0, 60, 1, 1);
}

BOOST_AUTO_TEST_CASE(test_cyan) {
    checkRGB2HSV(0, 255, 255, 180, 1, 1);
}

BOOST_AUTO_TEST_CASE(test_magenta) {
    checkRGB2HSV(255, 0, 255, 300, 1, 1);
}

BOOST_AUTO_TEST_CASE(test_silver) {
    checkRGB2HSV(192, 192, 192, 0, 0, 192.0 / 255);
}

BOOST_AUTO_TEST_CASE(test_gray) {
    checkRGB2HSV(128, 128, 128, 0, 0, 128.0 / 255);
}

BOOST_AUTO_TEST_CASE(test_maroon) {
    checkRGB2HSV(128, 0, 0, 0, 1, 128.0 / 255);
}

BOOST_AUTO_TEST_CASE(test_olive) {
    checkRGB2HSV(128, 128, 0, 60, 1, 128.0 / 255);
}

BOOST_AUTO_TEST_CASE(test_green) {
    checkRGB2HSV(0, 128, 0, 120, 1, 128.0 / 255);
}

BOOST_AUTO_TEST_CASE(test_purple) {
    checkRGB2HSV(128, 0, 128, 300, 1, 128.0 / 255);
}

BOOST_AUTO_TEST_CASE(test_teal) {
    checkRGB2HSV(0, 128, 128, 180, 1, 128.0 / 255);
}

BOOST_AUTO_TEST_CASE(test_navy) {
    checkRGB2HSV(0, 0, 128, 240, 1, 128.0 / 255);
}

BOOST_AUTO_TEST_SUITE_END()