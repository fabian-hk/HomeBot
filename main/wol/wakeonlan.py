import wakeonlan
import os

import config

conf = config.load_config()


def wake_desktop():
    wakeonlan.send_magic_packet(conf["network"]["wol_pc"])


def is_on():
    r = os.system("fping -t 10 " + conf["network"]["on_pc"])
    if r == 0:
        return "Desktop is online"
    else:
        return "Desktop is offline"
