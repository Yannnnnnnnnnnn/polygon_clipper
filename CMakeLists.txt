cmake_minimum_required(VERSION 2.8)

project(clipper)

# INFO
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE "release")

# FILE
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

# LIBRARY
add_library(libclipper ${SOURCE_DIR}/svg.h
                       ${SOURCE_DIR}/svg.cpp
                       ${SOURCE_DIR}/clipper.h 
                       ${SOURCE_DIR}/clipper.cpp
                       ${SOURCE_DIR}/clipper_offset.h
                       ${SOURCE_DIR}/clipper_offset.cpp
                       ${SOURCE_DIR}/clipper_triangulation.h
                       ${SOURCE_DIR}/clipper_triangulation.cpp)

# DEMO
include_directories(${SOURCE_DIR})
add_executable(clipper_intersection ${PROJECT_SOURCE_DIR}/demo/main_intersection.cpp)
target_link_libraries(clipper_intersection libclipper)

include_directories(${SOURCE_DIR})
add_executable(clipper_union ${PROJECT_SOURCE_DIR}/demo/main_union.cpp)
target_link_libraries(clipper_union libclipper)

include_directories(${SOURCE_DIR})
add_executable(clipper_difference ${PROJECT_SOURCE_DIR}/demo/main_difference.cpp)
target_link_libraries(clipper_difference libclipper)

include_directories(${SOURCE_DIR})
add_executable(clipper_xor ${PROJECT_SOURCE_DIR}/demo/main_xor.cpp)
target_link_libraries(clipper_xor libclipper)