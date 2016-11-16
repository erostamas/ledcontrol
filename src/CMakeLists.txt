add_library(ledcontrol_library STATIC
    TcpInterface.cc
    UnixDomainSocketInterface.cc
    LedControl.cc
    Logging.cc
)
target_link_libraries(ledcontrol_library
    boost_log
    boost_thread
    boost_system)

add_executable(ledcontrol
    main.cc)

target_link_libraries(ledcontrol
    ledcontrol_library)

