#include <gmock/gmock.h>
#include <boost/filesystem.hpp>
#include <thread>
#include <iostream>

#include "RGBColor.h"

class TestRGBColor : public testing::Test {
public:
    TestRGBColor() {
    }
    
    void checkRGB2HSV(unsigned red, unsigned green, unsigned blue, double hue, double saturation, double value) {
        RGBColor rgb(red, green, blue);
        HSVColor hsv;
        rgb.convertToHSV(hsv);
        EXPECT_EQ(hue, hsv._hue);
        EXPECT_EQ(saturation, hsv._saturation);
        EXPECT_EQ(value, hsv._value);
    }

};

TEST_F(TestRGBColor, test_black) {
    checkRGB2HSV(0, 0, 0, 0, 0, 0);
}

TEST_F(TestRGBColor, test_white) {
    checkRGB2HSV(255, 255, 255, 0, 0, 1);
}

TEST_F(TestRGBColor, test_red) {
    checkRGB2HSV(255, 0, 0, 0, 1, 1);
}

TEST_F(TestRGBColor, test_lime) {
    checkRGB2HSV(0, 255, 0, 120, 1, 1);
}

TEST_F(TestRGBColor, test_blue) {
    checkRGB2HSV(0, 0, 255, 240, 1, 1);
}

TEST_F(TestRGBColor, test_yellow) {
    checkRGB2HSV(255, 255, 0, 60, 1, 1);
}

TEST_F(TestRGBColor, test_cyan) {
    checkRGB2HSV(0, 255, 255, 180, 1, 1);
}

TEST_F(TestRGBColor, test_magenta) {
    checkRGB2HSV(255, 0, 255, 300, 1, 1);
}

TEST_F(TestRGBColor, test_silver) {
    checkRGB2HSV(192, 192, 192, 0, 0, 192.0 / 255);
}

TEST_F(TestRGBColor, test_gray) {
    checkRGB2HSV(128, 128, 128, 0, 0, 128.0 / 255);
}

TEST_F(TestRGBColor, test_maroon) {
    checkRGB2HSV(128, 0, 0, 0, 1, 128.0 / 255);
}

TEST_F(TestRGBColor, test_olive) {
    checkRGB2HSV(128, 128, 0, 60, 1, 128.0 / 255);
}

TEST_F(TestRGBColor, test_green) {
    checkRGB2HSV(0, 128, 0, 120, 1, 128.0 / 255);
}

TEST_F(TestRGBColor, test_purple) {
    checkRGB2HSV(128, 0, 128, 300, 1, 128.0 / 255);
}

TEST_F(TestRGBColor, test_teal) {
    checkRGB2HSV(0, 128, 128, 180, 1, 128.0 / 255);
}

TEST_F(TestRGBColor, test_navy) {
    checkRGB2HSV(0, 0, 128, 240, 1, 128.0 / 255);
}
