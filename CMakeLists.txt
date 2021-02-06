cmake_minimum_required(VERSION 3.0)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})

# compiler and linker flags
if ((NOT CMAKE_CXX_FLAGS) OR (CMAKE_CXX_FLAGS MATCHES "^[ \t]*$"))
  set(CXX11_FLAG "-std=c++11")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.2")
      set(CXX11_FLAG "-std=c++0x")
  endif()
  set(CMAKE_CXX_FLAGS "-O3 -g ${CXX11_FLAG} -Werror -Wall -DBOOST_LOG_DYN_LINK -DNDEBUG -Wno-unused-result -lpthread -lwiringPi")
  if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    message("Coverage mode selected")
      set(CMAKE_CXX_FLAGS "-O0 -g ${CXX11_FLAG} -Werror -Wall -DBOOST_LOG_DYN_LINK -fprofile-arcs -ftest-coverage -lpthread -lwiringPi")
  endif()
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
      set(CMAKE_CXX_FLAGS "-O0 -g ${CXX11_FLAG} -Werror -Wall -lpthread -lwiringPi")
  endif()
endif()

add_subdirectory(test)
add_subdirectory(src)

enable_testing()
