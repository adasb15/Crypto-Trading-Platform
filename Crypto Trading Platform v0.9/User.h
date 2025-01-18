#include <fstream>
#include <iostream>
#include <map>
#include <random>
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
  void showCryptoWallet() { // Method to show user's crypto wallet
    cout << "Crypto Wallet for " << username << ":" << endl;
    cout << "Bitcoin: " << bitcoinHolding << " BTC" << endl;
    cout << "Dogecoin: " << dogecoinHolding << " DOGE" << endl;
  }
};
