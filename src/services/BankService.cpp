#include "BankService.h"
#include <iostream>
#include <fstream>
#include <sstream>


void BankService::createAccount(const std::string& name, double initialDeposit) {
    if (initialDeposit < 0) {
        std::cout << "Invalid deposit amount.\n";
        return;
    }

    int id = repo.generateId();
    Account acc(id, name, initialDeposit);

    repo.save(acc);

    std::cout << "Account created successfully!\n";
    std::cout << "Account ID: " << id << "\n";
}

void BankService::deposit(int accountId, double amount) {
    if (amount <= 0) {
        std::cout << "Invalid amount.\n";
        return;
    }

    std::vector<Account> accounts = repo.getAll();

    for (auto& acc : accounts) {
        if (acc.id == accountId) {
            acc.balance += amount;

            int txId = txRepo.generateId();
            Transaction tx(txId, accountId, "DEPOSIT", amount);
            txRepo.save(tx);
            
            repo.updateAll(accounts);
            std::cout << "Deposit successful!\n";
            return;
        }
    }

    std::cout << "Account not found.\n";
}

void BankService::withdraw(int accountId, double amount) {
    if (amount <= 0) {
        std::cout << "Invalid Amount" << std::endl;
        return;
    }

    std::vector<Account> accounts = repo.getAll();

    for (auto& acc : accounts) {
        if (acc.id == accountId) {
            if (acc.balance < amount) {
                std::cout << "Insufficient funds.\n";
                return;
            };
            
            acc.balance -= amount;

            int txId = txRepo.generateId();
            Transaction tx(txId, accountId, "WITHDRAW", amount);
            txRepo.save(tx);

            repo.updateAll(accounts);

            std::cout << "Deposit successful!";
            return;
        }
    }

    std::cout << "Account not found.\n";
};

void BankService::transfer(int fromId, int toId, double amount) {
    if (amount <= 0) {
        std::cout << "Invalid amount.\n";
        return;
    }

    if (fromId == toId) {
        std::cout << "Cannot transfer to the same account.\n";
        return;
    }

    auto accounts = repo.getAll();

    Account* fromAcc = nullptr;
    Account* toAcc = nullptr;

    // 🔍 Find both accounts
    for (auto& acc : accounts) {
        if (acc.id == fromId) fromAcc = &acc;
        if (acc.id == toId) toAcc = &acc;
    }

    if (!fromAcc || !toAcc) {
        std::cout << "One or both accounts not found.\n";
        return;
    }

    // 💰 Check balance
    if (fromAcc->balance < amount) {
        std::cout << "Insufficient funds.\n";
        return;
    }

    // 🔄 Apply transfer
    fromAcc->balance -= amount;
    toAcc->balance += amount;

    // 🔥 LOG BOTH TRANSACTIONS
    int txId1 = txRepo.generateId();
    Transaction outTx(txId1, fromId, "TRANSFER_OUT", amount);
    txRepo.save(outTx);

    int txId2 = txRepo.generateId();
    Transaction inTx(txId2, toId, "TRANSFER_IN", amount);
    txRepo.save(inTx);

    repo.updateAll(accounts);

    std::cout << "Transfer successful!\n";
}

void BankService::showTransactions(int accountId) {
    auto transactions = txRepo.getByAccountId(accountId);

    if (transactions.empty()) {
        std::cout << "No transactions found.\n";
        return;
    }

    for (const auto& tx : transactions) {
        std::cout << "ID: " << tx.id
                  << " | Type: " << tx.type
                  << " | Amount: " << tx.amount << "\n";
    }
}




// Debug

void BankService::showAllAccounts() {
    auto accounts = repo.getAll();

    if(accounts.empty()) {
        std::cout << "No accounts found.\n";
        return;
    }

    std::cout << "All accounts.\n";

    for (const auto& acc : accounts) {
        std::cout << "ID: " << acc.id
                  << " | Owner: " << acc.ownerName << "\n";
                //   << " | Balance: " << acc.balance << "\n";
    }
}