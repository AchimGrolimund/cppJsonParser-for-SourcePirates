cmake_minimum_required(VERSION 3.6)
project(CPPWrapper)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES app.cpp json.hpp SourcePirates.h SourcePirates.cpp)
add_executable(CPPWrapper ${SOURCE_FILES})