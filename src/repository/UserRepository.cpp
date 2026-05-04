#include "UserRepository.h"
#include <fstream>
#include <sstream>

void UserRepository::save(const User& user) {
    std::ofstream file("data/users.txt", std::ios::app);

    file << user.getId() << ","
         << user.getUsername() << ","
         << user.getPassword() << "\n";
}

std::vector<User> UserRepository::getAll() {
    std::vector<User> users;
    std::ifstream file("data/users.txt");

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);

        std::string idStr, username, password;

        getline(ss, idStr, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');

        users.emplace_back(stoi(idStr), username, password);
    }

    return users;
}

int UserRepository::generateId() {
    auto users = getAll();
    return users.empty() ? 1 : users.back().getId() + 1;
}

User* UserRepository::findByUsername(const std::string& username) {
    static User found(0, "", "");

    auto users = getAll();
    for (auto& user : users) {
        if (user.getUsername() == username) {
            found = user;
            return &found;
        }
    }

    return nullptr;
}