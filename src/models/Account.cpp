#include "Account.h"

Account::Account(int id, std::string ownerName, double balance) {
    this->id = id;
    this->ownerName = ownerName;
    this->balance = balance;
    this->isFrozen = false;
}   