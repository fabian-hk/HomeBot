cmake_minimum_required(VERSION 3.12)
project(c_project)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=x86-64")

set(ENV{BOOST_ROOT} "/usr/include/boost")

find_package(Boost 1.62 EXACT REQUIRED COMPONENTS python)
find_library(CURL libcurl.so HINTS /usr/lib/arm-linux-gnueabihf)
find_library(PROTOBUF libprotobuf.so HINTS /usr/local/lib)

include_directories(${Boost_INCLUDE_DIRS} /usr/include/python3.5m)

add_executable(main ../../src/Main.cpp ../../src/proto/users.pb.cc ../../src/Base64.h ../../src/Scraper.cpp ../../src/Scraper.h)
target_link_libraries(main ${CURL})
target_link_libraries(main ${PROTOBUF})

add_library(webscraper SHARED ../../src/webScraper.cpp ../../src/proto/users.pb.cc ../../src/Base64.h ../../src/Scraper.cpp ../../src/Scraper.h)
target_link_libraries(webscraper boost_python-py35)
target_link_libraries(webscraper ${CURL})
target_link_libraries(webscraper ${PROTOBUF})

