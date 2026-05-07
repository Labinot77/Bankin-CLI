#include "Database.h"
#include <iostream>

sqlite3* Database::connect() {
    sqlite3* db;

    if (sqlite3_open("bank.db", &db)) {
        std::cout << "Error opening database\n";
        return nullptr;
    }

    return db;
}