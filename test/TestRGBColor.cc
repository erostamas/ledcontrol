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

};

BOOST_FIXTURE_TEST_SUITE(rgbcolor_test_suite, Fixture)

BOOST_AUTO_TEST_CASE(test_run) {
    RGBColor rgb(128, 0, 128);
    std::cout << rgb.toString() << std::endl;
    std::cout << rgb.convertToHSV()->toString() << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()