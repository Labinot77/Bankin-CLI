#pragma once
#include <optional>
#include <string>
#include "../models/User.h"

class UserRepository {
public:
    void save(const User& user);

    std::optional<User> findByUsername(const std::string& username);

    std::optional<User> login(const std::string& username, const std::string& password);
};