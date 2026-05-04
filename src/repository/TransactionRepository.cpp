#include "TransactionRepository.h"
#include <fstream>
#include <sstream>

void TransactionRepository::save(const Transaction& tx) {
    std::ofstream file("data/transactions.txt", std::ios::app);

    file << tx.getId() << ","
         << tx.getAccountId() << ","
         << tx.getType() << ","
         << tx.getAmount() << ","
         << tx.getTime() << "\n";
}

std::vector<Transaction> TransactionRepository::getByAccountId(int accountId) {
    std::vector<Transaction> transactions = getAll();
    std::vector<Transaction> result;

    for (const auto& tx : transactions) {
        if (tx.getAccountId() == accountId) {
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

        std::string idStr, accIdStr, type, amountStr, timestamp;

        getline(ss, idStr, ',');
        getline(ss, accIdStr, ',');
        getline(ss, type, ',');
        getline(ss, amountStr, ',');
        getline(ss, timestamp, ',');

        transactions.emplace_back(
            stoi(idStr),
            stoi(accIdStr),
            type,
            stod(amountStr),
            timestamp
        );
    }

    return transactions;
}

int TransactionRepository::generateId() {
    std::vector<Transaction> transactions = getAll();
    return transactions.empty() ? 1 : transactions.back().getId() + 1;
}