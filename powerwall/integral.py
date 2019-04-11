import scipy.integrate
import pandas


def integral(x, y):
    i = scipy.integrate.simps(y, x, even='first')
    return i


if __name__ == "__main__":
    df = pandas.read_csv("data/Power_2018_12_01.csv", sep="\t", decimal=",", index_col=0)
    df['time'] = df['time'].apply(
        lambda x: int(x.split(':')[0]) + (int(x.split(':')[1]) * 60 + int(x.split(':')[2])) / 3600)
    x = df['time'].values.tolist()
    y = df['home'].values.tolist()
    print(integral(x, y))
