cmake_minimum_required(VERSION 3.5)

project(06.homework)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -ggdb")
endif()

add_executable(containers
    main.cpp
    linked_list_container.cpp linked_list_container.h serial_container.cpp serial_container.h)

set_target_properties(containers PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


