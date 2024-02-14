    //
// Created by asuka on 09.04.2023.
//

#ifndef UNTITLED_SQLITECONTROLLER_H
#define UNTITLED_SQLITECONTROLLER_H


#include <vector>
#include <string>
#include "sqlite3.h"

#define null nullptr

class SqliteController{
private:
    sqlite3 *db{};
    std::string fpath;
    inline static int callback([[maybe_unused]] void *data, int argc, char **argv, [[maybe_unused]] char **azColName);
    static std::vector<std::string> list;
public:
    SqliteController()= default;
    bool isOpen;
    [[maybe_unused]] explicit SqliteController(const std::string& path);
    std::vector<std::string> exec(const std::string& ss);
    bool open(const std::string& path);
    void close();};
#endif
