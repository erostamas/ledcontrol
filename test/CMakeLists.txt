set (TESTNAME test_ledcontrol)  
include_directories(../src)

add_executable(${TESTNAME}
    Test.cc
    TestHSVColor.cc
    TestRGBColor.cc
    TestLedControl.cc)

target_link_libraries(${TESTNAME}
    ledcontrol_library
    gmock
    gmock_main
    boost_log
    boost_thread
    boost_system
    boost_filesystem)

add_test(${TESTNAME} ${CMAKE_CURRENT_BINARY_DIR}/${TESTNAME})