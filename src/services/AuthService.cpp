#include "AuthService.h"
#include <iostream>

std::optional<User> AuthService::login(
    const std::string& username,
    const std::string& password)
{
    auto user = repo.findByUsername(username);

    if (!user || user->getPassword() != password)
    {
        return std::nullopt;
    }

    return user;
}
User AuthService::registerUser(const std::string& username, const std::string& password)
{
    if (repo.findByUsername(username))
    {
        std::cout << "User already exists.\n";
        return User(-1, "", "");
    }

    User user(0, username, password);

    int newId = repo.save(user);

    std::cout << "User registered successfully.\n";

    return User(newId, username, password);
}