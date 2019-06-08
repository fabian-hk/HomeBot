import subprocess

import config
from iot.service.out import libiotservice


class IOT:

    def __init__(self):
        parser = config.load_config()
        subprocess.Popen([parser["paths"]["root_folder"] + "iot/service/out/IotService",
                          parser["paths"]["root_folder"] + "bot.conf"])

    @staticmethod
    def control_shade(id: str, values: str):
        parser = config.load_config()
        path = parser["paths"]["root_folder"] + "bot.conf"
        return libiotservice.control_shade(id, values, path)

    @staticmethod
    def get_status(id: str):
        parser = config.load_config()
        path = parser["paths"]["root_folder"] + "bot.conf"
        return libiotservice.get_status(id, path)
