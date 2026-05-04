#include "AuditLog.h"

AuditLog::AuditLog(int id, std::string action, std::string timestamp) {
    this->id = id;
    this->action = action;
    this->timestamp = timestamp;
}

int AuditLog::getId() const {
    return id;
}

std::string AuditLog::getAction() const {
    return action;
}

std::string AuditLog::getTimestamp() const {
    return timestamp;
}

