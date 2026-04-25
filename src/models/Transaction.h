#pragma once
#include <string>

class Transaction {
public:
    int id;
    int accountId;
    std::string type; // "DEPOSIT", "WITHDRAW"
    double amount;

    Transaction(int id, int accountId, std::string type, double amount);
};