#pragma once
#include <vector>
#include "../models/Account.h"

class AccountRepository {
public:
    std::vector<Account> getAll();
    std::vector<Account> getAccountsForUser(int userId);
    void save(const Account& account);

    Account getById(int id);
    void update(const Account& acc);
};