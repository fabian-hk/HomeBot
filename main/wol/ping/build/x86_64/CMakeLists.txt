cmake_minimum_required(VERSION 3.12)
project(c_project)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=x86-64")

add_executable(cping ../../src/Main.cpp ../../src/Ping.cpp)

