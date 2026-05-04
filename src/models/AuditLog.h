#pragma once
#include <string>

class AuditLog {
    private:
        int id;
        std::string action;
        std::string timestamp;

    public:
        AuditLog(int id, std::string action, std::string timestamp);

        int getId() const;
        std::string getAction() const;
        std::string getTimestamp() const;
};