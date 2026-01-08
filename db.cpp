#include "db.h"
#include <iostream>

DB::DB(const std::string& path) : db(nullptr) {
    if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Failed to open DB\n";
        db = nullptr;
    }
}

DB::~DB() {
    if (db) sqlite3_close(db);
}

bool DB::exec(const std::string& sql) {
    char* err = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err << "\n";
        sqlite3_free(err);
        return false;
    }
    return true;
}

sqlite3* DB::handle() {
    return db;
}
