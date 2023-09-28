// Specification file for utility functions

#ifndef UTILS_H_
#define UTILS_H_

#include <string>

// Forward Declaration
class Stock; 

// horizontal display of a stock
void hDisplay(Stock&);

// table format display of a stock
void tDisplay(Stock&);

// indented tree display of a stock
void iDisplay(Stock&, int);

// hash function - takes the key and returns 
// the index in the hash table
int key_to_index(const Stock& key, int size);

// compare the company names of two Stock objects
int compare(const Stock& b1, const Stock& b2);

// check if a number is prime
bool isPrime(int n);

// return the smallest prime number greater than N
int nextPrime(int N);

// Trim a string in C++ – Remove leading and trailing spaces
string ltrim(const string& s);
string rtrim(const string& s);
string trim(const string& s);

#endif // UTILS_H_

