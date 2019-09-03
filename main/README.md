# Description
This is the main program of the bot which is intended to run on a
Raspberry Pi. But it can also run on every other computer with a
linux operating system. The communication with the user is via 
 Telegram and it can talk to different users with different access
 permissions. The main features are:
1. Scrap the [clever-tanken](https://www.clever-tanken.de/) website
for my current location which I can send to it via Telegram and
draw graphs for the fuel prices in my hometown (folder: [fuelprice](fuelprice)).
2. Scrap the power data from the Tesla Powerwall and save them
in csv files (folder: [powerwall](powerwall)).
3. Control the IOT devices (currently only one microcontroller to
control the window shades). The control request can either come
through Telegram or via gRPC from the Android app for example (folder: [iot](iot)).
4. Check if my desktop computer is runing with the _Internet Control
Message Protocol_ (ICMP) and start it with wake on lan (folder: [wol](wol)).

# Dependencies
- python3
- apt packages: ``sudo apt install libatlas-base-dev python3-scipy``
- pip packages: ```pip3 install telepot wakeonlan matplotlib pandas protobuf configparser```

# Create config files
Create the following files in the root directory of the project:
1. Create a text file with the name ``secret`` which only holds ONE line with the access token for the bot
2. Create a ``bot.conf`` file which looks like the [bot.conf.example](bot.conf.example) file.

