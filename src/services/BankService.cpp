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

    Account acc(0, userId, name, initialDeposit, false); // Save the Info in a variable

    repo.save(acc);

    std::cout << "Account created successfully!\n";
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
    try {
 if (amount <= 0)
    {
        std::cout << "Invalid amount.\n";
        return;
    }

    auto acc = repo.getById(accountId);

    if (!acc) {
           std::cout << "Bank account doesn't exist. \n";
        return; 
    }
    // if (acc.getIsFronze()) {
    //     std::cout << "Account is fronze." << std::endl;
    //     return;
    // };

    Account updatedAcc = *acc;

    updatedAcc.deposit(amount);
    repo.update(updatedAcc);


    std::string time = getCurrentTimestamp();
    Transaction Txin(0, accountId, "DEPOSIT", amount, time);
    txRepo.save(Txin);

    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void BankService::withdraw(int accountId, double amount)
{
    try {
            if (amount <= 0)
    {
        std::cout << "Invalid Amount" << std::endl;
        return;
    }

        auto acc = repo.getById(accountId);

        if (!acc) {
            std::cout << "Bank account doesn't exist. \n";
            return; 
        }

        Account updatedAcc = *acc;

        if (!updatedAcc.withdraw(amount)) {
             std::cout << "Withdraw failed.\n";
            return;
        };

        updatedAcc.withdraw(amount);
        repo.update(updatedAcc);

        std::cout << "Withraw successful!";
        return;
        
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    };
};

void BankService::transfer(int fromId, int toId, double amount)
{
    if (amount <= 0)
    {
        std::cout << "Invalid amount.\n";
        return;
    }

    try {
    auto fromAcc = repo.getById(fromId);
    auto toAcc = repo.getById(toId);
    
    if (!fromAcc || !toAcc) {
        std::cout << "One of the accounts doesn't exist. \n";
        return;
    };

    Account updatedFromAcc = *fromAcc;
    Account updatedToAcc = *toAcc;

    if (updatedFromAcc.getId() == updatedToAcc.getId()) {
        std::cout << "Cannot transfer to the same account.\n";
        return;
    }

    // if (fromAcc.getIsFronze() || toAcc.getIsFronze())
    // {
    //     std::cout << "One of the accounts is frozen. \n";
    //     return;
    // }

    if (!updatedFromAcc.withdraw(amount))
    {
        std::cout << "Insufficient funds.\n";
        return;
    }

    updatedToAcc.deposit(amount);

    std::string time = getCurrentTimestamp();
    Transaction outTx(0, fromId, "TRANSFER_OUT", amount, time);
    txRepo.save(outTx);

    Transaction inTx(0, toId, "TRANSFER_IN", amount, time);
    txRepo.save(inTx);


    repo.update(updatedFromAcc);
    repo.update(updatedToAcc);

    std::cout << "Transfer successful!\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
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


void BankService::showUserAccounts(int userId) {
    auto accs = getAccountsByUser(userId);

      if (accs.empty()) {
        std::cout << "No accounts for this user";
        return;
        };

        std::cout << "You have: " << accs.size() - 1 << std::endl;
        printAccounts(accs);
}

// Admin

// void BankService::freezeAccount(int accountId) {
//     auto accounts = repo.getAll();

//     for (auto& acc : accounts) {
//         if (acc.getId() == accountId) {

//             if (acc.getIsFronze()) {
//                 std::cout << "Already frozen.\n";
//                 return;
//             }

//             acc.setFrozen(true);
//             repo.updateAll(accounts);

//             int logId = auditRepo.generateId();
//             AuditLog log(
//                 logId,
//                 "FROZE account " + std::to_string(accountId),
//                 getCurrentTimestamp()
//             );

//             auditRepo.save(log);

//             std::cout << "Account frozen.\n";
//             return;
//         }
//     }

//     std::cout << "Account not found.\n";
// }

// void BankService::unfreezeAccount(int accountId) {
//     auto accounts = repo.getAll();

//     for (auto& acc : accounts) {
//         if (acc.getId() == accountId) {

//             if (!acc.getIsFronze()) {
//                 std::cout << "Already active.\n";
//                 return;
//             }

//             acc.setFrozen(false);
//             repo.updateAll(accounts);

//             int logId = auditRepo.generateId();
//             AuditLog log(
//                 logId,
//                 "UNFROZE account " + std::to_string(accountId),
//                 getCurrentTimestamp()
//             );

//             auditRepo.save(log);

//             std::cout << "Account unfrozen.\n";
//             return;
//         }
//     }

//     std::cout << "Account not found.\n";
// }

// Helpers

void BankService::printAccounts(const std::vector<Account>& accs)
{
    for (size_t i = 0; i < accs.size(); i++)
    {
        std::cout << i + 1 << ". "
                  << accs[i].getOwnerName()
                  << " | Balance: "
                  << accs[i].getBalance()
                  << "\n";
    }
}
