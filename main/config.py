import configparser
import os


def load_config():
    parser = configparser.ConfigParser()
    config_file = open(os.path.dirname(os.path.abspath(__file__))+"/bot.conf", "r")
    parser.read_file(config_file)
    return parser
