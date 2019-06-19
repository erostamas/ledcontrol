add_library(ledcontrol_library STATIC
    UdpInterface.cc
    UnixDomainSocketInterface.cc
    LedControl.cc
    Logging.cc
    RGBColor.cc
    HSVColor.cc
)
target_link_libraries(ledcontrol_library
    boost_log
    boost_thread
    boost_system
    cpp_redis
    tacopie)

add_executable(ledcontrol
    main.cc)

target_link_libraries(ledcontrol
    ledcontrol_library)

