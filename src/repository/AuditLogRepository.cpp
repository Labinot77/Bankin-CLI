// #include "AuditLogRepository.h"
// #include <fstream>
// #include <sstream>

// void AuditLogRepository::save(const AuditLog& log) {
//     std::ofstream file("data/audit_logs.txt", std::ios::app);

//     file << log.getId() << ","
//          << log.getAction() << ","
//          << log.getTimestamp() << "\n";
// }

// std::vector<AuditLog> AuditLogRepository::getAll() {
//     std::vector<AuditLog> logs;
//     std::ifstream file("data/audit_logs.txt");

//     std::string line;
//     while (getline(file, line)) {
//         std::stringstream ss(line);

//         std::string idStr, action, timestamp;

//         getline(ss, idStr, ',');
//         getline(ss, action, ',');
//         getline(ss, timestamp, ',');

//         logs.emplace_back(
//             stoi(idStr),
//             action,
//             timestamp
//         );
//     }

//     return logs;
// }

// int AuditLogRepository::generateId() {
//     std::vector<AuditLog> logs = getAll();
//     return logs.empty() ? 1 : logs.back().getId() + 1;
// }