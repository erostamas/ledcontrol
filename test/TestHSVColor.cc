#define BOOST_LOG_DYN_LINK 1

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <thread>
#include <iostream>

#include "HSVColor.h"

class Fixture {
public:
    Fixture() {
        std::cout << std::endl << "********** " << boost::unit_test::framework::current_test_case().p_name << " **********" << std::endl;       
    }
    
    void checkHSV2RGB(unsigned red, unsigned green, unsigned blue, double hue, double saturation, double value) {
        RGBColor rgb;
        HSVColor hsv(hue, saturation, value);
        hsv.convertToRGB(rgb);
        BOOST_CHECK_EQUAL(red, rgb._red);
        BOOST_CHECK_EQUAL(green, rgb._green);
        BOOST_CHECK_EQUAL(blue, rgb._blue);
    }

};

BOOST_FIXTURE_TEST_SUITE(hsvcolor_test_suite, Fixture)

BOOST_AUTO_TEST_CASE(test_black) {
    checkHSV2RGB(0, 0, 0, 0, 0, 0);
}

BOOST_AUTO_TEST_CASE(test_white) {
    checkHSV2RGB(255, 255, 255, 0, 0, 1);
}

BOOST_AUTO_TEST_CASE(test_red) {
    checkHSV2RGB(255, 0, 0, 0, 1, 1);
}

BOOST_AUTO_TEST_CASE(test_lime) {
    checkHSV2RGB(0, 255, 0, 120, 1, 1);
}

BOOST_AUTO_TEST_CASE(test_blue) {
    checkHSV2RGB(0, 0, 255, 240, 1, 1);
}

BOOST_AUTO_TEST_CASE(test_yellow) {
    checkHSV2RGB(255, 255, 0, 60, 1, 1);
}

BOOST_AUTO_TEST_CASE(test_cyan) {
    checkHSV2RGB(0, 255, 255, 180, 1, 1);
}

BOOST_AUTO_TEST_CASE(test_magenta) {
    checkHSV2RGB(255, 0, 255, 300, 1, 1);
}

BOOST_AUTO_TEST_CASE(test_silver) {
    checkHSV2RGB(192, 192, 192, 0, 0, 192.0 / 255);
}

BOOST_AUTO_TEST_CASE(test_gray) {
    checkHSV2RGB(128, 128, 128, 0, 0, 128.0 / 255);
}

BOOST_AUTO_TEST_CASE(test_maroon) {
    checkHSV2RGB(128, 0, 0, 0, 1, 128.0 / 255);
}

BOOST_AUTO_TEST_CASE(test_olive) {
    checkHSV2RGB(128, 128, 0, 60, 1, 128.0 / 255);
}

BOOST_AUTO_TEST_CASE(test_green) {
    checkHSV2RGB(0, 128, 0, 120, 1, 128.0 / 255);
}

BOOST_AUTO_TEST_CASE(test_purple) {
    checkHSV2RGB(128, 0, 128, 300, 1, 128.0 / 255);
}

BOOST_AUTO_TEST_CASE(test_teal) {
    checkHSV2RGB(0, 128, 128, 180, 1, 128.0 / 255);
}

BOOST_AUTO_TEST_CASE(test_navy) {
    checkHSV2RGB(0, 0, 128, 240, 1, 128.0 / 255);
}

BOOST_AUTO_TEST_SUITE_END()