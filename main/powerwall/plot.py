import os
import sys
import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt
import pandas
import configparser
import argparse
import io


def load_config():
    parser = configparser.ConfigParser()
    config_file = open(os.path.dirname(os.path.abspath(__file__)) + "/../bot.conf", "r")
    parser.read_file(config_file)
    return parser


def plot_day(day: str, begin: int, end: int):
    """
    Function to plot a certain cutting of a day.
    :param day: format YYYY_MM_DD
    :param begin: first hour as integer
    :param end: last hour as integer
    """
    config = load_config()
    file = config['paths']['data_folder'] + 'powerwall/Power_' + day + ".csv"
    df = pandas.read_csv(file, sep="\t", decimal=",", index_col=0)
    df['time'] = df['time'].apply(
        lambda x: int(x.split(':')[0]) + (int(x.split(':')[1]) * 60 + int(x.split(':')[2])) / 3600)

    plot_data = df.loc[(df['time'] >= begin) & (df['time'] <= end)]

    show_cols = ["home", "grid", "solar", "powerwall"]
    f, axarr = plt.subplots(2, 2)
    i = 0
    j = 0
    for c in show_cols:
        axarr[i, j].plot(plot_data['time'], plot_data[c])
        axarr[i, j].set_title(c.title())
        axarr[i, j].set_ylabel("Watt")
        axarr[i, j].set_xlabel("Hours")
        if i == 0 and j == 0:
            j = 1
            i = 0
        elif i == 0 and j == 1:
            i = 1
            j = 0
        elif i == 1 and j == 0:
            j = 1

    f.subplots_adjust(hspace=0.7, wspace=0.5)
    f.suptitle(day)

    f = io.BytesIO()
    plt.savefig(f, format='svg')
    plt.close()
    sys.stdout.buffer.write(f.getvalue())


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Script to plot cuttings of a day')
    parser.add_argument('day', type=str, help='Day in format YYYY_MM_DD')
    parser.add_argument('begin', type=int, help='Hour to start the plot')
    parser.add_argument('end', type=int, help='Last hour to plot')
    args = parser.parse_args()

    plot_day(args.day, args.begin, args.end)
