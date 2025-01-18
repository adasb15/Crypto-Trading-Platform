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
  atomic<bool> stopPriceUpdate;

public:
  CryptoTradingPlatform() : stopPriceUpdate(false) {
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
      bitcoinPrice = 34000.0;
      dogecoinPrice = 0.67;
    }
  }

  void loadUsersFromFile() { // Method to load users from file
    ifstream file("users.txt");
    if (file.is_open()) {
      string username, password, transaction;
      double balance, bitcoinHolding, dogecoinHolding;
      while (file >> username >> password >> balance >> bitcoinHolding >>
             dogecoinHolding) {
        users[username] = User(username, password, balance);
        users[username].bitcoinHolding = bitcoinHolding;
        users[username].dogecoinHolding = dogecoinHolding;

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
           << " " << entry.second.dogecoinHolding << " ";
      for (const string &transaction : entry.second.transactions) {
        file << transaction << " ";
      }
      file << endl;
    }
    file.close();
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

    while (!stopPriceUpdate) {
      bitcoinPrice += bitcoinPrice * distribution(generator);
      dogecoinPrice += dogecoinPrice * distribution(generator);
      cout << "Bitcoin price: $" << bitcoinPrice << endl;
      cout << "Dogecoin price: $" << dogecoinPrice << endl;
      ofstream priceFile("crypto_prices.txt");
      if (priceFile.is_open()) {
        priceFile << bitcoinPrice << " " << dogecoinPrice << endl;
        priceFile.close();
      }
      this_thread::sleep_for(chrono::seconds(30));
    }
  }

  void exitProgram() { // Method to exit program
    stopPriceUpdate = true;
    saveUsersToFile();
    cout << "Exiting. Have a great day!" << endl;
    exit(0);
  }
};