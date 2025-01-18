#include <fstream>
#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    double bitcoinPrice;
    double dogecoinPrice;
    double ethereumPrice;
    double litecoinPrice;
    double ripplePrice;

    srand(time(NULL));
    
    while (true) {  //infinity loop  
        ifstream inFile("crypto_prices.txt"); // read crypto prices from file
        if (inFile.is_open()) {
            inFile >> bitcoinPrice >> dogecoinPrice >> ethereumPrice >> litecoinPrice >> ripplePrice;
            inFile.close();
        } else {  // if file doesn't exist
            bitcoinPrice = 34000.0;
            dogecoinPrice = 0.67;
            ethereumPrice = 2100.0;
            litecoinPrice = 60.0;
            ripplePrice = 0.5;
        }
        // change a crypto prices
        bitcoinPrice = bitcoinPrice * (rand() % 2000001 + 990000) / 1000000.0;
        dogecoinPrice = dogecoinPrice * (rand() % 2000001 + 990000) / 1000000.0;
        ethereumPrice = ethereumPrice * (rand() % 2000001 + 990000) / 1000000.0;
        litecoinPrice = litecoinPrice * (rand() % 2000001 + 990000) / 1000000.0;
        ripplePrice = ripplePrice * (rand() % 2000001 + 990000) / 1000000.0;

        // display new prices
        cout << "\nBitcoin price: $" << bitcoinPrice << endl;
        cout << "Dogecoin price: $" << dogecoinPrice << endl;
        cout << "Ethereum price: $" << ethereumPrice << endl;
        cout << "Litecoin price: $" << litecoinPrice << endl;
        cout << "Ripple price: $" << ripplePrice << endl;

        // save new prices to file
        ofstream outFile("crypto_prices.txt");
        if (outFile.is_open()) {
            outFile << bitcoinPrice << " " << dogecoinPrice << " " << ethereumPrice << " " << litecoinPrice << " " << ripplePrice << endl;
            outFile.close();
        }
        
        Sleep(5000);  // wait 5 seconds for next change
    }
}
