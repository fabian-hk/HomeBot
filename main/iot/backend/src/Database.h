#ifndef DATABASE_H
#define DATABASE_H

#include <unordered_map>
#include <vector>

class Database {
private:
    static Database* _instance;
    std::unordered_map<std::string, std::vector<std::string>> data;
    std::unordered_map<std::string, std::string> config;

    Database() {}
    Database(const Database&);

     bool loadIotData();
     bool loadConfig();

public:
    static Database* getInstance();
    std::unordered_map<std::string, std::vector<std::string>>* getIotData();
    std::unordered_map<std::string, std::string>* getConfig();
    bool saveIotData(std::unordered_map<std::string, std::vector<std::string>>* d);
};

#endif