#include "Transaction.h"

Transaction::Transaction(int id, int accountId, std::string type, double amount) {
        this->id = id;
        this->accountId = accountId;
        this->type = type;
        this->amount = amount;
}
