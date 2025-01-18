#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <random>
#include <thread>
#include <vector>
#include <atomic>

using namespace std;

class CryptoTradingPlatform {
private:
  map<string, User> users;
  double bitcoinPrice; 
  double dogecoinPrice;
  double ethereumPrice;
  double litecoinPrice;
  double ripplePrice;
  atomic<bool> stopPriceUpdate;

public: // Constructor
  CryptoTradingPlatform() : stopPriceUpdate(false) {
    loadUsersFromFile();
    loadPriceFromFile();
  }

  void loadPriceFromFile() { // Method to load crypto prices from file
    ifstream priceFile("crypto_prices.txt");
    if (priceFile.is_open()) {
      priceFile >> bitcoinPrice;
      priceFile >> dogecoinPrice;
      priceFile >> ethereumPrice;
      priceFile >> litecoinPrice;
      priceFile >> ripplePrice;
      priceFile.close();
    } else {
      // If the file doesn't exist
      bitcoinPrice = 34000.0;
      dogecoinPrice = 0.67;
      ethereumPrice = 2100.0;
      litecoinPrice = 60.0;
      ripplePrice = 0.5;
    }
  }

  void loadUsersFromFile() { // Method to load users from file
    ifstream file("users.txt");
    if (file.is_open()) {
      string username, password, transaction;
      double balance, bitcoinHolding, dogecoinHolding, ethereumHolding, litecoinHolding, rippleHolding;
      while (file >> username >> password >> balance >> bitcoinHolding >>
             dogecoinHolding >> ethereumHolding >> litecoinHolding >> rippleHolding) {
        users[username] = User(username, password, balance);
        users[username].bitcoinHolding = bitcoinHolding;
        users[username].dogecoinHolding = dogecoinHolding;
        users[username].ethereumHolding = ethereumHolding;
        users[username].litecoinHolding = litecoinHolding;
        users[username].rippleHolding = rippleHolding;
          

        getline(file, transaction); // Read the rest of the line as transaction history
        stringstream ss(transaction);
        string transactionItem, combinedTransaction; 
        int transactionCount = 0;

        // Read and group transactions in sets of 3, then add a newline
        while (ss >> transactionItem) {
          combinedTransaction += transactionItem + " ";
          transactionCount++;
          if (transactionCount == 3) {
            // Add the combined transaction to the user's transactions
            users[username].transactions.push_back(combinedTransaction);
            combinedTransaction = "";
            transactionCount = 0;
          }
        }
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
             << " " << entry.second.dogecoinHolding << " " << entry.second.ethereumHolding << " " << entry.second.litecoinHolding << " " << entry.second.rippleHolding << endl;
        for (const string &transaction : entry.second.transactions) {
          file << transaction << " ";
        }
        file << endl;
      }
      file.close();
    }
  }
  
  void savePriceToFile() { // Method to save crypto prices to file
    ofstream priceFile("crypto_prices.txt");
    if (priceFile.is_open()) {
      priceFile << bitcoinPrice << " " << dogecoinPrice << " " << ethereumPrice << " " << litecoinPrice << " " << ripplePrice << endl;
      priceFile.close();
    }
  }

  void createUser(string username, string password, double initialBalance) { // Method to create a new user
    users[username] = User(username, password, initialBalance);
    saveUsersToFile();
    cout << "User " << username << " created successfully." << endl;
  }


  bool checkExistsUser(string username) { // Method to check if user exists
    if (users.find(username) != users.end()) {
      cout << "User " << username << " exists." << endl;
      cout << "Try again." << endl;
      return 1;
    }
    return 0;
  }  

  User *authenticateUser(string username, string password) { // Method to authenticate a user
    if (users.find(username) != users.end() &&
        users[username].password == password) {
      return &users[username];
    }
    return nullptr;
  }

