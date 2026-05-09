#pragma once
#include <vector>
#include "../models/Account.h"
#include <optional>

class AccountRepository {
public:
    std::vector<Account> getAll();
    std::vector<Account> getAccountsForUser(int userId);
    void save(const Account& account);

    std::optional<Account> getById(int id);
    void update(const Account& acc);
};