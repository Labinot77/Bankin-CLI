#include "AccountRepository.h"
#include <fstream>
#include <sstream>

std::vector<Account> AccountRepository::getAll() {
    std::vector<Account> accounts;
    std::ifstream file("data/accounts.txt");

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, balanceStr;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, balanceStr, ',');

        accounts.emplace_back(
            stoi(idStr),
            name,
            stod(balanceStr)
        );
    }

    return accounts;
}

void AccountRepository::save(const Account& account) {
    std::ofstream file("data/accounts.txt", std::ios::app);

    file << account.id << ","
         << account.ownerName << ","
         << account.balance << "\n";
}

int AccountRepository::generateId() {
    std::vector<Account> accounts = getAll();
    return accounts.empty() ? 1 : accounts.back().id + 1;
}

Account AccountRepository::getById(int id) {
    std::vector<Account> accounts = getAll();

    for (auto& acc : accounts) {
        if (acc.id == id) {
            return acc;
        }
    }

    throw std::runtime_error("Account not found");
}

void AccountRepository::updateAll(const std::vector<Account>& accounts) {
    std::ofstream file("data/accounts.txt"); // overwrite

    for (const auto& acc : accounts) {
        file << acc.id << ","
             << acc.ownerName << ","
             << acc.balance << "\n";
    }
}