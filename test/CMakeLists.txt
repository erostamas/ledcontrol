set (TESTNAME test_ledcontrol)  
include_directories(../src)

add_executable(${TESTNAME}
    TestMain.cc
    TestLedControl.cc
    TestRGBColor.cc
    TestHSVColor.cc)

target_link_libraries(${TESTNAME}
    ledcontrol_library
    boost_unit_test_framework
    boost_log
    boost_thread
    boost_system
    boost_filesystem)

add_test(${TESTNAME} ${CMAKE_CURRENT_BINARY_DIR}/${TESTNAME})