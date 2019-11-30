#ifndef DATABASE_H
#define DATABASE_H

#include <unordered_map>
#include <vector>
#include <memory>

class Database {
private:
    static std::shared_ptr<Database> _instance;
    std::string configFilePath;
    std::unordered_map<std::string, std::vector<std::string>> data;
    std::unordered_map<std::string, std::string> config;

    explicit Database( std::string&& path );

     bool loadIotData();
     bool loadConfig();

public:
    // copy operations
    Database( const Database& ) = delete;
    Database& operator=( const Database& ) = delete;

    ~Database() = default;

    // move operations
    Database( Database&& ) = default;
    Database& operator=( Database&& ) = default;

    static std::shared_ptr<Database> getInstance( std::string&& path );
    std::unordered_map<std::string, std::vector<std::string>>* getIotData();
    bool getIotDataByInfo(const char* info, std::vector<std::string> *ret);
    std::unordered_map<std::string, std::string>* getConfig();
    bool saveIotData(std::unordered_map<std::string, std::vector<std::string>>* d);
    std::string operator[]( std::string&& key );

    void setConfigFilePath(std::string path);
};

#endif