#include "cli/Menu.h"

#include "db/Database.h"
#include <sqlite3.h>
#include <iostream>

// void testDatabase() {
//     sqlite3* db = Database::connect();

//     if (!db) {
//         std::cout << "DB connection failed\n";
//         return;
//     }

//     std::cout << "Connected to DB!\n";

//     char* errMsg = 0;

//     // 🔥 Create table (safe if already exists)
//     const char* createTableSQL =
//         "CREATE TABLE IF NOT EXISTS test ("
//         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
//         "name TEXT);";

//     if (sqlite3_exec(db, createTableSQL, 0, 0, &errMsg) != SQLITE_OK) {
//         std::cout << "Error creating table: " << errMsg << "\n";
//         sqlite3_free(errMsg);
//     }

//     // 🔥 Insert test data
//     const char* insertSQL = "INSERT INTO test (name) VALUES ('HelloDB');";

//     if (sqlite3_exec(db, insertSQL, 0, 0, &errMsg) != SQLITE_OK) {
//         std::cout << "Insert failed: " << errMsg << "\n";
//         sqlite3_free(errMsg);
//     }

//     // 🔥 Read data back
//     const char* selectSQL = "SELECT id, name FROM test;";

//     sqlite3_stmt* stmt;

//     if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK) {
//         std::cout << "\n--- TEST TABLE ---\n";

//         while (sqlite3_step(stmt) == SQLITE_ROW) {
//             int id = sqlite3_column_int(stmt, 0);
//             const char* name = (const char*)sqlite3_column_text(stmt, 1);

//             std::cout << "ID: " << id << " | Name: " << name << "\n";
//         }
//     }

//     sqlite3_finalize(stmt);
//     sqlite3_close(db);
// }


int main() {
    Menu menu;
    menu.show();



    return 0;
}