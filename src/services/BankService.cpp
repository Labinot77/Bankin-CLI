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
    Account acc(id, name, initialDeposit, false); // Save the Info in a variable

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
        if (!acc.getIsFronze()) {
            if (acc.getId() == accountId) {
                // acc.balance += amount;
                acc.deposit(amount); 
    
                int txId = txRepo.generateId();
                Transaction tx(txId, accountId, "DEPOSIT", amount);
                txRepo.save(tx);
                
                repo.updateAll(accounts);
                std::cout << "Deposit successful!\n";
                return;
            };
        } else {
            std::cout << "Account is frozen. \n";
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
        if (acc.getId() == accountId) {
            if (!acc.withdraw(amount)) {
                std::cout << "Withdraw failed.\n";
                return;
            }
        
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

    for (auto& acc : accounts) {
        if (acc.getId() == fromId) fromAcc = &acc;
        if (acc.getId() == toId) toAcc = &acc;
    }

    if (!fromAcc || !toAcc) {
        std::cout << "One or both accounts not found.\n";
        return;
    }

    if (fromAcc->getIsFronze() || toAcc->getIsFronze()) {
        std::cout << "One of the accounts is frozen. \n";
        return;
    }

    if (!fromAcc->withdraw(amount)) {
        std::cout << "Insufficient funds.\n";
        return;
    }

    toAcc->deposit(amount);


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

    for (const auto& tx : transactions) {
        std::cout << "ID: " << tx.getId()
                  << " | Type: " << tx.getType()
                  << " | Amount: " << tx.getAmount()
                  << "\n";
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
        std::cout << "ID: " << acc.getId()
                  << " | Owner: " << acc.getOwnerName() << "\n"
                  << " | Balance: " << acc.getBalance() << "\n"
                  << " | Frozen: " << (acc.getIsFronze() ? "True" : "False");
    }
}

// Admin

void BankService::freezeAccount(int accountId) {
    // Pull all the account because after that we will update them
    std::vector<Account> accounts = repo.getAll();

    for (auto& acc : accounts) {
        if (acc.getId() == accountId) {
            acc.setFrozen(true);
            repo.updateAll(accounts);
            std::cout << "Account is frozen. \n";
            return;
        }
    }

     std::cout << "Account not found.\n";
}

void BankService::unfreezeAccount(int accountId) {
    // Pull all the account because after that we will update them
    std::vector<Account> accounts = repo.getAll();

    for (auto& acc : accounts) {
        if (acc.getId() == accountId) {
            acc.setFrozen(false);
            repo.updateAll(accounts);
            std::cout << "Account is not frozen anymore. \n";
            return;
        }
    }

     std::cout << "Account not found.\n";
}