cmake_minimum_required(VERSION 3.12)
project(bot)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_CXX_FLAGS_RELEASE "-O3")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=x86-64")

set(ENV{BOOST_ROOT} "/usr/include/boost")

find_package(Boost 1.67 EXACT REQUIRED COMPONENTS python)
find_package(Protobuf REQUIRED)

include_directories("${Boost_INCLUDE_DIRS}" "/usr/include/python3.7")

# global variables
set(UTILS ${CMAKE_SOURCE_DIR}/utils)


###############################################################################################################
# build web scraper for the fuel price module
###############################################################################################################
set(WS_SRC ${CMAKE_SOURCE_DIR}/fuelprice/src)
set(PROTO_DIR ${WS_SRC}/proto/)

add_custom_command(OUTPUT ${WS_SRC}/proto/users.pb.cc ${WS_SRC}/proto/users.pb.h
        COMMAND protoc -I ${PROTO_DIR} --cpp_out=${PROTO_DIR} ${PROTO_DIR}/users.proto)

add_library(webscraper SHARED ${WS_SRC}/webScraper.cpp ${WS_SRC}/Base64.h ${WS_SRC}/Scraper.cpp
        ${WS_SRC}/Scraper.h ${WS_SRC}/proto/users.pb.cc ${WS_SRC}/proto/users.pb.h)

target_link_libraries(webscraper boost_python37)
target_link_libraries(webscraper curl)
target_link_libraries(webscraper protobuf)


###############################################################################################################
# build the ping executable for the wol module
###############################################################################################################
set(PING_SRC ${CMAKE_SOURCE_DIR}/wol/src)

add_executable(cping ${PING_SRC}/Main.cpp ${UTILS}/Ping.cpp ${UTILS}/Ping.h)

add_custom_command(TARGET cping POST_BUILD COMMAND sudo setcap CAP_NET_RAW=ep ./cping)


###############################################################################################################
# build the iot service library and the background service
###############################################################################################################
set(IOT_SRC ${CMAKE_SOURCE_DIR}/iot/src)
set(IOT_GRPC ${IOT_SRC}/grpc_proto)

add_custom_command(OUTPUT ${IOT_SRC}/grpc_proto/iot.grpc.pb.cc ${IOT_SRC}/grpc_proto/iot.grpc.pb.h
        COMMAND protoc -I ${IOT_GRPC} --grpc_out=${IOT_GRPC} --plugin=protoc-gen-grpc=`which grpc_cpp_plugin`
        ${IOT_GRPC}/iot.proto)
add_custom_command(OUTPUT ${IOT_SRC}/grpc_proto/iot.pb.cc ${IOT_SRC}/grpc_proto/iot.pb.h
        COMMAND protoc -I ${IOT_GRPC} --cpp_out=${IOT_GRPC} ${IOT_GRPC}/iot.proto)

add_library(iotservice SHARED ${IOT_SRC}/IotService.cpp ${IOT_SRC}/Service.cpp ${UTILS}/Ping.cpp
        ${IOT_SRC}/Database.cpp ${IOT_SRC}/grpc_proto/iot.pb.cc ${IOT_SRC}/grpc_proto/iot.pb.h
        ${IOT_SRC}/grpc_proto/iot.grpc.pb.cc ${IOT_SRC}/grpc_proto/iot.grpc.pb.h)

target_link_libraries(iotservice boost_python37)
target_link_libraries(iotservice grpc++)
target_link_libraries(iotservice grpc++_reflection)
target_link_libraries(iotservice protobuf)

add_executable(IotService ${IOT_SRC}/Main.cpp ${IOT_SRC}/Service.cpp ${UTILS}/Ping.cpp ${IOT_SRC}/Database.cpp
        ${IOT_SRC}/grpc_proto/iot.pb.cc ${IOT_SRC}/grpc_proto/iot.grpc.pb.cc)

target_link_libraries(IotService grpc++)
target_link_libraries(IotService grpc++_reflection)
target_link_libraries(IotService protobuf)