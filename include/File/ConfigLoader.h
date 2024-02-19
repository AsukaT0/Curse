#ifndef MYLIBRARY_CONFIGLOADER_H
#define MYLIBRARY_CONFIGLOADER_H

#include <string>
#include <map>
#include <variant>
#include <vector>
#define VALUE std::variant<int,bool,std::string,ConfigLoader,std::vector<std::variant<int,bool,std::string,ConfigLoader>>>
#define UL unsigned long
class ConfigLoader {
private:
    std::map<std::string,VALUE> fullData;
    std::string data;
    std::vector<std::string> parseObj(const std::string &_data);
    void parseValues(const std::string &_data);
public:
    explicit ConfigLoader(std::string data);
    ConfigLoader()= default;

    [[maybe_unused]] void loadFromPath(std::string path);
    void saveToPath(std::string path);
    void parseConfig(const std::string & data);
    void parseConfig();

    VALUE get(const std::string& key);

    [[maybe_unused]] std::string getString(const std::string& key);
    [[maybe_unused]] bool getBool(const std::string& key);
    [[maybe_unused]] int getInt(const std::string& key);
    [[maybe_unused]] ConfigLoader getSubConfig(const std::string& key);
    [[maybe_unused]] std::vector<std::variant<int,bool,std::string,ConfigLoader>> getArray(const std::string& key);
};



#endif