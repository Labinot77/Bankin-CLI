#pragma once
#include <string>

class Transaction {
public:
    int id;
    int accountId;
    std::string type; // "DEPOSIT", "WITHDRAW", "TRANSFER_IN", "TRANSFER_OUT"
    double amount;

    Transaction(int id, int accountId, std::string type, double amount);
};