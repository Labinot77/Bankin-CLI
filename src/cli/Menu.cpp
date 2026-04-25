#include "Menu.h"
#include "../services/BankService.h"
#include <iostream>
#include "../services/AdminService.h"

void Menu::show()
{
    BankService bankService;

    int choice;

    while (true)
    {
        std::cout << "\n--- BANK MENU ---\n";
        std::cout << "1. Open Account\n";
        std::cout << "2. Deposit\n";
        std::cout << "3. Withdraw\n";
        std::cout << "4. View Transactions\n";
        std::cout << "5. Transfer\n";
        std::cout << "6. View All Accounts\n";
        std::cout << "7. Admin Login\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            std::string name;
            double deposit;

            std::cout << "Enter name: ";
            std::cin >> name;

            std::cout << "Initial deposit: ";
            std::cin >> deposit;

            bankService.createAccount(name, deposit);
            break;
        }

        case 2:
        {
            int id;
            double amount;

            std::cout << "Enter account ID: ";
            std::cin >> id;

            std::cout << "Enter amount: ";
            std::cin >> amount;

            bankService.deposit(id, amount);
            break;
        }

        case 3:
        {
            int id;
            double amount;

            std::cout << "Enter account ID: ";
            std::cin >> id;

            std::cout << "Enter amount: ";
            std::cin >> amount;

            bankService.withdraw(id, amount);
            break;
        }

        case 4:
        {
            int id;
            std::cout << "Enter account ID: ";
            std::cin >> id;

            bankService.showTransactions(id);
            break;
        }

        case 5:
        {
            int fromId, toId;
            double amount;

            std::cout << "From account ID: ";
            std::cin >> fromId;

            std::cout << "To account ID: ";
            std::cin >> toId;

            std::cout << "Amount: ";
            std::cin >> amount;

            bankService.transfer(fromId, toId, amount);
            break;
        }

        case 6:
            bankService.showAllAccounts();
            break;
        case 7:{    
    AdminService adminService;
    std::string password;

    std::cout << "Enter admin password: ";
    std::cin >> password;

    if (!adminService.login(password)) {
        std::cout << "Wrong password.\n";
        break;
    }

    int adminChoice;

    while (true)
    {
        std::cout << "\n--- ADMIN MENU ---\n";
        std::cout << "1. Freeze Account\n";
        std::cout << "2. Unfreeze Account\n";
        std::cout << "0. Back\n";
        std::cout << "Choice: ";
        std::cin >> adminChoice;

        if (adminChoice == 1)
        {
            int id;
            std::cout << "Account ID: ";
            std::cin >> id;

            bankService.freezeAccount(id);
        }
        else if (adminChoice == 2)
        {
            int id;
            std::cout << "Account ID: ";
            std::cin >> id;

            bankService.unfreezeAccount(id);
        }
        else if (adminChoice == 0)
        {
            break; // exit admin menu
        }
        else
        {
            std::cout << "Invalid choice.\n";
        }
    }
    break;
}
        case 0:
            return; // cleaner than break (exits function directly)

        default:
            std::cout << "Invalid choice.\n";
        }
    }
}