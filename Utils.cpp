// Implementation file for utility functions
// This cpp file contains a few utility functions used by 
// the stock DB project

#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

#include "Stock.h"
#include "Utils.h"

//**************************************************
// horizontal display : all items on one line
// - input param: stock object
//**************************************************
void hDisplay(Stock& item)
{
    cout << fixed << setprecision(2);
    cout << item.getCompanyName() << " ("
        << item.getSymbol() << ") "
        << item.getDate() << " "
        << item.getPrice() << " "
        << (item.getChange() > 0 ? "+" : "")
        << item.getChange()
        << " Day's Range "
        << item.getLow() << "-" << item.getHigh()
        << " 52-Week Range "
        << item.getYearLow() << "-" << item.getYearHigh()
        << " Volume " << item.getVolume() << endl;
}

//**************************************************
// table format display : all items on one line
// - input param: stock object
//**************************************************
void tDisplay(Stock& item)
{
    cout << left;
    cout << " " << setw(6) << item.getSymbol() << " ";
    cout << " " << setw(22) << item.getCompanyName() << " ";
    cout << " " << setw(10) << item.getDate() << " ";
    cout << fixed << setprecision(2);
    cout << " " << setw(9) << item.getPrice() << " ";
    cout << " " << setw(9) << item.getHigh() << " ";
    cout << " " << setw(9) << item.getLow() << " ";
    cout << " " << setw(9) << item.getChange() << " ";
    cout << " " << setw(9) << item.getVolume() << " ";
    cout << " " << setw(9) << item.getYearHigh() << " ";
    cout << " " << setw(9) << item.getYearLow() << " ";
    cout << endl;
}

//**************************************************
// indented tree display: one item per line, including the level number
// - input param: stock object and the level of the tree to display
//**************************************************
void iDisplay(Stock& item, int level)
{
    for (int i = 1; i < level; i++)
        cout << "..";
    cout << level << "). " << item.getCompanyName() << endl;
}

//**************************************************
// Hash function: takes the key and returns the index in the hash table
// - input params: stock object
//                 the size of the hash table
//**************************************************
int key_to_index(const Stock& key, int size)
{
    string k = key.getUniqueKey();
    int sum = 0;
    for (int i = 0; k[i]; i++)
        sum += k[i];
    return sum % size;
};

//**************************************************
// compare two Stock objects
// - compare the secondary key (company name) of Stock object
// - input params: two Stock objects 
// - return 0 if two is equal
//         -1 if b1 is less than b2
//          1 if b1 is greater than b2
//**************************************************
int compare(const Stock& b1, const Stock& b2)
{
    if (b1.getCompanyName() == b2.getCompanyName()) {
        return 0;
    }
    else if (b1.getCompanyName() < b2.getCompanyName()) {
        return -1;
    }
    
    // b1.getCompanyName() > b2.getCompanyName()
    return 1;
}

//**************************************************
// check if a number is prime
// - input param: a number
//**************************************************
bool isPrime(int n)
{
    // Corner cases
    if (n <= 1)  return false;
    if (n <= 3)  return true;

    // This is checked so that we can skip 
    // middle five numbers in below loop
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;

    return true;
}

//**************************************************
// return the smallest prime number greater than N
// - input param: a number
//**************************************************
int nextPrime(int N)
{

    // Base case
    if (N <= 1)
        return 2;

    int prime = N;
    bool found = false;

    // Loop continuously until isPrime returns
    // true for a number greater than n
    while (!found) {
        prime++;

        if (isPrime(prime))
            found = true;
    }

    return prime;
}

//**************************************************
// Trim a string in C++ – Remove leading and trailing spaces
//**************************************************

const string WHITESPACE = " \n\r\t\f\v";

string ltrim(const string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}

string rtrim(const string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string trim(const string& s) {
    return rtrim(ltrim(s));
}
