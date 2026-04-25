#pragma once
#include <vector>
#include "../models/Account.h"

class AccountRepository {
public:
    std::vector<Account> getAll();
    void save(const Account& account);
    int generateId();

    Account getById(int id);
    void updateAll(const std::vector<Account>& accounts);
};