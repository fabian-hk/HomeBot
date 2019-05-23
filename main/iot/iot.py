import pandas
import socket
import os
import telepot
from multiprocessing import Process
import datetime

import config
from users import users


class IOT(Process):

    BUFFER = 2048

    def __init__(self, bot: telepot.Bot):
        super().__init__()
        self.bot = bot

        self.folder = config.data_folder + "iot/"
        self.devices = self.folder + "devices.csv"
        if not os.path.isdir(self.folder):
            os.mkdir(self.folder)

    def control_shade(self, name: str, vals: str) -> str:
        if os.path.isfile(self.devices):
            df = pandas.read_csv(self.devices)
        else:
            return 'No devices available'

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
                s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                s.connect((row['ip'], config.iot_port))
                tmp = s.recv(128)
                s.send(cmd)
                ret = s.recv(128)
                if ret[:3] == cmd:
                    return 'Request was successful'
                else:
                    return "Request failed"

        return 'No device with name ' + name + ' registered'

    def run(self):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind(('', 1616))
        s.listen(5)
        while True:
            conn, addr = s.accept()
            print(addr)
            data = conn.recv(self.BUFFER)
            print(data)
            t = int(data.decode("utf-8"))/1000.0  # next time in seconds
            _, admins = users.user_lists()
            self.bot.sendMessage(admins[0], "Set windows shade open to: " + datetime.datetime.fromtimestamp(t).strftime("%H:%M"))
            conn.sendall(b'\x00')
            conn.shutdown(socket.SHUT_RDWR)
            conn.close()


if __name__ == '__main__':
    iot = IOT()
    print(iot.control_shade('sh1', "50,75,12"))
