#include "Menu.h"
#include "../services/BankService.h"
#include "../services/AuthService.h"
#include <iostream>

void Menu::show()
{

    User* currentUser = nullptr;

    int choice;

    while (true)
    {
        // 🔐 NOT LOGGED IN MENU
        if (!currentUser)
        {
            std::cout << "\n--- MAIN MENU ---\n";
            std::cout << "1. Register\n";
            std::cout << "2. Login\n";
            std::cout << "0. Exit\n";
            std::cout << "Choice: ";
            std::cin >> choice;

            if (choice == 1)
            {
                std::string username, password;

                std::cout << "Username: ";
                std::cin >> username;

                std::cout << "Password: ";
                std::cin >> password;

                authService.registerUser(username, password);
            }
            else if (choice == 2)
            {
                std::string username, password;

                std::cout << "Username: ";
                std::cin >> username;

                std::cout << "Password: ";
                std::cin >> password;

                currentUser = authService.login(username, password);

                if (!currentUser)
                {
                    std::cout << "Invalid credentials.\n";
                }
                else
                {
                    std::cout << "Welcome, " << currentUser->getUsername() << "!\n";
                }
            }
            else if (choice == 0)
            {
                return;
            }
            else
            {
                std::cout << "Invalid choice.\n";
            }
        }

        // 👤 LOGGED-IN USER MENU
        else
        {
            std::cout << "\n--- USER MENU ---\n";
            std::cout << "1. Create Account\n";
            std::cout << "2. Deposit\n";
            std::cout << "3. Withdraw\n";
            std::cout << "4. Transfer\n";
            std::cout << "5. View My Accounts\n";
            std::cout << "6. View Transactions\n";
            std::cout << "7. Logout\n";
            std::cout << "Choice: ";
            std::cin >> choice;

            switch (choice)
            {
            case 1:
            {
                std::string name;
                double deposit;

                std::cout << "Account name: ";
                std::cin >> name;

                std::cout << "Initial deposit: ";
                std::cin >> deposit;

                bankService.createAccount(currentUser->getId(), name, deposit);
                break;
            }

case 2:
{
    auto accounts = bankService.getAccountsByUser(currentUser->getId());

    if (accounts.empty()) {
        std::cout << "No accounts found.\n";
        break;
    }

    std::cout << "\n--- Your Accounts ---\n";

    for (size_t i = 0; i < accounts.size(); i++) {
        std::cout << i + 1 << ". "
                  << accounts[i].getOwnerName()
                  << " | Balance: " << accounts[i].getBalance()
                  << "\n";
    }

    int choice;
    std::cout << "Choose account: ";
    std::cin >> choice;

    if (choice < 1 || choice > accounts.size()) {
        std::cout << "Invalid choice.\n";
        break;
    }

    int selectedId = accounts[choice - 1].getId();

    double amount;
    std::cout << "Amount: ";
    std::cin >> amount;

    bankService.deposit(selectedId, amount);

    break;
}

            case 3:
            {
                int id;
                double amount;

                std::cout << "Account ID: ";
                std::cin >> id;

                std::cout << "Amount: ";
                std::cin >> amount;

                bankService.withdraw(id, amount);
                break;
            }

            case 4:
            {
                int fromId, toId;
                double amount;

                std::cout << "From Account ID: ";
                std::cin >> fromId;

                std::cout << "To Account ID: ";
                std::cin >> toId;

                std::cout << "Amount: ";
                std::cin >> amount;

                bankService.transfer(fromId, toId, amount);
                break;
            }

            case 5:
                // bankService.showAccountsByUser(currentUser->getId());
                break;

            case 6:
            {
                int id;
                std::cout << "Account ID: ";
                std::cin >> id;

                bankService.showTransactions(id);
                break;
            }

            case 7:
                currentUser = nullptr;
                std::cout << "Logged out.\n";
                break;

            default:
                std::cout << "Invalid choice.\n";
            }
        }
    }
}