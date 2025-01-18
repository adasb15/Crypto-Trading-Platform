#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <thread>
#include <vector>

using namespace std;

class User {
private:
  double bitcoinPrice;
  double dogecoinPrice;

public:
  string username;
  string password;
  double balance;
  double bitcoinHolding;
  double dogecoinHolding;
  vector<string> transactions;

  User() // Default constructor
      : username(""), password(""), balance(0.0), bitcoinHolding(0.0),
        dogecoinHolding(0.0) {}

  User(string u, string p, double b) // Constructor with parameters
      : username(u), password(p), balance(b), bitcoinHolding(0.0),
        dogecoinHolding(0.0) {}
  
  void deposit(double amount) { // Method to deposit money
    balance += amount;
    transactions.push_back("Deposited $" + to_string(amount));
  }
  void withdraw(double amount) { // Method to withdraw money
    if (amount <= balance) {
      balance -= amount;
      transactions.push_back("Withdrew $" + to_string(amount));
    } else {
      cout << "Insufficient funds." << endl;
    }
  }
  void loadCryptoPrices() { // Method to load crypto prices from file
    ifstream priceFile("crypto_prices.txt");
    if (priceFile.is_open()) {
      priceFile >> bitcoinPrice;
      priceFile >> dogecoinPrice;
      priceFile.close();
    }
  }

  void buyBitcoin(double amount) { // Method to buy bitcoin
    loadCryptoPrices();
    if (amount * bitcoinPrice <= balance) {
      bitcoinHolding += amount;
      balance -= amount * bitcoinPrice;
      transactions.push_back("Bought " + to_string(amount) + " BTC");
    } else {
      cout << "Insufficient balance to buy Bitcoin." << endl;
    }
  }
  void sellBitcoin(double amount) { // Method to sell bitcoin
    loadCryptoPrices();
    if (amount <= bitcoinHolding) {
      bitcoinHolding -= amount;
      balance += amount * bitcoinPrice;
      transactions.push_back("Sold " + to_string(amount) + " BTC");
    } else {
      cout << "Insufficient Bitcoin holdings to sell." << endl;
    }
  }

  void buyDogecoin(double amount) { // Method to buy dogecoin
    loadCryptoPrices();
    if (amount * dogecoinPrice <= balance) {
      dogecoinHolding += amount;
      balance -= amount * dogecoinPrice;
      transactions.push_back("Bought " + to_string(amount) + " DOGE");
    } else {
      cout << "Insufficient balance to buy Bitcoin." << endl;
    }
  }
  void sellDogecoin(double amount) { // Method to sell dogecoin
    loadCryptoPrices();
    if (amount <= dogecoinHolding) {
      dogecoinHolding -= amount;
      balance += amount * dogecoinPrice;
      transactions.push_back("Sold " + to_string(amount) + " DOGE");
    } else {
      cout << "Insufficient Bitcoin holdings to sell." << endl;
    }
  }

  void checkTransactions() { // Method to check user's transactions
    cout << "Transaction History for " << username << ":" << endl;
    for (const string &transaction : transactions) {
      cout << transaction << endl;
    }
  }

  void checkBalance() { // Method to check user's balance
    cout << "Account balance for " << username << ": $" << balance << endl;
  }
};

class CryptoTradingPlatform {
private:
  map<string, User> users;
  double bitcoinPrice; 
  double dogecoinPrice;

public:
  CryptoTradingPlatform() {
    loadUsersFromFile();
    loadPriceFromFile();
  }

  void loadPriceFromFile() { // Method to load crypto prices from file
    ifstream priceFile("crypto_prices.txt");
    if (priceFile.is_open()) {
      priceFile >> bitcoinPrice;
      priceFile >> dogecoinPrice;
      priceFile.close();
    } else {
      // If the file doesn't exist
      bitcoinPrice = 45000.0;
      dogecoinPrice = 0.25;
    }
  }

  void loadUsersFromFile() { // Method to load users from file
    ifstream file("users.txt");
    if (file.is_open()) {
      string username, password;
      double balance, bitcoinHolding, dogecoinHolding;
      while (file >> username >> password >> balance >> bitcoinHolding >>
             dogecoinHolding) {
        users[username] = User(username, password, balance);
        users[username].bitcoinHolding = bitcoinHolding;
        users[username].dogecoinHolding = dogecoinHolding;
      }
      file.close();
    }
  }

