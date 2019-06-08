//
// Created by fabian on 01.06.19.
//

#ifndef C_PROJECT_SERVICE_H
#define C_PROJECT_SERVICE_H

#include <string>

void startService();
std::string controlWindowShade(std::string id, std::string values);
std::string getStatus(const std::string id);

#endif //C_PROJECT_SERVICE_H
