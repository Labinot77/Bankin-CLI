#pragma once
#include <string>

class Account {
private:
    int id;
    int userId;
    std::string ownerName;
    double balance;
    bool isFrozen;

public:
    Account(int id, int userId, std::string ownerName, double balance, bool isFrozen);

    int getId() const;
    int getUserId() const;
    std::string getOwnerName() const;
    double getBalance() const;
    bool getIsFronze() const;

    void setFrozen(bool frozen);

    void deposit(double amount);
    int withdraw(double amount);
};