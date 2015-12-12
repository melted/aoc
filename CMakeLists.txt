cmake_minimum_required(VERSION 3.3)
project(aoc)

set(CMAKE_CXX_STANDARD 14)

add_executable(day1 day1.cpp)
add_executable(day2 day2.cpp)
add_executable(day3 day3.cpp)
add_executable(day4 day4.cpp md5.cpp)
add_executable(day5 day5.cpp)
add_executable(day6 day6.cpp)
add_executable(day7 day7.cpp)
add_executable(day8 day8.cpp)
add_executable(day9 day9.cpp)
add_executable(day10 day10.cpp)
add_executable(day11 day11.cpp)
add_executable(day12 day12.cpp)

target_link_libraries(day12 jsoncpp)