//
// Created by Fabian on 29.11.2019.
//

#ifndef TELEGRAMTEST_TELEGRAMAPI_H
#define TELEGRAMTEST_TELEGRAMAPI_H

#include <unordered_map>

#include "Database.h"


void sendMessage( std::string msg, long chatId, std::shared_ptr<Database> db );


#endif //TELEGRAMTEST_TELEGRAMAPI_H