  void updateCryptoPrices() { // Method to change prices of crypto ?? maybe same different way
    default_random_engine generator;
    uniform_real_distribution<double> distribution(-0.02, 0.02);  

    while (!stopPriceUpdate) {  // Loop until stopPriceUpdate is set to true
      bitcoinPrice += bitcoinPrice * distribution(generator);
      dogecoinPrice += dogecoinPrice * distribution(generator);
      ethereumPrice += ethereumPrice * distribution(generator);
      litecoinPrice += litecoinPrice * distribution(generator);
      ripplePrice += ripplePrice * distribution(generator);
        
      cout << "Bitcoin price: $" << bitcoinPrice << endl;
      cout << "Dogecoin price: $" << dogecoinPrice << endl;
      cout << "Ethereum price: $" << ethereumPrice << endl;
      cout << "Litecoin price: $" << litecoinPrice << endl;
      cout << "Ripple price: $" << ripplePrice << endl;
      savePriceToFile();
      this_thread::sleep_for(chrono::seconds(30)); // Sleep update prices for 30 seconds
    }
  }

  void deleteAccount(string username) { // Method to delete account
    auto it = users.find(username);
        if (it != users.end()) {
            users.erase(it);
            cout << "User " << username << " has been removed." << endl;
            saveUsersToFile(); 
        } else {
            cout << "User " << username << " not found." << endl;
        }
  }

 // admin function
  void viewUserList() { // Method to view user list
    cout << "User List:" << endl;
    for (const auto &entry : users) {
      cout << "Username: " << entry.second.username << ", Balance: $" << entry.second.balance;
      cout << ", Bitcoin: " << entry.second.bitcoinHolding << " BTC";
      cout << ", Dogecoin: " << entry.second.dogecoinHolding << " DOGE";
      cout << ", Ethereum: " << entry.second.ethereumHolding << " ETH";
      cout << ", Litcoin: " << entry.second.litecoinHolding << " LTC";
      cout << ", Ripple: " << entry.second.rippleHolding << " XRP";
    }
  }

  void viewCryptoPrices() { // Method to view crypto prices
    cout << "Current Crypto Prices:" << endl;
    cout << "Bitcoin Price: $" << bitcoinPrice << endl;
    cout << "Dogecoin Price: $" << dogecoinPrice << endl;
    cout << "Ethereum Price: $" << ethereumPrice << endl;
    cout << "Litecoin Price: $" << litecoinPrice << endl;
    cout << "Ripple Price: $" << ripplePrice << endl;
  }

  void removeUser(const string& username) { // Method to remove a user
      auto it = users.find(username);
      if (it != users.end()) {
          users.erase(it);
          cout << "User " << username << " has been removed." << endl;
          saveUsersToFile(); 
      } else {
          cout << "User " << username << " not found." << endl;
      }
  }

  void checkAllHistory() {  // Method to check all transactions
    cout << "History for all users:" << endl;
    for (const auto &entry : users) {
      cout << "User: " << entry.second.username << endl;
      cout << "Transactions:" << endl;
      for (const string &transaction : entry.second.transactions) {
        cout << transaction << endl;
      }
    }
  }

  void changeCryptoPrices() { // Method to change crypto prices
    while (true) {
      cout << "Which crypto would you like to change the price of? (BTC, DOGE, ETH, LTC, XRP)" << endl;
      string crypto;
      cin >> crypto;
      cout << "Give the new prices." << endl;
      double newPrice;
      cin >> newPrice;
      if (cin.fail()) { // Clear the input buffer if the user enters a non-integer value
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please select a valid option." << endl;
        continue;
      }
      if (crypto == "BTC") {
        bitcoinPrice = newPrice;
      } else if (crypto == "DOGE") {
        dogecoinPrice = newPrice;
      } else if (crypto == "ETH") {
        ethereumPrice = newPrice;
      } else if (crypto == "LTC") {
        litecoinPrice = newPrice;
      } else if (crypto == "XRP") {
        ripplePrice = newPrice;
      } else { 
        cout << "Invalid crypto, try again." << endl;
        continue;
      }
      savePriceToFile();
        cout << "Crypto prices chaanged successfully." << endl;
      break;
      }
    }

  void exitProgram() { // Method to exit program
    stopPriceUpdate = true;
    saveUsersToFile();
    cout << "Exiting. Have a great day!" << endl;
    exit(0);
  }
};
