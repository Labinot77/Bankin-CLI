#include "AuthService.h"
#include <iostream>

User* AuthService::login(const std::string& username, const std::string& password) {
    User* user = repo.findByUsername(username);

    if (!user || user->getPassword() != password) {
        return nullptr;
    }

    return user;
}

void AuthService::registerUser(const std::string& username, const std::string& password) {
    if (repo.findByUsername(username)) {
        std::cout << "User already exists.\n";
        return;
    }

    int id = repo.generateId();
    User user(id, username, password);

    repo.save(user);

    std::cout << "User registered successfully.\n";
}