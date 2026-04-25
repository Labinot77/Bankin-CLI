#pragma once
#include "../repository/AccountRepository.h"
#include "../repository/TransactionRepository.h"

class BankService {
private:
    AccountRepository repo;
    TransactionRepository txRepo;

public:
    void createAccount(const std::string& name, double initialDeposit);
    void deposit(int accountId, double amount);
    void withdraw(int accountId, double amount);
    void transfer(int fromId, int toId, double amount);

    void showTransactions(int accountId);

    // Debug
    void showAllAccounts();
};