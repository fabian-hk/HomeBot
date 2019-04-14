import os
from multiprocessing import Process, Queue
import numpy as np
from selenium import webdriver
from selenium.webdriver.firefox.options import Options
import pandas
import matplotlib.pyplot as plt
import time
import datetime
import logging

import config
from users import users as user_management


class FuelPrice(Process):

    def __init__(self, bot, q: Queue):
        super().__init__()
        self.bot = bot
        self.q = q

        # initialize logger
        log_folder = config.data_folder + "log/"
        if not os.path.isdir(log_folder):
            os.makedirs(log_folder)
        logging.basicConfig(filename=log_folder + 'bot.log',
                            format='%(levelname)s %(asctime)s %(filename)s Line %(lineno)d:\t%(message)s',
                            datefmt='%d-%m-%Y %H:%M:%S')
        self.logger = logging.getLogger('fuelprice')
        self.logger.setLevel(config.debug_level)
        self.logger.debug("fuelprice.py started")

        self.send_results = 5

        # initialization
        self.folder = config.data_folder + "fuelprice/"
        if not os.path.isdir(self.folder):
            os.makedirs(self.folder)

        if not config.firefox_webdriver:
            options = webdriver.ChromeOptions()
            options.add_argument("headless")
            options.add_argument("window-size=1200x600")
            self.driver = webdriver.Chrome(chrome_options=options,
                                           executable_path="fuelprice/chromedriver/chromedriver.exe")

        if config.virtual_display:
            from pyvirtualdisplay import Display

            display = Display(visible=0, size=(320, 240))
            display.start()

        if config.firefox_webdriver:
            options = Options()
            # options.add_argument("headless")
            self.driver = webdriver.Firefox(firefox_options=options,
                                            executable_path=config.data_folder + 'webdriver/geckodriver')

    @staticmethod
    def encode_prices(list):
        response = ""
        for item in list:
            response += item.name + ": " + "{:1.3f}".format(item.price) + "\n" + item.street + "\n" + item.city + "\n\n"
        return response

    def price_alert(self, user):
        list = []
        send = False
        for item in user.fuel_prices:
            if item.price < user.price_limit and item.price != -1:
                list.append(item)
            if item.price < user.lowest_price and item.price != -1:
                send = True
                user.lowest_price = item.price
        if list and send:
            try:
                self.bot.sendMessage(user.chat_id, self.encode_prices(list))
            except Exception as e:
                self.logger.error(e)

    def save_data(self, results):
        name = "Fuel_" + time.strftime("%Y_%m_%d", time.localtime()) + ".csv"

        cols = ['time']
        input = [[time.strftime("%H:%M:%S", time.localtime())]]
        for i in results:
            cols.append(i.name + ', ' + i.street + ', ' + i.city)
            input[0].append(i.price)

        df = pandas.DataFrame(columns=cols)

        if os.path.isfile(self.folder + name):
            df = pandas.read_csv(self.folder + name, sep="\t", decimal=",", index_col=0)

        new_df = pandas.DataFrame(input, columns=cols)
        df = df.append(new_df, ignore_index=True, sort=False)

        df.to_csv(self.folder + name, sep="\t", decimal=",")

    def draw_graph(self):
        f, axarr = plt.subplots(2, 2)
        i = 0
        j = 0
        for s in range(3, -1, -1):
            date = datetime.datetime.now() - datetime.timedelta(days=s)
            name = "Fuel_" + date.strftime("%Y_%m_%d") + ".csv"

            if os.path.isfile(self.folder + name):
                df = pandas.read_csv(self.folder + name, sep="\t", decimal=",", index_col=0)

                df['time'] = df['time'].apply(
                    lambda x: int(x.split(':')[0]) + (int(x.split(':')[1]) * 60 + int(x.split(':')[2])) / 3600)

                for c in df.columns.values:
                    if "time" not in c:
                        tmp = df[df[c].astype(np.float32) != -1]
                        t = tmp['time'].astype(np.float32).values.tolist()
                        y = tmp[c].astype(np.float32).values.tolist()
                        axarr[i, j].plot(t, y, label=c, alpha=0.5)
                axarr[i, j].set_title(date.strftime("%Y_%m_%d"))
                axarr[i, j].set_ylabel("Price in euro")
                axarr[i, j].set_xlabel("Hours")
                # axarr[i, j].legend(prop={'size': 5})

            if i == 0 and j == 0:
                j = 1
                i = 0
            elif i == 0 and j == 1:
                i = 1
                j = 0
            elif i == 1 and j == 0:
                j = 1

        handels, labels = axarr[1, 1].get_legend_handles_labels()
        f.legend(handels, labels, loc='center', prop={'size': 5})

        f.subplots_adjust(hspace=0.7, wspace=0.5)
        plt.savefig(self.folder + "fuel.png", dpi=300)
        plt.close()

    def scrap_web_data(self):
        users = user_management.load_users()
        for user in users.users:
            self.driver.get(
                "https://www.clever-tanken.de/tankstelle_liste?lat=" + str(user.latitude) + "&lon=" + str(
                    user.longitude) + "&spritsorte=" + str(config.fuel_kind) + "&r=5.0&sort=km")

            items = self.driver.find_elements_by_css_selector("*[id^='tankstelle-']")

            user.ClearField("fuel_prices")
            for item in items[:self.send_results]:
                fp = user.fuel_prices.add()
                fp.name = item.find_element_by_class_name("fuel-station-location-name").text
                fp.street = item.find_element_by_id("fuel-station-location-street").text
                fp.city = item.find_element_by_id("fuel-station-location-city").text
                try:
                    fp.price = float(item.find_element_by_class_name("price").text)
                except Exception:
                    fp.price = -1

            # send alert to the user if the price is low
            if user.chat_id != -1:
                self.price_alert(user)

            # save results to csv
            if user.chat_id == -1:
                self.save_data(user.fuel_prices)

        user_management.save_users(users)

        self.logger.debug("Scraped fuel prices")

    @staticmethod
    def get_results(chat_id):
        return user_management.get_fuel_prices(chat_id)

    @staticmethod
    def get_graph():
        return open(config.data_folder + "fuelprice/fuel.png", 'rb')

    def run(self):
        reset_price = True

        while True:
            try:
                price_limit = self.q.get_nowait()
                user_management.change_fuel_price_limit(price_limit[0], price_limit[1])
            except Exception as e:
                self.logger.debug(e)

            try:
                self.scrap_web_data()
                # draw graph with prices
                self.draw_graph()

                # reset lowest price every morning
                if time.strftime("%H", time.localtime()) == '00' and reset_price:
                    user_management.reset_price_alert()
                    reset_price = False
                    self.logger.debug("Reset price alert")

                if time.strftime("%H", time.localtime()) == '02':
                    reset_price = True

            except Exception as e:
                self.logger.error(e)

            time.sleep(300)
