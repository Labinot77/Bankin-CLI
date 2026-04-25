#pragma once
#include <string>

class Transaction {
private:
    int id;
    int accountId;
    std::string type;
    double amount;

public:
    Transaction(int id, int accountId, std::string type, double amount);

    // getters
    int getId() const;
    int getAccountId() const;
    std::string getType() const;
    double getAmount() const;
};