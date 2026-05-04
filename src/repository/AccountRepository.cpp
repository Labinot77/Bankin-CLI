#include "AccountRepository.h"
#include <fstream>
#include <sstream>

std::vector<Account> AccountRepository::getAll() {
    std::vector<Account> accounts;
    std::ifstream file("data/accounts.txt");

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, userIdStr, name, balanceStr, frozenStr;

        getline(ss, idStr, ',');
        getline(ss, userIdStr, ',');
        getline(ss, name, ',');
        getline(ss, balanceStr, ',');
        getline(ss, frozenStr, ',');

        accounts.emplace_back(
            stoi(idStr),
            stoi(userIdStr),
            name,
            stod(balanceStr),
            frozenStr == "1"
        );
    }

    return accounts;
}

void AccountRepository::save(const Account& account) {
    std::ofstream file("data/accounts.txt", std::ios::app);

    file << account.getId() << ","
         << account.getUserId() << ','
         << account.getOwnerName() << ","
         << account.getBalance() << "\n";
}

int AccountRepository::generateId() {
    std::vector<Account> accounts = getAll();
    return accounts.empty() ? 1 : accounts.back().getId() + 1;
}

Account AccountRepository::getById(int id) {
    std::vector<Account> accounts = getAll();

    for (auto& acc : accounts) {
        if (acc.getId() == id) {
            return acc;
        }
    }

    throw std::runtime_error("Account not found");
}

void AccountRepository::updateAll(const std::vector<Account>& accounts) {
    std::ofstream file("data/accounts.txt"); // overwrite

    for (const auto& acc : accounts) {
    file << acc.getId() << ","
     << acc.getUserId() << ","
     << acc.getOwnerName() << ","
     << acc.getBalance() << ","
     << acc.getIsFronze() << "\n";
    }
}