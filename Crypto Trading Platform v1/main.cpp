#include "User.h"
#include "CryptoTradingPlatform.h"


int main() {
    CryptoTradingPlatform platform;

    while (true) { // Loop until the program is stopped
        cout << endl;
        cout << "Crypto Trading Platform Menu:" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Log In" << endl;
        cout << "3. Administrator Menu" << endl;
        cout << "0. Exit" << endl;

        int choice;
        cin >> choice;

        if (cin.fail()) { // Clear the input buffer if the user enters a non-integer value
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (choice == 1) { // Create a new user
            string username, password;
            double initialBalance;
            cout << "Enter a username: ";
            cin >> username;
            if (platform.checkExistsUser(username)) {
                continue;
            }
            cout << "Enter a password: ";
            cin >> password;
            cout << "Enter initial balance: $";
            cin >> initialBalance;
            if (cin.fail()) { // Clear the input buffer if the user enters a non-integer value
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Initial balance must be in the form of numbers";
                continue;
            }
            platform.createUser(username, password, initialBalance);
        } else if (choice == 2) { // Log in to an existing user
            string username, password;
            cout << "Enter your username: ";
            cin >> username;
            cout << "Enter your password: ";
            cin >> password;
            User *user = platform.authenticateUser(username, password);
            if (user) {
                while (true) { // Loop until the user logs out
                    cout << "Logged in as " << username << endl;
                    cout << endl;
                    cout << "Trading Options:" << endl;
                    cout << "1. Show crpyto prices." << endl;
                    cout << "2. Deposit Money" << endl;
                    cout << "3. Withdraw Money" << endl;
                    cout << "4. Buy Bitcoin" << endl;
                    cout << "5. Sell Bitcoin" << endl;
                    cout << "6. Buy Dogecoin" << endl;
                    cout << "7. Sell Dogecoin" << endl;
                    cout << "8. Buy Ethereum" << endl;
                    cout << "9. Sell Ethereum" << endl;
                    cout << "10. Buy Litecoin" << endl;
                    cout << "11. Sell Litecoin" << endl;
                    cout << "12. Buy Ripple" << endl;
                    cout << "13. Sell Ripple" << endl;
                    cout << "14. Check Transactions" << endl;
                    cout << "15. Change password" << endl;
                    cout << "16. Delete Account" << endl;
                    cout << "17. Check statistics" << endl;
                    cout << "0. Log out" << endl;

                    int option;
                    cin >> option;

                    if (cin.fail()) { // Clear the input buffer if the user enters a non-integer value
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid choice. Please select a valid option." << endl;
                        continue;
                    }

                    User *user = platform.authenticateUser(username, password);

                    if (option == 1) {
                        user->showCryptoPrices();
                    } else if (option == 2) { // Deposit money
                        double amount;
                        cout << "Enter the amount to deposit: $";
                        cin >> amount;
                        user->deposit(amount);
                    } else if (option == 3) { // Withdraw money
                        double amount;
                        platform.saveUsersToFile();
                        cout << "Enter the amount to withdraw: $";
                        cin >> amount;
                        user->withdraw(amount);
                        platform.saveUsersToFile();
                    } else if (option == 4) { // Buy bitcoin
                        double amount;
                        cout << "Enter the amount of Bitcoin to buy: ";
                        cin >> amount;
                        user->buyBitcoin(amount);
                        platform.saveUsersToFile();
                    } else if (option == 5) { // Sell bitcoin
                        double amount;
                        cout << "Enter the amount of Bitcoin to sell: ";
                        cin >> amount;
                        user->sellBitcoin(amount);
                        platform.saveUsersToFile();
                    } else if (option == 6) { // Buy dogecoin
                        double amount;
                        cout << "Enter the amount of Dogecoin to buy: ";
                        cin >> amount;
                        user->buyDogecoin(amount);
                        platform.saveUsersToFile();
                    } else if (option == 7) { // Sell dogecoin
                        double amount;
                        cout << "Enter the amount of Dogecoin to sell: ";
                        cin >> amount;
                        user->sellDogecoin(amount);
                        platform.saveUsersToFile();
                    } else if (option == 8) { // Buy ethereum
                        double amount;
                        cout << "Enter the amount of Ethereum to buy: ";
                        cin >> amount;
                        user->buyEthereum(amount);
                        platform.saveUsersToFile();
                    } else if (option == 9) { // Sell ethereum
                        double amount;
                        cout << "Enter the amount of Ethereum to sell: ";
                        cin >> amount;
                        user->sellEthereum(amount);
                        platform.saveUsersToFile();
                    } else if (option == 10) { // Buy litecoin
                        double amount;
                        cout << "Enter the amount of Litecoin to buy: ";
                        cin >> amount;
                        user->buyLitecoin(amount);
                        platform.saveUsersToFile();
                    } else if (option == 11) { // Sell litecoin
                        double amount;
                        cout << "Enter the amount of Litecoin to sell: ";
                        cin >> amount;
                        user->sellLitecoin(amount);
                        platform.saveUsersToFile();
                    } else if (option == 12) { // Buy ripple
                        double amount;
                        cout << "Enter the amount of Ripple to buy: ";
                        cin >> amount;
                        user->buyRipple(amount);
                        platform.saveUsersToFile();
                    } else if (option == 13) { // Sell ripple
                        double amount;
                        cout << "Enter the amount of Ripple to sell: ";
                        cin >> amount;
                        user->sellRipple(amount);
                        platform.saveUsersToFile();
                    } else if (option == 14) { // Check transactions
                        user->checkTransactions();
                    } else if (option == 15) { // Change password
                        user->changePassword();
                        platform.saveUsersToFile();
                    } else if (option == 16) {
                        cout << "Are you sure you want to delete your account? (y/n): ";
                        char confirm;
                        cin >> confirm;
                        if (confirm == 'y' || confirm == 'Y') {
                            platform.deleteAccount(username);
                            cout << "Account deleted successfully." << endl;
                            platform.saveUsersToFile();
                            break;
                        } else {
                            cout << "Account deletion canceled." << endl;
                        }
                    } else if (option == 17) {
                        user->displayAccountInfo();
                    } else if (option == 0) { // Logout
                        cout << "Logging out..." << endl;
                        platform.saveUsersToFile();
                        break;
                    } else { // Invalid option
                        cout << "Invalid option. Please select a valid option." << endl;
                    }
                    cout << endl;
                }
            } else { // User not found or password is incorrect
                cout << "Authentication failed. Invalid username or password." << endl;
            }
        } else if (choice == 3) { // Administrator Menu
            cout << "Log in as administrator:" << endl;
            cout << "Username: ";
            string adminUsername;
            cin >> adminUsername;
            cout << "Password: ";
            string adminPassword;
            cin >> adminPassword;
            cout << endl;
            if (adminUsername == "admin" && adminPassword == "1234") {
                cout << "Welcome, administrator!" << endl;

                while (true) {
                    cout << endl;
                    cout << "Administrator Menu:" << endl;
                    cout << "1. View User List" << endl;
                    cout << "2. View Crypto Prices" << endl;
                    cout << "3. Remove user" << endl;
                    cout << "4. Show history of transaction" << endl;
                    cout << "5. Chaange prices of Crypto" << endl;
                    cout << "0. Exit Administrator Menu" << endl;

                    int adminChoice;
                    cin >> adminChoice;

                    if (cin.fail()) { // Clear the input buffer if the user enters a non-integer value
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid choice. Please select a valid option." << endl;
                        continue;
                    }

                    if (adminChoice == 1) { // View User List
                        // Display the list of users
                        platform.viewUserList();
                    } else if (adminChoice == 2) { // View Crypto Prices
                        // Display current crypto prices or any other relevant information
                        platform.viewCryptoPrices();
                    } else if (adminChoice == 3) {
                        cout << "Enter the username to delete: " << endl;
                        string username_remove;
                        cin >> username_remove;
                        cout << "Confirm it with your administrator password: " << endl;
                        string autorization_remove;
                        cin >> autorization_remove;
                        if (autorization_remove == adminPassword) {
                            platform.removeUser(username_remove);
                        } else {
                            cout << "Wrong." << endl;
                            continue;
                        }
                    } else if (adminChoice == 4) {
                        platform.checkAllHistory();
                    } else if (adminChoice == 5) {
                        platform.changeCryptoPrices();
                    } else if (adminChoice == 0) { // Exit Administrator Menu
                        cout << "Exiting Administrator Menu." << endl;
                        break;
                    } else {
                        cout << "Invalid choice. Please select a valid option." << endl;
                    }
                }
            } else {
                cout << "Invalid username or password. Please try again." << endl;
            }

        } else if (choice == 0) { // Exit
            platform.exitProgram();
            exit(0);
        } else {
            cout << "Invalid choice. Please select a valid option." << endl;
        }
    }
}
