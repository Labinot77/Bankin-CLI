#pragma once
#include "../models/User.h"
#include <vector>
#include <optional>

class UserRepository {
public:
    int save(const User& user);
    std::vector<User> getAll();

    std::optional<User> findByUsername(const std::string& username);
};