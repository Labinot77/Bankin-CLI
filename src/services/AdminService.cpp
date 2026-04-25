#include "AdminService.h"
#include <string>

bool AdminService::login(std::string password) {
    return password == "admin123"; // simple for now
}