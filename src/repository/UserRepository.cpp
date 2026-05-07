#include "UserRepository.h"
#include <fstream>
#include <sstream>
#include <sqlite3.h>
#include "../db/Database.h"

int UserRepository::save(const User& user) {
    sqlite3* db = Database::connect();

    std::string sql = "INSERT INTO users (username, password) VALUES (?, ?);";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, user.getUsername().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, user.getPassword().c_str(), -1, SQLITE_STATIC);

    sqlite3_step(stmt);
    
    sqlite3_finalize(stmt);

    int userId = sqlite3_last_insert_rowid(db);
    return userId; 
    
    sqlite3_close(db);

}

std::optional<User> UserRepository::findByUsername(const std::string& username)
{
    sqlite3* db = Database::connect();

    std::string sql =
        "SELECT id, username, password FROM users WHERE username = ?;";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        User user(
            sqlite3_column_int(stmt, 0),
            (const char*)sqlite3_column_text(stmt, 1),
            (const char*)sqlite3_column_text(stmt, 2)
        );

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        return user;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return std::nullopt;
}