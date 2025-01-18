#include "User.h"
#include "CryptoTradingPlatform.h"


int main() {
  CryptoTradingPlatform platform;

  thread priceUpdateThread(&CryptoTradingPlatform::updateCryptoPrices, &platform); // Start the price update thread

  while (true) { // Loop until the program is stopped
    cout << endl;
    cout << "Crypto Trading Platform Menu:" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Log In" << endl;
    cout << "3. Exit" << endl;

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
          cout << "1. Deposit Money" << endl;
          cout << "2. Withdraw Money" << endl;
          cout << "3. Buy Bitcoin" << endl;
          cout << "4. Sell Bitcoin" << endl;
          cout << "5. Buy Dogecoin" << endl;
          cout << "6. Sell Dogecoin" << endl;
          cout << "7. Check Transactions" << endl;
          cout << "8. Check Balance" << endl;
          cout << "9. Show crypto wallet" << endl;
          cout << "0. Logout" << endl;

          int option;
          cin >> option;

          if (cin.fail()) { // Clear the input buffer if the user enters a non-integer value
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << "Invalid choice. Please select a valid option." << endl;
              continue;
          }

          User *user = platform.authenticateUser(username, password);

          if (option == 1) { // Deposit money
            double amount;
            cout << "Enter the amount to deposit: $";
            cin >> amount;
            user->deposit(amount);
          } else if (option == 2) { // Withdraw money
            double amount;
            platform.saveUsersToFile();
            cout << "Enter the amount to withdraw: $";
            cin >> amount;
            user->withdraw(amount);
            platform.saveUsersToFile();
          } else if (option == 3) { // Buy bitcoin
            double amount;
            cout << "Enter the amount of Bitcoin to buy: ";
            cin >> amount;
            user->buyBitcoin(amount);
            platform.saveUsersToFile();
          } else if (option == 4) { // Sell bitcoin
            double amount;
            cout << "Enter the amount of Bitcoin to sell: ";
            cin >> amount;
            user->sellBitcoin(amount);
            platform.saveUsersToFile();
          } else if (option == 5) { // Buy dogecoin
            double amount;
            cout << "Enter the amount of Dogecoin to buy: ";
            cin >> amount;
            user->buyDogecoin(amount);
            platform.saveUsersToFile();
          } else if (option == 6) { // Sell dogecoin
            double amount;
            cout << "Enter the amount of Dogecoin to sell: ";
            cin >> amount;
            user->sellDogecoin(amount);
            platform.saveUsersToFile();
          } else if (option == 7) { // Check transactions
            user->checkTransactions();
          } else if (option == 8) { // Check balance
            user->checkBalance();
          } else if (option == 9) { // Show crypto wallet
            user->showCryptoWallet();
          } else if (option == 0) { // Logout
            cout << "Logging out..." << endl;
            platform.saveUsersToFile();
            break;
          } else { // Invalid option
            cout << "Invalid option. Please select a valid option." << endl;
          }
        cout << endl;
        }
        // some new functionality need be added over that
      } else { // User not found or password is incorrect
        cout << "Authentication failed. Invalid username or password." << endl;
      }
    } else if (choice == 3) { // Exit
      platform.exitProgram();
    } else {
      cout << "Invalid choice. Please select a valid option." << endl;
    }
  }
}