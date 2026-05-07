#pragma once
#include "../repository/UserRepository.h"

class AuthService {
private:
    UserRepository repo;

public:
    std::optional<User> login(
    const std::string& username,
    const std::string& password
);
    User registerUser(const std::string& username, const std::string& password);
};