#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <unordered_map>

#include "Database.h"

Database* Database::_instance = nullptr;

Database* Database::getInstance() {
    if(!_instance) {
        _instance = new Database();
    }
    return _instance;
}

std::unordered_map<std::string, std::vector<std::string>>* Database::getIotData() {
    if(data.size() == 0) {
        loadIotData();
    }
    return &data;
}

bool Database::loadIotData() {
    getConfig();
    std::cout << "Load iot.csv from disk" << std::endl;
    std::ifstream file(config["data_storage"]+"iot.csv");
    
    std::vector<std::string> lineArr;
    std::string line;
    size_t i = 0;
    while(std::getline(file, line)) {
        if (i > 0) {
            boost::split(lineArr, line, boost::is_any_of("\t"));
            if(lineArr.size() == 5) {
                std::vector<std::string> vec(lineArr.begin()+2, lineArr.end());
                data[lineArr[1]] = vec;
                lineArr.clear();
            }
        }
        i++;
    }
    file.close();
    if (i <= 1) {
        return false;
    } 
    return true;
}

std::unordered_map<std::string, std::string>* Database::getConfig() {
    if(config.size() == 0) {
        loadConfig();
    }
    return &config;
}

bool Database::loadConfig() {
    std::cout << "Load config from disk" << std::endl;
    std::ifstream file("../bot.conf");
    
    std::vector<std::string> lineArr;
    std::string line;
    size_t i = 0;
    while(std::getline(file, line)) {
        boost::split(lineArr, line, boost::is_any_of("="));
        if(lineArr.size() == 2 && line[0] != '#') {
            config[lineArr[0]] = lineArr[1];
            lineArr.clear();
        }
        i++;
    }
    file.close();
    if (i == 0) {
        return false;
    } 
    return true;
}

bool Database::saveIotData(std::unordered_map<std::string, std::vector<std::string>>* d) {
    getConfig();

    data = (*d);

    std::ofstream file;
    file.open(config["data_storage"]+"new_iot.csv");

    // write header
    file << "	name	address	type	info" << std::endl;

    std::string tmp;
    int i=0;
    for (std::pair<std::string, std::vector<std::string>> el : (*d)) {
        tmp = el.first;
        file << i << "	" << tmp;
        for(size_t j=0; j<3; j++) {
            file << "	" << el.second[j];
        }
        file << std::endl;
        i++;
    }

    file.close();
    return true;
}