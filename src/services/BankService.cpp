#include "BankService.h"
#include <iostream>
#include <fstream>
#include <sstream>


#include <ctime>
#include <sstream>

std::string getCurrentTimestamp() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    std::stringstream ss;

    ss << (1900 + localTime->tm_year) << "-"
       << (1 + localTime->tm_mon) << "-"
       << localTime->tm_mday << " "
       << localTime->tm_hour << ":"
       << localTime->tm_min << ":"
       << localTime->tm_sec;

    return ss.str();
}

void BankService::createAccount(int userId, const std::string& name, double initialDeposit)
{
    if (initialDeposit < 0)
    {
        std::cout << "Invalid deposit amount.\n";
        return;
    }

    int id = repo.generateId();
    Account acc(id, userId, name, initialDeposit, false); // Save the Info in a variable

    repo.save(acc);

    std::cout << "Account created successfully!\n";
    std::cout << "Account ID: " << id << "\n";
}

std::vector<Account> BankService::getAccountsByUser(int userId) {
    auto accounts = repo.getAll();
    std::vector<Account> result;

    for (const auto& acc : accounts) {
        if (acc.getUserId() == userId) {
            result.push_back(acc);
        }
    }

    return result;
}

void BankService::deposit(int accountId, double amount)
{
    if (amount <= 0)
    {
        std::cout << "Invalid amount.\n";
        return;
    }

    std::vector<Account> accounts = repo.getAll();

    for (auto &acc : accounts)
    {
        if (!acc.getIsFronze())
        {
            if (acc.getId() == accountId)
            {
                // acc.balance += amount;
                acc.deposit(amount);

                int txId = txRepo.generateId();
                Transaction tx(txId, accountId, "DEPOSIT", amount, getCurrentTimestamp());
                txRepo.save(tx);

                repo.updateAll(accounts);
                std::cout << "Deposit successful!\n";
                return;
            };
        }
        else
        {
            std::cout << "Account is frozen. \n";
            return;
        }
    }

    std::cout << "Account not found.\n";
}

void BankService::withdraw(int accountId, double amount)
{
    if (amount <= 0)
    {
        std::cout << "Invalid Amount" << std::endl;
        return;
    }

    std::vector<Account> accounts = repo.getAll();

    for (auto &acc : accounts)
    {
        if (acc.getId() == accountId)
        {
            if (!acc.withdraw(amount))
            {
                std::cout << "Withdraw failed.\n";
                return;
            }

            int txId = txRepo.generateId();
            Transaction tx(txId, accountId, "WITHDRAW", amount, getCurrentTimestamp());
            txRepo.save(tx);

            repo.updateAll(accounts);

            std::cout << "Deposit successful!";
            return;
        }
    }

    std::cout << "Account not found.\n";
};

void BankService::transfer(int fromId, int toId, double amount)
{
    if (amount <= 0)
    {
        std::cout << "Invalid amount.\n";
        return;
    }

    if (fromId == toId)
    {
        std::cout << "Cannot transfer to the same account.\n";
        return;
    }

    auto accounts = repo.getAll();

    Account *fromAcc = nullptr;
    Account *toAcc = nullptr;

    for (auto &acc : accounts)
    {
        if (acc.getId() == fromId)
            fromAcc = &acc;
        if (acc.getId() == toId)
            toAcc = &acc;
    }

    if (!fromAcc || !toAcc)
    {
        std::cout << "One or both accounts not found.\n";
        return;
    }

    if (fromAcc->getIsFronze() || toAcc->getIsFronze())
    {
        std::cout << "One of the accounts is frozen. \n";
        return;
    }

    if (!fromAcc->withdraw(amount))
    {
        std::cout << "Insufficient funds.\n";
        return;
    }

    toAcc->deposit(amount);

    int txId1 = txRepo.generateId();
    Transaction outTx(txId1, fromId, "TRANSFER_OUT", amount, getCurrentTimestamp());
    txRepo.save(outTx);

    int txId2 = txRepo.generateId();
    Transaction inTx(txId2, toId, "TRANSFER_IN", amount, getCurrentTimestamp());
    txRepo.save(inTx);

    repo.updateAll(accounts);

    std::cout << "Transfer successful!\n";
}

void BankService::showTransactions(int accountId)
{
    auto transactions = txRepo.getByAccountId(accountId);

    for (const auto &tx : transactions)
    {
        std::cout << "[" << tx.getTime() << "] "
                  << tx.getType()
                  << " | Amount: " << tx.getAmount()
                  << "\n";
    }
}

// Debug

void BankService::showAllAccounts()
{
    auto accounts = repo.getAll();

    if (accounts.empty())
    {
        std::cout << "No accounts found.\n";
        return;
    }

    std::cout << "All accounts.\n";

    for (const auto &acc : accounts)
    {
        std::cout << "ID: " << acc.getId()
                  << " | Owner: " << acc.getOwnerName() << "\n"
                  << " | Balance: " << acc.getBalance() << "\n"
                  << " | Frozen: " << (acc.getIsFronze() ? "True" : "False");
    }
}

// Admin

void BankService::freezeAccount(int accountId) {
    auto accounts = repo.getAll();

    for (auto& acc : accounts) {
        if (acc.getId() == accountId) {

            if (acc.getIsFronze()) {
                std::cout << "Already frozen.\n";
                return;
            }

            acc.setFrozen(true);
            repo.updateAll(accounts);

            int logId = auditRepo.generateId();
            AuditLog log(
                logId,
                "FROZE account " + std::to_string(accountId),
                getCurrentTimestamp()
            );

            auditRepo.save(log);

            std::cout << "Account frozen.\n";
            return;
        }
    }

    std::cout << "Account not found.\n";
}

void BankService::unfreezeAccount(int accountId) {
    auto accounts = repo.getAll();

    for (auto& acc : accounts) {
        if (acc.getId() == accountId) {

            if (!acc.getIsFronze()) {
                std::cout << "Already active.\n";
                return;
            }

            acc.setFrozen(false);
            repo.updateAll(accounts);

            int logId = auditRepo.generateId();
            AuditLog log(
                logId,
                "UNFROZE account " + std::to_string(accountId),
                getCurrentTimestamp()
            );

            auditRepo.save(log);

            std::cout << "Account unfrozen.\n";
            return;
        }
    }

    std::cout << "Account not found.\n";
}