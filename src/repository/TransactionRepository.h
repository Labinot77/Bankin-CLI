#pragma once
#include <vector>
#include "../models/Transaction.h"

class TransactionRepository {
public:
    void save(const Transaction& tx);
    std::vector<Transaction> getByAccountId(int accountId);
    int generateId();
};