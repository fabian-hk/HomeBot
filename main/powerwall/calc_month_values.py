import pandas
import time
import os

import config

folder = config.data_folder + "powerwall/"


def get_month_value(date: str, cv: pandas.DataFrame, index=[0]):
    """
    Calculate the sum of the current values for a given month.
    """
    show_cols = ["home", "from_grid", "to_grid", "solar", "from_powerwall", "to_powerwall"]
    data = [date]
    for col in show_cols:
        data.append(cv.loc[(cv["time"].str.contains(date))][col].sum())
    return pandas.DataFrame([data], columns=['time'] + show_cols, index=index)


def calculate_month_values():
    show_cols = ["time", "home", "from_grid", "to_grid", "solar", "from_powerwall", "to_powerwall"]

    if os.path.isfile(folder + "current_values.csv"):
        cv = pandas.read_csv(folder + "current_values.csv", sep=";", decimal=",", index_col=0)

        time_list = cv['time'].apply(lambda x: x.split("_")[0] + "_" + x.split("_")[1]).values.tolist()
        time_list = list(dict.fromkeys(time_list))

        if os.path.isfile(folder + "month_values.csv"):
            mv = pandas.read_csv(folder + "month_values.csv", sep=";", decimal=",", index_col=0)
            calc_time_list = mv['time'].values.tolist()
        else:
            mv = pandas.DataFrame(columns=show_cols)
            calc_time_list = []

        current_date = time.strftime("%Y_%m", time.localtime())

        for date in time_list:
            if date in calc_time_list and date == current_date:
                index = mv.index[mv['time'] == date].tolist()
                mv.update(get_month_value(date, cv, index))
            elif date not in calc_time_list:
                mv = mv.append(get_month_value(date, cv), ignore_index=True, sort=False)

        mv.reindex(show_cols, axis=1)

        mv.to_csv(folder + "month_values.csv", sep=";", decimal=",")


if __name__ == "__main__":
    calculate_month_values()
