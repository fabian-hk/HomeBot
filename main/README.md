# Description
This is the main program of the bot which is intended to run on a
Raspberry Pi. But it can also run on every other computer with a
linux operating system. The communication with the user is via 
 Telegram and it can talk to different users with different access
 permissions. The main features are:
1. Scraps the [clever-tanken](https://www.clever-tanken.de/) website
for my current location which I can send to it via Telegram and
draws graphs for the fuel prices in my hometown (folder: [fuelprice](fuelprice)).
2. Scraps the power data from the Tesla Powerwall and saves them
in csv files (folder: [powerwall](powerwall)).
3. Controls the IOT devices (currently only one microcontroller to
control the window shades). The control requests can either come
via Telegram or via gRPC from the Android app (folder: [iot](iot)).
4. Checks if my desktop computer is running with the _Internet Control
Message Protocol_ (ICMP) and starts it with wake-on-lan (folder: [wol](wol)).

# Dependencies
- python3
- apt packages: ``sudo apt install libatlas-base-dev python3-scipy``
- pip packages: ```pip3 install telepot wakeonlan matplotlib pandas protobuf configparser```

# Create config files
Create the following files in the root directory of the project:
1. Create a text file with the name ``secret`` which only holds ONE line with the access token for the bot.
2. Create a ``bot.conf`` file which looks like the [bot.conf.example](bot.conf.example) file.

# Usage with Docker
For easy setup, you can just pull the Docker image with the
following command:

```
docker pull fabianhk/homebot
```

You have to mount a data folder and the configuration file
with these options:

1. ``-v "$PWD/data:/mnt/data"``
2. ``-v "$PWD/bot.conf:/workdir/bot/bot.conf"``

Complete Docker run command:

```
docker run -p 80:80 \
 -v "$PWD/data:/mnt/data" \
 -v "$PWD/bot.conf:/workdir/bot/bot.conf" \
 fabianhk/homebot
```
