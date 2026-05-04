#pragma once
#include "../models/User.h"
#include <vector>

class UserRepository {
public:
    void save(const User& user);
    std::vector<User> getAll();
    int generateId();

    User* findByUsername(const std::string& username);
};