from powerwall.powerwall import Powerwall
from users import users
from fuelprice import fuelprice

if __name__ == "__main__":
    pw = Powerwall()
    pw.calc_current_values()
