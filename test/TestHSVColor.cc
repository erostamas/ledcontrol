#include <gmock/gmock.h>
#include <boost/filesystem.hpp>
#include <thread>
#include <iostream>

#include "HSVColor.h"

class TestHSVColor : public ::testing::Test{
public:
    TestHSVColor() {
    }
    
    void checkHSV2RGB(unsigned red, unsigned green, unsigned blue, double hue, double saturation, double value) {
        RGBColor rgb;
        HSVColor hsv(hue, saturation, value);
        hsv.convertToRGB(rgb);
        EXPECT_EQ(red, rgb._red);
        EXPECT_EQ(green, rgb._green);
        EXPECT_EQ(blue, rgb._blue);
    }

};

TEST_F(TestHSVColor, test_black) {
    checkHSV2RGB(0, 0, 0, 0, 0, 0);
}

TEST_F(TestHSVColor, test_white) {
    checkHSV2RGB(255, 255, 255, 0, 0, 1);
}

TEST_F(TestHSVColor, test_red) {
    checkHSV2RGB(255, 0, 0, 0, 1, 1);
}

TEST_F(TestHSVColor, test_lime) {
    checkHSV2RGB(0, 255, 0, 120, 1, 1);
}

TEST_F(TestHSVColor, test_blue) {
    checkHSV2RGB(0, 0, 255, 240, 1, 1);
}

TEST_F(TestHSVColor, test_yellow) {
    checkHSV2RGB(255, 255, 0, 60, 1, 1);
}

TEST_F(TestHSVColor, test_cyan) {
    checkHSV2RGB(0, 255, 255, 180, 1, 1);
}

TEST_F(TestHSVColor, test_magenta) {
    checkHSV2RGB(255, 0, 255, 300, 1, 1);
}

TEST_F(TestHSVColor, test_silver) {
    checkHSV2RGB(192, 192, 192, 0, 0, 192.0 / 255);
}

TEST_F(TestHSVColor, test_gray) {
    checkHSV2RGB(128, 128, 128, 0, 0, 128.0 / 255);
}

TEST_F(TestHSVColor, test_maroon) {
    checkHSV2RGB(128, 0, 0, 0, 1, 128.0 / 255);
}

TEST_F(TestHSVColor, test_olive) {
    checkHSV2RGB(128, 128, 0, 60, 1, 128.0 / 255);
}

TEST_F(TestHSVColor, test_green) {
    checkHSV2RGB(0, 128, 0, 120, 1, 128.0 / 255);
}

TEST_F(TestHSVColor, test_purple) {
    checkHSV2RGB(128, 0, 128, 300, 1, 128.0 / 255);
}

TEST_F(TestHSVColor, test_teal) {
    checkHSV2RGB(0, 128, 128, 180, 1, 128.0 / 255);
}

TEST_F(TestHSVColor, test_navy) {
    checkHSV2RGB(0, 0, 128, 240, 1, 128.0 / 255);
}
