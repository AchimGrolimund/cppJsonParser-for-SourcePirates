cmake_minimum_required(VERSION 3.6)
project(CPPWrapper)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES app.cpp)
add_executable(CPPWrapper ${SOURCE_FILES})