import os
import telepot
from telepot.loop import MessageLoop
import logging
from multiprocessing import Queue

from fuelprice.fuelprice import FuelPrice
from wol import wakeonlan
from powerwall.powerwall import Powerwall
from users import users
import config

# initialize logger
log_folder = config.data_folder + "log/"
if not os.path.isdir(log_folder):
    os.makedirs(log_folder)
logging.basicConfig(filename=log_folder + 'bot.log',
                    format='%(levelname)s %(asctime)s %(filename)s Line %(lineno)d:\t%(message)s',
                    datefmt='%d-%m-%Y %H:%M:%S')
logger = logging.getLogger('main')
logger.setLevel(config.debug_level)
logger.debug("main.py started")

chat_ids, admin_ids = users.user_lists()

# initialize queue to send data between main and FuelPrice
q = Queue()


def handle(msg):
    content_type, chat_type, chat_id = telepot.glance(msg)
    logger.debug("Chat id: " + str(chat_id) + " type: " + str(content_type))
    if chat_id in chat_ids:
        if content_type == "text":
            cmd = str(msg['text']).lower().split(" ")
            if cmd[0] == "fuel":
                if len(cmd) == 1:
                    try:
                        bot.sendMessage(chat_id, FuelPrice.encode_prices(FuelPrice.get_results(chat_id)))
                    except Exception as e:
                        logger.error(e)
                elif cmd[1] == "stat":
                    try:
                        bot.sendPhoto(chat_id, FuelPrice.get_graph())
                    except Exception as e:
                        logger.error(e)
                elif cmd[1] == "limit":
                    try:
                        l = float(cmd[2])
                        q.put((chat_id, l))
                        bot.sendMessage(chat_id, "Changed price limit to " + str(l) + "€")
                    except Exception as e:
                        logger.error(e)
            elif cmd[0] == "wol" and chat_id in admin_ids:
                wakeonlan.wake_desktop()
                try:
                    bot.sendMessage(chat_id, "Starting desktop...")
                except Exception as e:
                    logger.error(e)
            elif cmd[0] == "on" and chat_id in admin_ids:
                try:
                    m = wakeonlan.is_on()
                    bot.sendMessage(chat_id, m)
                except Exception as e:
                    logger.error(e)
            elif cmd[0] == "temp" and chat_id in admin_ids:
                try:
                    r = os.popen('vcgencmd measure_temp').read()
                    bot.sendMessage(chat_id, r)
                except Exception as e:
                    logger.error(e)
            elif cmd[0] == "power":
                try:
                    bot.sendPhoto(chat_id, Powerwall.get_current_value())
                except Exception as e:
                    logger.error(e)
        if content_type == "location":
            try:
                users.change_position(chat_id, msg['location']['longitude'], msg['location']['latitude'])
                bot.sendMessage(chat_id, "Position changed")
            except Exception as e:
                logger.error(e)


def start(bot=None):
    if bot is None:
        token = open(config.root_folder + "secret", "r")
        bot = telepot.Bot(token.readline())
    bot.sendMessage(admin_ids[0], "Bot is running")
    logger.debug("Initialized bot")
    try:
        MessageLoop(bot, handle).run_forever()
    except Exception as e:
        logger.error("Exception in MessageLoop")
        logger.error(e)
        start()


if __name__ == "__main__":
    token = open(config.root_folder + "secret", "r")
    bot = telepot.Bot(token.readline())

    pw = Powerwall()
    pw.start()

    fp = FuelPrice(bot, q)
    fp.start()

    start(bot)
