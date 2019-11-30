//
// Created by Fabian on 29.11.2019.
//

#include <libtelegram/sender.h>

#include "TelegramAPI.h"

void sendMessage( const std::string msg, const long chatId, std::shared_ptr<Database> db ) {
    telegram::sender sender{ (*db)["access_token"] };
    sender.send_message( chatId, msg );
}