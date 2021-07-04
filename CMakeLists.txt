cmake_minimum_required(VERSION 3.19)
project(CGIapp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CGIapp
        cgiClientExample.cpp
        cgiServerExample.cpp
        myCgi.cpp
        myCgi.hpp)
