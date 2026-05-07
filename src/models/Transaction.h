#pragma once
#include <string>

class Transaction {
private:
    int id;
    int accountId;
    std::string type;
    double amount;
    std::string timestamp;

public:
    Transaction(int id, int accountId, std::string type, double amount, std::string timestamp);

    int getId() const;
    int getAccountId() const;
    std::string getType() const;
    double getAmount() const;
    std::string getTime() const;
};