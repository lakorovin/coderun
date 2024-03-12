cmake_minimum_required(VERSION 3.16)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)

add_subdirectory(cafe)
add_subdirectory(cheapest-way)
add_subdirectory(knight-move)
add_subdirectory(median-out-of-three)
add_subdirectory(print-the-route-of-the-maximum-cost)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT cafe)
