#include <gmock/gmock.h>
#include <boost/filesystem.hpp>
#include <thread>
#include <iostream>

#include "LedControl.h"

class TestLedControl : public ::testing::Test, public LedControl {

};
TEST_F(TestLedControl, test_setcolor_integer) {
    ASSERT_TRUE(setColor(1, 2, 3));
    EXPECT_EQ(_rgbColor._red, 1);
    EXPECT_EQ(_rgbColor._green, 2);
    EXPECT_EQ(_rgbColor._blue, 3);
}

TEST_F(TestLedControl, test_setcolor_integer_out_of_range) {
    EXPECT_EQ(setColor(1, 256, 3), false);
    EXPECT_EQ(_rgbColor._red, 0);
    EXPECT_EQ(_rgbColor._green, 0);
    EXPECT_EQ(_rgbColor._blue, 0);
}

TEST_F(TestLedControl, test_setcolor_string) {
    ASSERT_TRUE(setColor("1", "2", "3"));
    EXPECT_EQ(_rgbColor._red, 1);
    EXPECT_EQ(_rgbColor._green, 2);
    EXPECT_EQ(_rgbColor._blue, 3);
}

TEST_F(TestLedControl, test_setcolor_string_out_of_range) {
    EXPECT_EQ(setColor("1", "256", "3"), false);
    EXPECT_EQ(_rgbColor._red, 0);
    EXPECT_EQ(_rgbColor._green, 0);
    EXPECT_EQ(_rgbColor._blue, 0);
}

TEST_F(TestLedControl, test_setcolor_string_invalid_number) {
    EXPECT_EQ(setColor("1", "blabla", "3"), false);
    EXPECT_EQ(_rgbColor._red, 0);
    EXPECT_EQ(_rgbColor._green, 0);
    EXPECT_EQ(_rgbColor._blue, 0);
}

