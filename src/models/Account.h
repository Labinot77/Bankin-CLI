#pragma once
#include <string>

class Account {
public:
    int id;
    std::string ownerName;
    double balance;
    bool isFrozen;

    Account(int id, std::string ownerName, double balance);
};