#include "TransactionRepository.h"
#include <fstream>
#include <sstream>

void TransactionRepository::save(const Transaction& tx) {
    std::ofstream file("data/transactions.txt", std::ios::app);

    file << tx.id << ","
         << tx.accountId << ","
         << tx.type << ","
         << tx.amount << "\n";
}

std::vector<Transaction> TransactionRepository::getByAccountId(int accountId) {
    std::vector<Transaction> transactions = getAll();
    std::vector<Transaction> result;

    for (const auto& tx : transactions) {
        if (tx.accountId == accountId) {
            result.push_back(tx);
        }
    }

    return result;
}

std::vector<Transaction> TransactionRepository::getAll() {
    std::vector<Transaction> transactions;
    std::ifstream file("data/transactions.txt");

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);

        std::string idStr, accIdStr, type, amountStr;

        getline(ss, idStr, ',');
        getline(ss, accIdStr, ',');
        getline(ss, type, ',');
        getline(ss, amountStr, ',');

        transactions.emplace_back(
            stoi(idStr),
            stoi(accIdStr),
            type,
            stod(amountStr)
        );
    }

    return transactions;
}

int TransactionRepository::generateId() {
    std::vector<Transaction> transactions = getAll();
    return transactions.empty() ? 1 : transactions.back().id + 1;
}