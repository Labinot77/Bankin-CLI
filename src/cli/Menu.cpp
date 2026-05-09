#include "Menu.h"
#include "../services/BankService.h"
#include "../services/AuthService.h"
#include <iostream>
#include <optional>

void Menu::show()
{

    std::optional<User> currentUser = std::nullopt;

    int choice;

    while (true)
    {
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

                User user = authService.registerUser(username, password);

                if (user.getId() != -1)
                {
                    std::cout << "Welcome, " << user.getUsername() << "!\n";
                }
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
                int selectedId = selectUserAccount(currentUser->getId());

                if (selectedId == -1)
                    break;

                double amount = askAmount();

                bankService.deposit(selectedId, amount);

                break;
            }

            case 3:
            {
                int selectedId = selectUserAccount(currentUser->getId());

                if (selectedId == -1)
                    break;

                double amount = askAmount();

                bankService.withdraw(selectedId, amount);

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
                bankService.showUserAccounts(currentUser->getId());
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
                currentUser = std::nullopt;
                std::cout << "Logged out.\n";
                break;

            default:
                std::cout << "Invalid choice.\n";
            }
        }
    }
}

int Menu::selectUserAccount(int userId)
{
    auto accs = bankService.getAccountsByUser(userId);

    if (accs.empty())
    {
        std::cout << "No accounts for this user";
        return -1;
    }

    bankService.printAccounts(accs);

    int choice;

    std::cout << "Choose account: ";
    std::cin >> choice;

    if (choice < 1 || choice > accs.size())
    {
        std::cout << "Invalid choice.\n";
        return -1;
    }

    return accs[choice - 1].getId();
}

double Menu::askAmount()
{
    double amount;

    std::cout << "Amount: ";
    std::cin >> amount;

    return amount;
}