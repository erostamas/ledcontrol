link_directories(/usr/lib/erostamas/)

add_library(ledcontrol_library STATIC
    LedControl.cc
    RGBColor.cc
    HSVColor.cc
    OutputControl.cc
    StringCommandAdapter.cc
)

target_link_libraries(ledcontrol_library
    boost_log
    boost_thread
    boost_system
    cpp_redis
    tacopie
)

add_executable(ledcontrol
    main.cc)

target_link_libraries(ledcontrol
    ledcontrol_library
    et_logging
    et_command_processor)

INSTALL(TARGETS ledcontrol
	DESTINATION /usr/bin/
	PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
