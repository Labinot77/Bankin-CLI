#include "TransactionRepository.h"
#include "../db/Database.h"
#include <sqlite3.h>
#include <iostream>

void TransactionRepository::save(const Transaction& tx) {
    sqlite3* db = Database::connect();

    std::string sql =
        "INSERT INTO transactions (account_id, type, amount, timestamp) VALUES (?, ?, ?, ?);";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cout << "Failed to prepare statement\n";
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(stmt, 1, tx.getAccountId());
    sqlite3_bind_text(stmt, 2, tx.getType().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, tx.getAmount());
    sqlite3_bind_text(stmt, 4, tx.getTime().c_str(), -1, SQLITE_STATIC);

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

std::vector<Transaction> TransactionRepository::getByAccountId(int accountId) {
    sqlite3* db = Database::connect();

    std::vector<Transaction> result;

    std::string sql =
        "SELECT id, account_id, type, amount, timestamp "
        "FROM transactions WHERE account_id = ? ORDER BY id DESC;";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, accountId);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        result.emplace_back(
            sqlite3_column_int(stmt, 0),
            sqlite3_column_int(stmt, 1),
            (const char*)sqlite3_column_text(stmt, 2),
            sqlite3_column_double(stmt, 3),
            (const char*)sqlite3_column_text(stmt, 4)
        );
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return result;
}

std::vector<Transaction> TransactionRepository::getAll() {
    sqlite3* db = Database::connect();

    std::vector<Transaction> result;

    std::string sql =
        "SELECT id, account_id, type, amount, timestamp FROM transactions;";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        result.emplace_back(
            sqlite3_column_int(stmt, 0),
            sqlite3_column_int(stmt, 1),
            (const char*)sqlite3_column_text(stmt, 2),
            sqlite3_column_double(stmt, 3),
            (const char*)sqlite3_column_text(stmt, 4)
        );
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return result;
}