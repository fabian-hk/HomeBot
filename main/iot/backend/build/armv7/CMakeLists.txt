cmake_minimum_required(VERSION 3.12)
project(c_project)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=x86-64")

set(ENV{BOOST_ROOT} "/usr/include/boost")

find_package(Boost 1.62 EXACT REQUIRED COMPONENTS python)

find_library(GRPC_C libgrpc.a HINTS /usr/local/lib)
find_library(GRPC_CXX libgrpc++.a HINTS /usr/local/lib)
find_library(GRPC_REFLECTION libgrpc++_reflection.a HINTS /usr/local/lib)
find_library(PROTOBUF_CXX libprotobuf.a HINTS /usr/local/lib/protobuf)

message(${PROTOBUF_CXX})

include_directories(${Boost_INCLUDE_DIRS} /usr/include/python3.5m /usr/local/include)

add_executable(main ../../src/Main.cpp)
target_link_libraries(main ${GRPC_C})
target_link_libraries(main ${GRPC_CXX})
target_link_libraries(main ${GRPC_REFLECTION})
target_link_libraries(main ${PROTOBUF_CXX})

#add_library(webscraper SHARED ../../src/webScraper.cpp ../../src/proto/users.pb.cc ../../src/Base64.h ../../src/Scraper.cpp ../../src/Scraper.h)
#target_link_libraries(webscraper boost_python-py35)
#target_link_libraries(webscraper ${CURL})
#target_link_libraries(webscraper protobuf)

