#include "User.h"

User::User(int id, std::string username, std::string password) {
    this->id = id;
    this->username = username;
    this->password = password;
}

int User::getId() const { return id; }
std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }