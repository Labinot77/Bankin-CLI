#include "UserRepository.h"
#include "../db/Database.h"
#include <sqlite3.h>
#include <iostream>

std::optional<User> UserRepository::login(const std::string& username, const std::string& password) {
    sqlite3* db = Database::connect();

    std::string sql =
        "SELECT id, username, password FROM users WHERE username = ? AND password = ?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return std::nullopt;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string uname = (const char*)sqlite3_column_text(stmt, 1);
        std::string pass = (const char*)sqlite3_column_text(stmt, 2);

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        return User(id, uname, pass);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return std::nullopt;
}