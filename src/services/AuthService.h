#pragma once
#include "../repository/UserRepository.h"

class AuthService {
private:
    UserRepository repo;

public:
    User* login(const std::string& username, const std::string& password);
    void registerUser(const std::string& username, const std::string& password);
};