cmake_minimum_required(VERSION 3.7)
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
find_library(PROTOBUF libprotobuf.so HINTS /usr/local/lib)

include_directories(${Boost_INCLUDE_DIRS} /usr/include/python3.5m /usr/local/include)

#add_library(service SHARED ../../src/Service.cpp ../../src/Database.cpp ../../src/grpc_proto/iot.pb.cc ../../src/grpc_proto/iot.grpc.pb.cc)
#set_target_properties(service PROPERTIES PUBLIC_HEADER ../../src/Service.h)
#set_target_properties(service PROPERTIES PUBLIC_HEADER ../../src/Database.h)
#target_link_libraries(service grpc++)
#target_link_libraries(service grpc++_reflection)
#target_link_libraries(service protobuf)

add_library(iotservice SHARED ../../../src/IotService.cpp ../../../src/Service.cpp ../../../../utils/Ping.cpp ../../../src/Database.cpp ../../../src/grpc_proto/iot.pb.cc ../../../src/grpc_proto/iot.grpc.pb.cc)
#target_link_libraries(iotservice service)
target_link_libraries(iotservice boost_python-py35)
target_link_libraries(iotservice grpc++)
target_link_libraries(iotservice grpc++_reflection)
target_link_libraries(iotservice ${PROTOBUF})

add_executable(IotService ../../../src/Main.cpp ../../../src/Service.cpp ../../../../utils/Ping.cpp ../../../src/Database.cpp ../../../src/grpc_proto/iot.pb.cc ../../../src/grpc_proto/iot.grpc.pb.cc)
target_link_libraries(IotService grpc++)
target_link_libraries(IotService grpc++_reflection)
target_link_libraries(IotService ${PROTOBUF})
#target_link_libraries(IotService service)

