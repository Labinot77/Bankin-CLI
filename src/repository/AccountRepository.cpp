#include "AccountRepository.h"
#include "../db/Database.h"
#include <sqlite3.h>
#include <iostream>
#include <optional>

std::vector<Account> AccountRepository::getAll() {
    sqlite3* db = Database::connect();

    std::vector<Account> accounts;

    std::string sql = "SELECT id, user_id, name, balance, is_frozen FROM accounts;";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        accounts.emplace_back(
            sqlite3_column_int(stmt, 0),
            sqlite3_column_int(stmt, 1),
            (const char*)sqlite3_column_text(stmt, 2),
            sqlite3_column_double(stmt, 3),
            sqlite3_column_int(stmt, 4)
        );
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return accounts;
}

std::vector<Account> AccountRepository::getAccountsForUser(int userId) {
    sqlite3* db = Database::connect();

    std::vector<Account> result;

    std::string sql =
        "SELECT id, user_id, name, balance, is_frozen "
        "FROM accounts WHERE user_id = ?;";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, userId);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        result.emplace_back(
            sqlite3_column_int(stmt, 0),
            sqlite3_column_int(stmt, 1),
            (const char*)sqlite3_column_text(stmt, 2),
            sqlite3_column_double(stmt, 3),
            sqlite3_column_int(stmt, 4)
        );
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return result;
}

// Only created new accounts, doesnt update
void AccountRepository::save(const Account& account) {
    sqlite3* db = Database::connect();

    std::string sql =
        "INSERT INTO accounts (user_id, name, balance, is_frozen) VALUES (?, ?, ?, ?);";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, account.getUserId());
    sqlite3_bind_text(stmt, 2, account.getOwnerName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, account.getBalance());
    sqlite3_bind_int(stmt, 4, account.getIsFronze());

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

// Updates existing accounts
void AccountRepository::update(const Account& account)
{
    sqlite3* db = Database::connect();

    std::string sql =
        "UPDATE accounts "
        "SET balance = ?, is_frozen = ? "
        "WHERE id = ?;";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_double(stmt, 1, account.getBalance());
    sqlite3_bind_int(stmt, 2, account.getIsFronze());
    sqlite3_bind_int(stmt, 3, account.getId());

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cout << "Update failed: "
                  << sqlite3_errmsg(db)
                  << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

// Gets users bank account by ID
std::optional<Account> AccountRepository::getById(int id)
{
    sqlite3* db = Database::connect();

    std::string sql =
        "SELECT id, user_id, name, balance, is_frozen "
        "FROM accounts WHERE id = ?;";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Account acc(
            sqlite3_column_int(stmt, 0),
            sqlite3_column_int(stmt, 1),
            (const char*)sqlite3_column_text(stmt, 2),
            sqlite3_column_double(stmt, 3),
            sqlite3_column_int(stmt, 4)
        );

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        return acc;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return std::nullopt;
}
