# Dependencies
- python3
- apt packages: ``sudo apt install libatlas-base-dev python3-scipy``
- pip packages: ```pip3 install telepot wakeonlan matplotlib pandas protobuf configparser```
- create 'user_pb2.py' file from project root directory ``protoc --python_out=./ users/users.proto``

# Create config files
Create the following files in the root directory of the project:
1. create a text file with the name ``secret`` which only holds ONE line with the access token for the bot
2. create the ``bot.conf`` file which has the following variables:
```
[paths]
data_folder=<path to the folder where you want to save your data>
root_folder=<path to the root folder of this project>

[powerwall]
ip_powerwall=192.168.2.50

[defaults]
default_latitude=30.0 // default location for new created users
default_longitude=20.0 // default location for new created users
# debug level WARNING
debug_level=30

[network]
wol_pc=FF:BB:00:11:22:33
on_pc=192.168.2.55
```
