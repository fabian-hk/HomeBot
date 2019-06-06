cmake_minimum_required(VERSION 3.12)
project(c_project)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_CXX_FLAGS_RELEASE "-O3")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=x86-64")

set(ENV{BOOST_ROOT} "/usr/include/boost")

find_package(Boost 1.67 EXACT REQUIRED COMPONENTS python)

include_directories("${Boost_INCLUDE_DIRS}" "/usr/include/python3.7")


add_executable(main ../../src/Main.cpp ../../src/Service.cpp ../../src/Database.cpp ../../src/grpc_proto/iot.pb.cc ../../src/grpc_proto/iot.grpc.pb.cc)

target_link_libraries(main grpc++)
target_link_libraries(main grpc++_reflection)
target_link_libraries(main protobuf)

# add_library(webscraper SHARED ../../src/webScraper.cpp ../../src/proto/users.pb.cc ../../src/Base64.h ../../src/Scraper.cpp ../../src/Scraper.h)
# target_link_libraries(webscraper boost_python37)
# target_link_libraries(webscraper curl)
# target_link_libraries(webscraper protobuf)

