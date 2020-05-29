import wakeonlan
import subprocess

import config

conf = config.load_config()


def wake_desktop():
    wakeonlan.send_magic_packet(conf["network"]["wol_pc"], ip_address=conf["network"]["on_pc"])


def is_on():
    r = subprocess.getoutput(conf["paths"]["root_folder"] + "build/cping "
                             + conf["network"]["on_pc"]
                             + " 10")
    if r == "1":
        return "Desktop is online"
    else:
        return "Desktop is offline"
