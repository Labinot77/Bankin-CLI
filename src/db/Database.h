#pragma once
#include <sqlite3.h>

class Database {
public:
    static sqlite3* connect();
};