cmake_minimum_required(VERSION 3.12)
project(c_project)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_CXX_FLAGS_RELEASE "-O3")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=x86-64")

set(ENV{BOOST_ROOT} "/usr/include/boost")

find_package(Boost 1.67 EXACT REQUIRED COMPONENTS python)

include_directories("${Boost_INCLUDE_DIRS}" "/usr/include/python3.7")

add_library(iotservice SHARED ../../src/IotService.cpp ../../src/Service.cpp ../../src/tools/Ping.cpp ../../src/Database.cpp ../../src/grpc_proto/iot.pb.cc ../../src/grpc_proto/iot.grpc.pb.cc)
target_link_libraries(iotservice boost_python37)
target_link_libraries(iotservice grpc++)
target_link_libraries(iotservice grpc++_reflection)
target_link_libraries(iotservice protobuf)

add_executable(IotService ../../src/Main.cpp ../../src/Service.cpp ../../src/tools/Ping.cpp ../../src/Database.cpp ../../src/grpc_proto/iot.pb.cc ../../src/grpc_proto/iot.grpc.pb.cc)
target_link_libraries(IotService grpc++)
target_link_libraries(IotService grpc++_reflection)
target_link_libraries(IotService protobuf)

