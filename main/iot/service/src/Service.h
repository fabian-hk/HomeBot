//
// Created by fabian on 01.06.19.
//

#ifndef C_PROJECT_SERVICE_H
#define C_PROJECT_SERVICE_H

#include <string>

void startService();
std::string controlWindowShade(std::string id, std::string values, std::string configPath);
std::string getStatus(std::string id, std::string configPath);

#endif //C_PROJECT_SERVICE_H
