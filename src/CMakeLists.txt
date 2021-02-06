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
    et_command_processor
    et_config)

INSTALL(TARGETS ledcontrol
	DESTINATION /usr/bin/
	PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

SET(CPACK_PACKAGE_VERSION_MAJOR 0)
SET(CPACK_PACKAGE_VERSION_MINOR 0)
SET(CPACK_PACKAGE_VERSION_PATCH 1)
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "TAMAS EROS") #required
SET(CPACK_PACKAGE_FILE_NAME ledcontrol)
#SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-log-dev, libboost-system-dev, libboost-thread-dev")
INCLUDE(CPack)
