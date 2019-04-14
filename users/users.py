import os

import config
from users import users_pb2

folder = config.data_folder + 'users/'


def add_user(chat_id, username=None, privs=3, longitude=config.default_longitude,
             latitude=config.default_latitude):
    user_data = users_pb2.UserManagement()

    if os.path.isfile(folder + 'database.db'):
        f = open(folder + 'database.db', 'rb')
        user_data.ParseFromString(f.read())
        f.close()

    new_user = user_data.users.add()

    new_user.chat_id = chat_id
    if username:
        new_user.username = username
    if privs != 3:
        new_user.privs = privs

    new_user.longitude = longitude
    new_user.latitude = latitude

    f = open(folder + 'database.db', "wb")
    f.write(user_data.SerializeToString())
    f.close()


def save_users(users: users_pb2.UserManagement):
    f = open(folder + 'database.db', "wb")
    f.write(users.SerializeToString())
    f.close()


def show_users():
    f = open(folder + 'database.db', 'rb')
    user_data = users_pb2.UserManagement()
    user_data.ParseFromString(f.read())
    f.close()

    print(user_data)


def load_users():
    f = open(folder + 'database.db', 'rb')
    user_data = users_pb2.UserManagement()
    user_data.ParseFromString(f.read())
    return user_data


def change_position(chat_id, longitude, latitude):
    f = open(folder + 'database.db', 'rb')
    user_data = users_pb2.UserManagement()
    user_data.ParseFromString(f.read())
    f.close()

    for user in user_data.users:
        if user.chat_id == chat_id:
            user.longitude = longitude
            user.latitude = latitude
            user.lowest_price = user.price_limit

    f = open(folder + 'database.db', "wb")
    f.write(user_data.SerializeToString())
    f.close()


def change_fuel_price_limit(chat_id, limit):
    f = open(folder + 'database.db', 'rb')
    user_data = users_pb2.UserManagement()
    user_data.ParseFromString(f.read())
    f.close()

    for user in user_data.users:
        if user.chat_id == chat_id:
            user.price_limit = limit
            user.lowest_price = limit

    f = open(folder + 'database.db', "wb")
    f.write(user_data.SerializeToString())
    f.close()


def reset_price_alert():
    users = load_users()
    for user in users.users:
        user.lowest_price = user.price_limit
    save_users(users)


def get_fuel_prices(chat_id):
    f = open(folder + 'database.db', 'rb')
    user_data = users_pb2.UserManagement()
    user_data.ParseFromString(f.read())
    f.close()

    for user in user_data.users:
        if user.chat_id == chat_id:
            return user.fuel_prices


def user_lists():
    f = open(folder + 'database.db', 'rb')
    user_data = users_pb2.UserManagement()
    user_data.ParseFromString(f.read())
    user_lst = []
    admin_lst = []
    for user in user_data.users:
        if user.chat_id != -1:
            user_lst.append(user.chat_id)
            if user.privs == 0:
                admin_lst.append(user.chat_id)
    return user_lst, admin_lst


def user_by_id(chat_id):
    f = open(folder + 'database.db', 'rb')
    user_data = users_pb2.UserManagement()
    user_data.ParseFromString(f.read())
    f.close()

    for user in user_data.users:
        if user.chat_id == chat_id:
            return user


def change_user(chat_id, privs):
    f = open(folder + 'database.db', 'rb')
    user_data = users_pb2.UserManagement()
    user_data.ParseFromString(f.read())
    f.close()

    for user in user_data.users:
        if user.chat_id == chat_id:
            user.privs = privs

    f = open(folder + 'database.db', "wb")
    f.write(user_data.SerializeToString())
    f.close()