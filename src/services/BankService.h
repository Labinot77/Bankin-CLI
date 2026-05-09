#pragma once
#include "../repository/AccountRepository.h"
#include "../repository/TransactionRepository.h"
#include "../repository/AuditLogRepository.h"

class BankService {
private:
    AccountRepository repo;
    TransactionRepository txRepo;
    // AuditLogRepository auditRepo;
    
public:
    void createAccount(int userId, const std::string& name, double initialDeposit);    
    void deposit(int accountId, double amount);
    void withdraw(int accountId, double amount);
    void transfer(int fromId, int toId, double amount);

    void showTransactions(int accountId);

    // void showAccountsByUser(int userId);

    // Debug
    void showUserAccounts(int userId);
    std::vector<Account> getAccountsByUser(int userId);

    void printAccounts(const std::vector<Account>& accs);

    // // Admin;
    // void freezeAccount(int accountId);
    // void unfreezeAccount(int accountId);

};