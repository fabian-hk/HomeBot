import subprocess

from iot.service.out import libiotservice


class IOT:

    def __init__(self):
        subprocess.Popen(["./iot/service/out/IotService"])

    @staticmethod
    def control_shade(id: str, values: str):
        return libiotservice.control_shade(id, values)

    @staticmethod
    def get_status(id: str):
        return libiotservice.get_status(id)
