cmake_minimum_required(VERSION 2.8)

project(clipper)

# INFO
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE "release")

# FILE
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

# LIBRARY
add_library(libclipper ${SOURCE_DIR}/clipper.h 
                       ${SOURCE_DIR}/clipper.cpp
                       ${SOURCE_DIR}/clipper_offset.h
                       ${SOURCE_DIR}/clipper_offset.cpp
                       ${SOURCE_DIR}/clipper_triangulation.h
                       ${SOURCE_DIR}/clipper_triangulation.cpp)

# DEMO
include_directories(${SOURCE_DIR})
add_executable(clipper ${PROJECT_SOURCE_DIR}/demo/main.cpp)
target_link_libraries(clipper libclipper)
