#include "Account.h"

Account::Account(int id, int userId, std::string ownerName, double balance, bool isFrozen)
{
    this->id = id;
    this->userId = userId;
    this->ownerName = ownerName;
    this->balance = balance;
    this->isFrozen = isFrozen;
}

int Account::getId() const
{
    return id;
}

int Account::getUserId() const {
    return userId;
}

std::string Account::getOwnerName() const
{
    return ownerName;
}

double Account::getBalance() const
{
    return balance;
}

bool Account::getIsFronze() const
{
    return isFrozen;
}

void Account::setFrozen(bool frozen) {
    isFrozen = frozen;
}

// Functions

void Account::deposit(double amount) {
    if (isFrozen) return; 

    if (amount > 0) {
        balance += amount;
    }
}

int Account::withdraw(double amount) {
    if (isFrozen) return false;
    if (amount <= 0) return false;
    if (balance < amount) return false;

    balance -= amount;

    return true;
}