#ifndef MYLIBRARY_CONFIGLOADER_H
#define MYLIBRARY_CONFIGLOADER_H
#include <string>
#include <map>
#include <variant>
#include <vector>
#define UL unsigned long
class ConfigLoader {
private:
    std::string data;
    std::vector<std::string> configs;
    std::vector<std::string> keys;
    std::vector<std::string> strings;
    std::vector<std::string> arrays;

    std::string restringer(std::string _data);
    std::string unstringer(std::string _data);
    std::string reconfigur(std::string _data);
    std::string rearray(std::string _data);
    std::vector<std::variant<int,float,bool,std::string,ConfigLoader>> unarray(int i);
#define VALUE std::variant<int,float,bool,std::string,ConfigLoader,std::vector<std::variant<int,float,bool,std::string,ConfigLoader>>>
    std::map<std::string,VALUE> fullData;
public:
    explicit ConfigLoader(std::string data);
    explicit ConfigLoader(std::string data,bool parsing);
    ConfigLoader()= default;
    void loadFromPath(std::string path);
    void saveToPath(std::string path);
    void parseConfig(const std::string & data);
    void parseConfig();

    VALUE get(const std::string& key);
    std::map<std::string,VALUE> getFullData();


    [[maybe_unused]] std::string getString(const std::string& key);
    [[maybe_unused]] bool getBool(const std::string& key);
    [[maybe_unused]] int getInt(const std::string& key);
    [[maybe_unused]] float getFloat(const std::string& key);
    [[maybe_unused]] ConfigLoader getSubConfig(const std::string& key);
    [[maybe_unused]] std::vector<std::variant<int,float,bool,std::string,ConfigLoader>> getArray(const std::string& key);

    [[maybe_unused]] std::string getStringFromArr(const std::string& key,int index);
    [[maybe_unused]] bool getBoolFromArr(const std::string& key, int index);
    [[maybe_unused]] int getIntFromArr(const std::string& key,int index);
    [[maybe_unused]] float getFloatFromArr(const std::string& key,int index);
    [[maybe_unused]] ConfigLoader getSubConfigFromArr(const std::string& key,int index);

    std::string getData();
    std::string getDataForSave(std::string index);
    void set(std::string key,VALUE value);
    void finalize();
};
#endif