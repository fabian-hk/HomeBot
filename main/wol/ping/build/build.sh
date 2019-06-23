#!/bin/bash

mkdir -p out

if [ "$1" == "0" ]
then
	cd out/
	rm -r CMakeFiles CMakeCache.txt cmake_install.cmake Makefile cping
	cmake ../build/x86_64/
	make
	sudo setcap CAP_NET_RAW=ep ./cping
elif [ "$1" == "1" ]
then
	cd out/
	rm -r CMakeFiles CMakeCache.txt cmake_install.cmake Makefile cping
	cmake ../build/armv7/ -D CMAKE_BUILD_TYPE=Debug -D CMAKE_TOOLCHAIN_FILE=$HOME/rpi/Toolchain-RaspberryPi.cmake ..
	make
else
	echo "Pass 0 for x86_64 build and 1 for armv7 build."
fi
