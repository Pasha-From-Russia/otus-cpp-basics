cmake_minimum_required(VERSION 3.5)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -ggdb")
endif()

project(03.guess_number)

add_executable(guess_number
    main.cpp
    highscore.cpp
    highscore.h
)

set_target_properties(guess_number PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
