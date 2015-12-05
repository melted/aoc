cmake_minimum_required(VERSION 3.3)
project(aoc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES_D1 day1.cpp)
set(SOURCE_FILES_D2 day2.cpp)
add_executable(day1 ${SOURCE_FILES_D1})
add_executable(day2 ${SOURCE_FILES_D2})
add_executable(day3 day3.cpp)
add_executable(day4 day4.cpp md5.cpp)