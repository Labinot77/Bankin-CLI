#pragma once
#include "../repository/AuditLogRepository.h"
#include "../services/BankService.h"
#include "../services/AuthService.h"

class Menu {
private:
    // AuditLogRepository auditRepo;
    BankService bankService;
    AuthService authService;

public:
    void show();
};