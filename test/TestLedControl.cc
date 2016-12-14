#define BOOST_LOG_DYN_LINK 1

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <thread>
#include <iostream>

#include "LedControl.h"

class TestLedControl : public LedControl {
public:
    TestLedControl() {
        std::cout << std::endl << "********** " << boost::unit_test::framework::current_test_case().p_name << " **********" << std::endl;       
    }
};

BOOST_FIXTURE_TEST_SUITE(ledcontrol_test_suite, TestLedControl)

BOOST_AUTO_TEST_CASE(test_setcolor) {
    setColor(0, 0, 0);
    BOOST_CHECK_EQUAL(_rgbColor._red, 0);
    BOOST_CHECK_EQUAL(_rgbColor._green, 0);
    BOOST_CHECK_EQUAL(_rgbColor._blue, 0);
}


BOOST_AUTO_TEST_SUITE_END()