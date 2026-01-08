#pragma once
#include <string>
#include <sqlite3.h>

class DB {
public:
    DB(const std::string& path);
    ~DB();

    bool exec(const std::string& sql);
    sqlite3* handle();

private:
    sqlite3* db;
};
