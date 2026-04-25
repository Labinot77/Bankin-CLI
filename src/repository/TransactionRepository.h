#pragma once
#include <vector>
#include "../models/Transaction.h"

class TransactionRepository {
public:
    void save(const Transaction& tx);
    
    int generateId();

    std::vector<Transaction> getAll();
    std::vector<Transaction> getByAccountId(int accountId);
};