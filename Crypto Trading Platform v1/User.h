#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <vector>

using namespace std;

// Base class representing a basic user with common attributes and operations
class BaseUser {
public:
    string username;
    string password;
    double initialBalance;
    double balance;
    vector<string> transactions;

    // Default constructor
    BaseUser() : username(""), password(""), initialBalance(0.0), balance(0.0) {}

    // Parameterized constructor
    BaseUser(string u, string p, double b) : username(u), password(p), initialBalance(b), balance(b) {}

    // Virtual function to display account information (can be overridden in derived classes)
    virtual void displayAccountInfo() {
        cout << "Account balance for " << username << ": $" << balance << endl;
    }

    // Function to deposit money into the account
    void deposit(double amount) {
        balance += amount;
        initialBalance += amount;
        transactions.push_back("Deposited $ " + to_string(amount));
        cout << "Account balance for " << username << ": $" << balance << endl;
    }

    // Function to withdraw money from the account
    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            initialBalance -= amount;
            transactions.push_back("Withdrew $ " + to_string(amount));
            cout << "Account balance for " << username << ": $" << balance << endl;
        } else {
            cout << "Insufficient funds." << endl;
        }
    }

    // Function to display transaction history
    void checkTransactions() {
        cout << "Transaction History for " << username << ":" << endl;
        for (const string &transaction : transactions) {
            cout << transaction << endl;
        }
    }

    // Function to change user password
    void changePassword() {
        // Input old and new passwords, check if old passwords match and set the new password
        string testpassword, testpassword2, newpassword, newpassword2;
        cout << "Enter your old password: " << endl;
        cin >> testpassword;
        cout << "Enter your old password again: " << endl;
        cin >> testpassword2;
        cout << "Enter your new password: " << endl;
        cin >> newpassword;
        cout << "Enter your new password again: " << endl;
        cin >> newpassword2;

        if (testpassword == password && testpassword2 == password && newpassword == newpassword2) {
            password = newpassword;
            cout << "Password changed successfully." << endl;
        } else {
            cout << "Incorrect password. Password not changed." << endl;
        }
    }
};

// Derived class representing a user with additional cryptocurrency-related attributes and operations
class User : public BaseUser {
private:
    double bitcoinPrice;
    double dogecoinPrice;
    double ethereumPrice;
    double litecoinPrice;
    double ripplePrice;

public:
    double bitcoinHolding;
    double dogecoinHolding;
    double ethereumHolding;
    double litecoinHolding;
    double rippleHolding;

    // Default constructor
    User() : BaseUser(), bitcoinHolding(0.0), dogecoinHolding(0.0), ethereumHolding(0.0), litecoinHolding(0.0), rippleHolding(0.0) {}

    // Parameterized constructor
    User(string u, string p, double b)
            : BaseUser(u, p, b), bitcoinHolding(0.0), dogecoinHolding(0.0), ethereumHolding(0.0), litecoinHolding(0.0), rippleHolding(0.0) {}

    // Function to load cryptocurrency prices from a file
    void loadCryptoPrices() {
        ifstream priceFile("crypto_prices.txt");
        if (priceFile.is_open()) {
            priceFile >> bitcoinPrice;
            priceFile >> dogecoinPrice;
            priceFile >> ethereumPrice;
            priceFile >> litecoinPrice;
            priceFile >> ripplePrice;
            priceFile.close();
        }
    }

    // Function to display cryptocurrency prices
    void showCryptoPrices() {
        loadCryptoPrices();
        cout << "\nBitcoin price: $" << fixed << bitcoinPrice << endl;
        cout << "Dogecoin price: $" << fixed << dogecoinPrice << endl;
        cout << "Ethereum price: $" << fixed << ethereumPrice << endl;
        cout << "Litecoin price: $" << fixed << litecoinPrice << endl;
        cout << "Ripple price: $" << fixed << ripplePrice << endl;
    }

    // Override function to display user account information with cryptocurrency details
    void displayAccountInfo() override {
        double balanceDifference = balance - initialBalance;
        cout << "Balance change since account creation: $" << fixed << balanceDifference << endl;
        cout << "Account balance for " << username << ": $" << fixed << balance << endl;
        cout << "Bitcoin: " << bitcoinHolding << " BTC" << endl;
        cout << "Dogecoin: " << dogecoinHolding << " DOGE" << endl;
        cout << "Ethereum: " << ethereumHolding << " ETH" << endl;
        cout << "Litecoin: " << litecoinHolding << " LTC" << endl;
        cout << "Ripple: " << rippleHolding << " XRP" << endl;
    }

