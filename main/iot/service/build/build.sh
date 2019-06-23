#!/bin/bash

mkdir -p out

if [ "$1" == "0" ]
then
	cd out/
	rm -r CMakeFiles CMakeCache.txt cmake_install.cmake Makefile main libiotservice.so
	cmake ../build/x86_64/
	make
	sudo setcap CAP_NET_RAW=ep ./IotService
elif [ "$1" == "1" ]
then
	cd out/
	rm -r CMakeFiles CMakeCache.txt cmake_install.cmake Makefile main libwebscraper.so
	cmake ../build/armv7/
	make
	sudo setcap CAP_NET_RAW=ep ./IotService
else
	echo "Pass 0 for x86_64 build and 1 for armv7 build."
fi
