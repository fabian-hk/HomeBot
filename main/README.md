# Installation requirements
- python3
- apt packages: ``sudo apt install libatlas-base-devpython3-scipy``
- pip packages: ```pip3 install telepot wakeonlan matplotlib pandas protobuf```
- create 'user_pb2.py' file from project root directory ``protoc --python_out=./ users/users.proto``

### Create config files
Create the following files in the root directory of the project:
1. create a text file with the name 'secret' which only holds ONE line with the access token for the bot
2. create the 'config.py' file which has the following variables:
```python
import logging

data_folder = '<directory where you want to save the data>/'
root_folder = '<directory where the project is>/'
virtual_display = True # true if you are running on a raspberry pi
firefox_webdriver = True # if false the chrome webdriver will be used
debug_level = logging.LEVEL

ip_powerwall = "192.168.2.50"
default_latitude = 30.0
default_longitude = 10.0
fuel_kind = 0 # kind of fuel as integer

wol_pc = "FF:AA:00:11:22:33"
on_pc = "192.168.2.55"
```

## Webinterface requirements
``sudo apt install apache2 php``