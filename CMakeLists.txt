cmake_minimum_required(VERSION 3.24)

project(similarityProject C CXX)

set(CMAKE_STANDARD 11)

add_subdirectory(googletest)

include_directories(googletest/include)

add_executable(similarityProjecttest similarityProjecttest.cpp)

target_link_libraries(similarityProjecttest PRIVATE gtest)


