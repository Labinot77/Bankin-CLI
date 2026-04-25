#pragma once
#include <string>

class Account {
public:
    int id;
    std::string ownerName;
    double balance;

    Account(int id, std::string ownerName, double balance);
};