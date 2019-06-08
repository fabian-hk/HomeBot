cmake_minimum_required(VERSION 3.12)
project(c_project)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=x86-64")

set(ENV{BOOST_ROOT} "/usr/include/boost")

find_package(Boost 1.67 EXACT REQUIRED COMPONENTS python)

include_directories("${Boost_INCLUDE_DIRS}" "/usr/include/python3.7")

add_library(service SHARED ../../src/Service.cpp ../../src/Database.cpp ../../src/grpc_proto/iot.pb.cc ../../src/grpc_proto/iot.grpc.pb.cc)
set_target_properties(service PROPERTIES PUBLIC_HEADER ../../src/Service.h)
set_target_properties(service PROPERTIES PUBLIC_HEADER ../../src/Database.h)
target_link_libraries(service grpc++)
target_link_libraries(service grpc++_reflection)
target_link_libraries(service protobuf)

add_library(iotservice SHARED ../../src/IotService.cpp )
target_link_libraries(iotservice service)
target_link_libraries(iotservice boost_python37)
target_link_libraries(iotservice grpc++)
target_link_libraries(iotservice grpc++_reflection)
target_link_libraries(iotservice protobuf)

add_executable(IotService ../../src/Main.cpp)
target_link_libraries(IotService grpc++)
target_link_libraries(IotService grpc++_reflection)
target_link_libraries(IotService protobuf)
target_link_libraries(IotService service)

