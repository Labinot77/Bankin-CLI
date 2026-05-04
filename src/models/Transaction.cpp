#include "Transaction.h"

Transaction::Transaction(int id, int accountId, std::string type, double amount, std::string timestamp) {
    this->id = id;
    this->accountId = accountId;
    this->type = type;
    this->amount = amount;
    this->timestamp = timestamp;
}

int Transaction::getId() const {
    return id;
}

int Transaction::getAccountId() const {
    return accountId;
}

std::string Transaction::getType() const {
    return type;
}

double Transaction::getAmount() const {
    return amount;
}

std::string Transaction::getTime() const {
    return timestamp;
}