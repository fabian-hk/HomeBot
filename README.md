# Project description

This project is a bot which can collect
data and controls systems in your home. Currently the bot does save
power values from an Tesla Powerwall, scraps a website for fuel
prices for my location, can start my desktop pc and controls
my window shades. It has several user interfaces
like an Android app, a website and a Telegram Bot. In the following
graphic you can see how the devices interact with each other.

<img src="./doc/BotSchema.png">

This project is written in Python, C++, Kotlin, PHP and HTML.
I am writing it besides my studies in my free time and the system
is running on a Raspberry Pi 3 Model B since the beginning of 2019 without failing.

## Overview

- **Android app** (folder: [android_app](android_app)): The app listens to the Android Broadcast 
"NEXT_ALARM_CLOCK_CHANGED" which is send if a new alarm is set. 
The app than tells the RPI over gRPC when the alarm will go off. 
The RPI will then open the window shade a little 15 minutes before
the alarm goes off. After the alarm when the smartphones locks into 
the wifi network the RPI opens the window shade completely. 
Additional the app provides a Android Widget to move the window 
shades completely up or down.

- **IOT devices** (folder: [iot_devices](iot_devices/ControlShade)): This folder contains the Arduino
program for the NodeMCU ESP32 microcontroller to control the buttons 
of the window shade remote via transistors. The RPI can
either ask the microcontroller in which state it is or set a new
state via messages send over TCP. Further more the microcontroller
has an light detector on its analog input to move the windows
shades down if it gets dark outside. [Picture]

- **Main program** (folder: [main](main)): This is the main program which
runs on the Raspberry Pi and communicates with all the devices like
the microcontroller for the window shades, the Tesla Powerwall,
the Android app and Telegram. It also saves the collected data
and draws diagrams of it.

- **Webinterface** (folder: [website](website)): Currently the website only
shows the power values from the Powerwall for every day and every
month as well as the graphs for the current day.
