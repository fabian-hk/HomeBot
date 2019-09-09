import scipy.integrate
import numpy as np
import pandas

SAMPLING_RATE = 4


def integral(x_in, y_in):
    x = []
    y = []

    # fill missing data with the mean value of the day
    mean = np.mean(x_in)

    sr = SAMPLING_RATE / 3600  # sampling rate in hours
    threshold = 4 * sr
    for i in range(len(x_in) - 1):
        if x_in[i + 1] - x_in[i] < threshold:
            x.append(x_in[i])
            y.append(y_in[i])
        else:
            xx = x_in[i] + sr
            while x_in[i + 1] - xx > sr:
                x.append(xx)
                y.append(mean)
                xx += sr

    i = scipy.integrate.simps(y, x, even='first')
    return i


if __name__ == "__main__":
    df = pandas.read_csv("../../data/powerwall/Power_2019_08_30.csv", sep="\t", decimal=",", index_col=0)
    df['time'] = df['time'].apply(
        lambda x: int(x.split(':')[0]) + (int(x.split(':')[1]) * 60 + int(x.split(':')[2])) / 3600)
    x = df['time'].values.tolist()
    y = df['home'].values.tolist()
    print(integral(x, y))