  void saveUsersToFile() { // Method to save users to file
    ofstream file("users.txt");
    if (file.is_open()) {
      for (const auto &entry : users) {
        file << entry.second.username << " " << entry.second.password << " "
             << entry.second.balance << " " << entry.second.bitcoinHolding
             << " " << entry.second.dogecoinHolding << endl;
      }
      file.close();
    }
  }

  void createUser(string username, string password, double initialBalance) { // Method to create a new user
    if (users.find(username) == users.end()) {
      users[username] = User(username, password, initialBalance);
      saveUsersToFile();
      cout << "User " << username << " created successfully." << endl;
    } else {
      cout << "User with this username already exists. Please choose a "
              "different username."
           << endl;
    }
  }

  User *authenticateUser(string username, string password) { // Method to authenticate a user
    if (users.find(username) != users.end() &&
        users[username].password == password) {
      return &users[username];
    }
    return nullptr;
  }

  void updateCryptoPrices() { // Method to update crypto prices
    default_random_engine generator;
    uniform_real_distribution<double> distribution(-0.02, 0.02);

    // Need to think about how to display the price in a nice format and how often to update the price
    while (true) { // Loop until the program is stopped
      bitcoinPrice += bitcoinPrice * distribution(generator);
      dogecoinPrice += dogecoinPrice * distribution(generator);
      cout << "Bitcoin price: $" << bitcoinPrice << endl; 
      cout << "Dogecoin price: $" << dogecoinPrice << endl;
      ofstream priceFile("crypto_prices.txt"); // Write the new prices to file
      if (priceFile.is_open()) {
        priceFile << bitcoinPrice << " " << dogecoinPrice << endl;
        priceFile.close();
      }
      this_thread::sleep_for(chrono::seconds(60));
    }
  }
};

int main() {
  CryptoTradingPlatform platform;

  thread priceUpdateThread(&CryptoTradingPlatform::updateCryptoPrices, &platform); // Start the price update thread

  while (true) { // Loop until the program is stopped
    cout << "Crypto Trading Platform Menu:" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Log In" << endl;
    cout << "3. Exit" << endl;

    int choice;
    cin >> choice;

    if (choice == 1) { // Create a new user
      string username, password;
      double initialBalance;
      cout << "Enter a username: ";
      cin >> username;
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
      // maybe some changes, if user is not found or password is incorrect
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
          cout << "9. Logout" << endl;

          int option;
          cin >> option;

          User *user = platform.authenticateUser(username, password);

          if (option == 1) { // Deposit money
            double amount;
            cout << "Enter the amount to deposit: $";
            cin >> amount;
            user->deposit(amount);
          } else if (option == 2) { // Withdraw money
            double amount;
            cout << "Enter the amount to withdraw: $";
            cin >> amount;
            user->withdraw(amount);
          } else if (option == 3) { // Buy bitcoin
            double amount;
            cout << "Enter the amount of Bitcoin to buy: ";
            cin >> amount;
            user->buyBitcoin(amount);
          } else if (option == 4) { // Sell bitcoin
            double amount;
            cout << "Enter the amount of Bitcoin to sell: ";
            cin >> amount;
            user->sellBitcoin(amount);
          } else if (option == 5) { // Buy dogecoin
            double amount;
            cout << "Enter the amount of Dogecoin to buy: ";
            cin >> amount;
            user->buyDogecoin(amount);
          } else if (option == 6) { // Sell dogecoin
            double amount;
            cout << "Enter the amount of Dogecoin to sell: ";
            cin >> amount;
            user->sellDogecoin(amount);
          } else if (option == 7) { // Check transactions
            user->checkTransactions();
          } else if (option == 8) { // Check balance
            user->checkBalance();
          } else if (option == 9) { // Logout
            cout << "Logging out..." << endl;
            platform.saveUsersToFile();
            break;
          } else { // Invalid option
            cout << "Invalid option. Please select a valid option." << endl;
          }
        }
        // some new functionality need be added over that
      } else { // User not found or password is incorrect
        cout << "Authentication failed. Invalid username or password." << endl;
      }
    } else if (choice == 3) { // Exit
      cout << "Exiting. Have a great day!" << endl;
      priceUpdateThread.join(); // Wait for price update thread to finish
      return 0;
    } else {
      cout << "Invalid choice. Please select a valid option." << endl;
    }
  }
  priceUpdateThread.join(); // Wait for price update thread to finish
  return 0;
}