    // Functions to buy and sell Bitcoin
    void buyBitcoin(double amount) {
        loadCryptoPrices();
        if (amount * bitcoinPrice <= balance) {
            bitcoinHolding += amount;
            balance -= amount * bitcoinPrice;
            transactions.push_back("Bought " + to_string(amount) + " BTC");
            cout << "Account bitcoin for " << username << ": BTC" << fixed << bitcoinHolding << endl;
        } else {
            cout << "Insufficient balance to buy Bitcoin." << endl;
        }
    }

    void sellBitcoin(double amount) {
        loadCryptoPrices();
        if (amount <= bitcoinHolding) {
            bitcoinHolding -= amount;
            balance += amount * bitcoinPrice;
            transactions.push_back("Sold " + to_string(amount) + " BTC");
            cout << "Account bitcoin for " << username << ": BTC" << fixed << bitcoinHolding << endl;
        } else {
            cout << "Insufficient Bitcoin holdings to sell." << endl;
        }
    }

    // Functions to buy and sell Dogecoin
    void buyDogecoin(double amount) {
        loadCryptoPrices();
        if (amount * dogecoinPrice <= balance) {
            dogecoinHolding += amount;
            balance -= amount * dogecoinPrice;
            transactions.push_back("Bought " + to_string(amount) + " DOGE");
            cout << "Account dogecoin for " << username << ": DOGE" << fixed << dogecoinHolding << endl;
        } else {
            cout << "Insufficient balance to buy Dogecoin." << endl;
        }
    }

    void sellDogecoin(double amount) {
        loadCryptoPrices();
        if (amount <= dogecoinHolding) {
            dogecoinHolding -= amount;
            balance += amount * dogecoinPrice;
            transactions.push_back("Sold " + to_string(amount) + " DOGE");
            cout << "Account dogecoin for " << username << ": DOGE" << fixed << dogecoinHolding << endl;
        } else {
            cout << "Insufficient Dogecoin holdings to sell." << endl;
        }
    }

    // Functions to buy and sell Ethereum
    void buyEthereum(double amount) {
        loadCryptoPrices();
        if (amount * ethereumPrice <= balance) {
            ethereumHolding += amount;
            balance -= amount * ethereumPrice;
            transactions.push_back("Bought " + to_string(amount) + " ETH");
            cout << "Account ethereum for " << username << ": ETH" << fixed << ethereumHolding << endl;
        } else {
            cout << "Insufficient balance to buy Ethereum." << endl;
        }
    }

    void sellEthereum(double amount) {
        loadCryptoPrices();
        if (amount <= ethereumHolding) {
            ethereumHolding -= amount;
            balance += amount * ethereumPrice;
            transactions.push_back("Sold " + to_string(amount) + " ETH");
            cout << "Account ethereum for " << username << ": ETH" << fixed << ethereumHolding << endl;
        } else {
            cout << "Insufficient Ethereum holdings to sell." << endl;
        }
    }

    // Functions to buy and sell Litecoin
    void buyLitecoin(double amount) {
        loadCryptoPrices();
        if (amount * litecoinPrice <= balance) {
            litecoinHolding += amount;
            balance -= amount * litecoinPrice;
            transactions.push_back("Bought " + to_string(amount) + " LTC");
            cout << "Account litecoin for " << username << ": LTC" << fixed << litecoinHolding << endl;
        } else {
            cout << "Insufficient balance to buy Litecoin." << endl;
        }
    }

    void sellLitecoin(double amount) {
        loadCryptoPrices();
        if (amount <= litecoinHolding) {
            litecoinHolding -= amount;
            balance += amount * litecoinPrice;
            transactions.push_back("Sold " + to_string(amount) + " LTC");
            cout << "Account litecoin for " << username << ": LTC" << fixed << litecoinHolding << endl;
        } else {
            cout << "Insufficient Litecoin holdings to sell." << endl;
        }
    }

    // Functions to buy and sell Ripple
    void buyRipple(double amount) {
        loadCryptoPrices();
        if (amount * ripplePrice <= balance) {
            rippleHolding += amount;
            balance -= amount * ripplePrice;
            transactions.push_back("Bought " + to_string(amount) + " XRP");
            cout << "Account ripple for " << username << ": XRP" << fixed << rippleHolding << endl;
        } else {
            cout << "Insufficient balance to buy Ripple." << endl;
        }
    }

    void sellRipple(double amount) {
        loadCryptoPrices();
        if (amount <= rippleHolding) {
            rippleHolding -= amount;
            balance += amount * ripplePrice;
            transactions.push_back("Sold " + to_string(amount) + " XRP");
            cout << "Account ripple for " << username << ": XRP" << fixed << rippleHolding << endl;
        } else {
            cout << "Insufficient Ripple holdings to sell." << endl;
        }
    }
};
