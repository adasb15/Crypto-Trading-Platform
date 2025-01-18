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

class CryptoTradingPlatform {  // Class representing a Crypto Trading Platform
private:
    map<string, User> users;  // Map to store users
    double bitcoinPrice;
    double dogecoinPrice;
    double ethereumPrice;
    double litecoinPrice;
    double ripplePrice;

public: // Constructor
    CryptoTradingPlatform(){
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
            savePriceToFile();
        }
    }

    void loadUsersFromFile() { // Method to load users from file
        ifstream file("users.txt");
        if (file.is_open()) {
            // Loop to read user data from the file
            string username, password, transaction;
            double initialBalance, balance, bitcoinHolding, dogecoinHolding, ethereumHolding, litecoinHolding, rippleHolding;
            while (file >> username >> password >> initialBalance >> balance >> bitcoinHolding >>
                        dogecoinHolding >> ethereumHolding >> litecoinHolding >> rippleHolding) {
                // Create User objects and load their transaction history
                users[username] = User(username, password, balance);
                users[username].initialBalance = initialBalance;
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
            // Loop to write user data to the file
            for (const auto &entry : users) {
                file  << fixed << entry.second.username << " " << fixed << entry.second.password << " " << fixed
                      << entry.second.initialBalance << " " << fixed << entry.second.balance << " "
                      << fixed << entry.second.bitcoinHolding << " " << fixed << entry.second.dogecoinHolding << " "
                      << fixed << entry.second.ethereumHolding << " " << fixed << entry.second.litecoinHolding << " "
                      << fixed << entry.second.rippleHolding;
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

    void exitProgram() { // Method to exit program
        saveUsersToFile();
        cout << "Exiting. Have a great day!" << endl;
        exit(0);
    }

    // admin function
    void viewUserList() { // Method to view user list
        cout << "User List:" << endl;
        for (const auto &entry : users) {
            cout << "Username: " << fixed << entry.second.username << ", Balance: $" << entry.second.balance;
            cout << ", Bitcoin: " << fixed << entry.second.bitcoinHolding << " BTC";
            cout << ", Dogecoin: " << fixed << entry.second.dogecoinHolding << " DOGE";
            cout << ", Ethereum: " << fixed << entry.second.ethereumHolding << " ETH";
            cout << ", Litcoin: " << fixed << entry.second.litecoinHolding << " LTC";
            cout << ", Ripple: " << fixed << entry.second.rippleHolding << " XRP";
        }
    }

    void viewCryptoPrices() { // Method to view crypto prices
        loadPriceFromFile();
        cout << "Current Crypto Prices:" << endl;
        cout << "Bitcoin Price: $" << fixed << bitcoinPrice << endl;
        cout << "Dogecoin Price: $" << fixed << dogecoinPrice << endl;
        cout << "Ethereum Price: $" << fixed << ethereumPrice << endl;
        cout << "Litecoin Price: $" << fixed << litecoinPrice << endl;
        cout << "Ripple Price: $" << fixed << ripplePrice << endl;
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
};
