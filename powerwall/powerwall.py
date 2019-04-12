from multiprocessing import Process
import requests
import json
import pandas
import time
import os
import matplotlib.pyplot as plt
import logging

import config
from powerwall import integral
import powerwall.calc_month_values as cmv


class Powerwall(Process):

    def __init__(self):
        super().__init__()
        self.cols = ["time", "solar", "home", "powerwall", "grid", "capacity"]

        # create data folder if it doesn't exists
        self.folder = config.data_folder + "powerwall/"
        if not os.path.isdir(self.folder):
            os.makedirs(self.folder)

        # initialize logger
        log_folder = config.data_folder + "log/"
        if not os.path.isdir(log_folder):
            os.makedirs(log_folder)
        logging.basicConfig(filename=log_folder + 'bot.log',
                            format='%(levelname)s %(asctime)s %(filename)s Line %(lineno)d:\t%(message)s',
                            datefmt='%d-%m-%Y %H:%M:%S')
        self.logger = logging.getLogger('powerwall')
        self.logger.setLevel(config.debug_level)
        self.logger.debug("powerwall.py started")

        self.data = {}

    @staticmethod
    def get_date(name):
        return str(name[name.find('_') + 1:name.find('.')])

    def calc_current_values(self):
        show_cols = ["home", "grid", "solar", "powerwall"]
        csv_cols = ["time", "home", "from_grid", "to_grid", "solar", "from_powerwall", "to_powerwall"]

        if os.path.isfile(self.folder + "current_values.csv"):
            cv = pandas.read_csv(self.folder + "current_values.csv", sep=";", decimal=",", index_col=0)
        else:
            cv = pandas.DataFrame(columns=csv_cols)

        current_date = time.strftime("%Y_%m_%d", time.localtime())
        dates = cv["time"].values.tolist()

        for name in sorted(os.listdir(self.folder)):
            if os.path.isfile(self.folder + name) and "Power" in name:
                date = self.get_date(name)
                if date not in dates or date == current_date:
                    line = [[date]]
                    if date == current_date:
                        f, axarr = plt.subplots(2, 2)
                        i = 0
                        j = 0
                    for c in show_cols:
                        df = pandas.read_csv(self.folder + name, sep="\t", decimal=",", index_col=0)
                        df['time'] = df['time'].apply(
                            lambda x: int(x.split(':')[0]) + (int(x.split(':')[1]) * 60 + int(x.split(':')[2])) / 3600)
                        df['powerwall'] = df['powerwall'].apply(lambda x: 0 if x in [-20, -10, 10, 20] else x)
                        x = df['time'].values.tolist()
                        y = df[c].values.tolist()
                        if c is "grid" or c is "powerwall":
                            y1 = [t if t > 0 else 0.0 for t in y]
                            y2 = [t if t < 0 else 0.0 for t in y]
                            if abs(sum(y1)) > 0:
                                result1 = integral.integral(x, y1)
                            else:
                                result1 = 0.0
                            if abs(sum(y2)) > 0:
                                result2 = integral.integral(x, y2)
                            else:
                                result2 = 0.0

                            line[0].append(abs(result1))
                            line[0].append(abs(result2))

                            result = "from: " + str(abs(result1)).split(".")[0] + "Wh to: " + \
                                     str(abs(result2)).split(".")[
                                         0] + "Wh"
                        else:
                            result = integral.integral(x, y)
                            line[0].append(result)
                            result = str(result).split(".")[0] + "Wh"

                        if date == current_date:
                            axarr[i, j].plot(x, y)
                            axarr[i, j].set_title(c.title() + " (" + result + ")")
                            axarr[i, j].set_ylabel("Watt")
                            axarr[i, j].set_xlabel("Stunden")
                            if i == 0 and j == 0:
                                j = 1
                                i = 0
                            elif i == 0 and j == 1:
                                i = 1
                                j = 0
                            elif i == 1 and j == 0:
                                j = 1

                    if date == current_date:
                        f.subplots_adjust(hspace=0.7, wspace=0.5)
                        plt.savefig(self.folder + "power.svg")
                        plt.savefig(self.folder + "power.png", dpi=300)
                        plt.close()

                    if date in dates:
                        index = cv.index[cv['time'] == date].tolist()
                        tmp = pandas.DataFrame(line, index=index, columns=csv_cols)
                        cv.update(tmp)
                    else:
                        tmp = pandas.DataFrame(line, columns=csv_cols)
                        cv = cv.append(tmp, ignore_index=True, sort=False)

        cv.to_csv(self.folder + "current_values.csv", sep=";", decimal=",")

    def load_csv(self):
        date = time.strftime("%Y_%m_%d", time.localtime())
        name = "Power_" + date + ".csv"
        if date in self.data:
            pass
        elif os.path.isfile(self.folder + name):
            self.data[date] = pandas.read_csv(self.folder + name, sep="\t", decimal=",", index_col=0)
            self.logger.debug("read csv from disc")
        else:
            self.data[date] = pandas.DataFrame(columns=self.cols)

    def save_csv(self):
        current_date = time.strftime("%Y_%m_%d", time.localtime())
        for date in self.data.keys():
            name = "Power_" + date + ".csv"
            self.data[date].to_csv(self.folder + name, sep="\t", decimal=",")
            if date != current_date:
                del self.data[date]
        self.logger.debug("saved csv files")
        self.logger.debug("data size:" + str(len(self.data)))

    def get_power_data(self):
        date = time.strftime("%Y_%m_%d", time.localtime())
        self.load_csv()

        raw_data = requests.get("https://" + config.ip_powerwall + "/api/meters/aggregates", verify=False)
        data1 = json.loads(raw_data.text)

        raw_data = requests.get("https://" + config.ip_powerwall + "/api/system_status/soe", verify=False)
        data2 = json.loads(raw_data.text)

        input_data = [[time.strftime("%H:%M:%S", time.localtime()), float(data1['solar']['instant_power']),
                       float(data1['load']['instant_power']),
                       float(data1['battery']['instant_power']), float(data1['site']['instant_power']),
                       float(data2['percentage'])]]
        new_df = pandas.DataFrame(input_data, columns=self.cols)
        self.data[date] = self.data[date].append(new_df, ignore_index=True, sort=False)

    def run(self):
        last_time_saved = time.time()
        calc_month_values = False
        while True:
            try:
                self.get_power_data()

                # save every two minutes the csv files to the disk
                if time.time() - last_time_saved >= 120:
                    self.save_csv()
                    self.calc_current_values()
                    last_time_saved = time.time()

                    # calc month values once a day
                    if time.strftime("%H_%M", time.localtime()) in ['09_55', '09_56', '09_57'] and not calc_month_values:
                        calc_month_values = True
                        cmv.calculate_month_values()
                        self.logger.debug("Calculated month values")

                    if time.strftime("%H", time.localtime()) == '01':
                        calc_month_values = False
                        self.logger.debug("Reset daily month calculation")

            except Exception as e:
                self.logger.error(e)
            time.sleep(4)

    @staticmethod
    def get_current_value():
        return open(config.data_folder + "powerwall/power.png", 'rb')
