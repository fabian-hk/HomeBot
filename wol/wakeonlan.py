import wakeonlan
import os

import config


def wake_desktop():
    wakeonlan.send_magic_packet(config.wol_pc)


def is_on():
    r = os.system("ping -c 1 " + config.on_pc)
    if r == 0:
        return "Desktop is online"
    else:
        return "Desktop is offline"
