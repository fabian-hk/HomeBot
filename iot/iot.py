import pandas
import socket
import os

import config


class IOT:

    def __init__(self):
        self.folder = config.data_folder + "iot/"
        if not os.path.isdir(self.folder):
            os.mkdir(self.folder)

    @staticmethod
    def control_shade(name: str, vals: str) -> str:
        test = {"ip": config.iot_ip, "type": "shade", "name": "sh1"}
        df = pandas.DataFrame(test, index=[0])

        vals = vals.split(',')

        if len(vals) != 3:
            return 'Wrong number of arguments'

        cmd = b''
        for i in range(3):
            try:
                cmd += int(vals[i]).to_bytes(1, byteorder='big')
            except ValueError:
                return 'Wrong format for number ' + vals[i]

        for i, row in df.iterrows():
            if row['name'] == name:
                print(row)
                print(cmd)
                s = socket.socket()

                return 'Request was send'

        return 'No device with name ' + name + ' registered'


if __name__ == '__main__':
    iot = IOT()
    print(iot.control_shade('sh1', "50,75,12"))
