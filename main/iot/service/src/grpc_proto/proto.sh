#!/bin/bash

protoc -I . --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` iot.proto
protoc -I . --cpp_out=. iot.proto
