// Implementation file for the StockDB class

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <limits>
using namespace std;

#include "Stock.h"
#include "BinarySearchTree.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "Utils.h"
#include "Stack.h"
#include "StockDB.h"

//**************************************************
// Constructor
//**************************************************
StockDB::StockDB()
{
    // set to null
    bst = NULL;
    hash = NULL;

    // set to default
    dbFile = DEF_DB_FILENAME;
    dbExtn = DEF_DB_FILEEXTN;
}

//**************************************************
// Destructor
// freeing all memory in the database
//**************************************************
StockDB::~StockDB()
{
    // free all memory
    freeDB();
}

//**************************************************
// freeing all memory in the database
//**************************************************
void StockDB::freeDB()
{
    if (bst) {
        delete bst;
        bst = NULL;
    }
    if (hash) {
        delete hash;
        hash = NULL;
    }
    if (stack) {
        // free deleted books
        while (!stack->isEmpty()) {
            Stock* b = stack->pop();
            delete b;
        }
        // free stack obj
        delete stack;
        stack = NULL;
    }
}

//**************************************************
// create an empty database
//   - input param: hashSize - the size to create internal hash table
//   - return true if successful, otherwise, false
//**************************************************
bool StockDB::initDB(int hashSize)
{
    // delete old DB if it already exists
    freeDB();

    // create BST
    // pass a compare function
    bst = new BinarySearchTree<Stock>(compare);
    if (!bst) {
        cout << "Failed to create BinarySearchTree in StockDB" << endl;
        return false;
    }

    // create Hash table
    // pass a hash function
    hash = new HashTable<Stock>(hashSize, key_to_index);
    if (!hash) {
        cout << "Failed to create HashTable in StockDB" << endl;
        // free BST memory if it has been created
        if (bst) {
            delete bst;
            bst = NULL;
        }
        return false;
    }

    // create Stack
    stack = new Stack<Stock>();
    if (!stack) {
        cout << "Failed to create Stack in BookDB" << endl;
        return false;
    }

    return true;
}

//**************************************************
// show main menu to user 
//**************************************************
void StockDB::showMenu() const
{
    cout << "Stock Database menu:" << endl;
    cout << "T - Display data sorted by Company Name" << endl;
    cout << "P - Primary key search (by Symbol + Date)" << endl;
    cout << "S - Secondary key search (by Company Name)" << endl;
    cout << "A - Add a new stock" << endl;
    cout << "D - Delete a stock (by Symbol + Date)" << endl;
    cout << "E - Delete a stock (by Company Name)" << endl;
    cout << "F - Save to file" << endl;
    cout << "G - Undo delete" << endl;
    cout << "O - Show statistics" << endl;
    cout << "Q - Quit" << endl;
}

//**************************************************
// run main menu loop
//**************************************************
void StockDB::mainMenu()
{
    // show main menu to user
    showMenu();

    bool done = false;
    while (!done) {
        string str;
        cout << "Please enter an option (h - for help): ";
        cin.clear();
        cin >> str;
        if (str == "h") {
            // show menu (hidden option)
            showMenu();
        }
        else if (str == "A") {
            // add a stock
            // if the database is not yet created,
            // it will be created in addStock
            addStock();
        }
        else if (str == "Q") {
            if (!bst || !hash || !hash->getCount()) {
                cout << "Empty Stock database. Skip saving DB." << endl;
            }
            else {
                // save the DB to the default output DB file
                saveToFile(true);
            }
            // quit the program
            cout << "Exit the program" << endl;
            done = true;
        }
        else {
            if (!bst || !hash || !hash->getCount()) {
                // the database is not yet created or empty,
                // do not run the following menu options
                cout << "Empty Stock database" << endl;
            }
            else {
                if (str == "H") {
                    // hidden option
                    // display BST as an indented list 
                    displayBST();
                }
                else if (str == "t") {
                    // hidden option
                    // display the contents of the hash table
                    displayHash();
                }
                else if (str == "T") {
                    // display sorted data by company name
                    displayDB();
                }
                else if (str == "P") {
                    // search stock by symbol and date
                    searchSymbol();
                }
                else if (str == "S") {
                    // search stock by company name
                    searchCompany();
                }
                else if (str == "D") {
                    // delete a stock by symbol and date
                    deleteSymbol();
                }
                else if (str == "E") {
                    // delete a stock by company name
                    deleteCompany();
                }
                else if (str == "F") {
                    // save DB to a file
                    saveToFile();
                }
                else if (str == "G") {
                    undoDelete();
                }
                else if (str == "O") {
                    // show DB's statistics
                    showStatistics();
                }
                else {
                    cout << "Invalid menu option. Try again." << endl;
                }
            }
        }
    }
}

//**************************************************
// display sorted data by company name
// as a table, with header and footer included
//**************************************************
void StockDB::displayDB() const
{
    // header of the table
    cout << left;
    cout << " " << setw(6) << "Symbol" << " ";
    cout << " " << setw(22) << "Company Name" << " ";
    cout << " " << setw(10) << "Date" << " ";
    cout << fixed << setprecision(2);
    cout << " " << setw(9) << "Price" << " ";
    cout << " " << setw(9) << "Day High" << " ";
    cout << " " << setw(9) << "Day Low" << " ";
    cout << " " << setw(9) << "Change" << " ";
    cout << " " << setw(9) << "Volume" << " ";
    cout << " " << setw(9) << "52wk High" << " ";
    cout << " " << setw(9) << "52wk Low" << " ";
    cout << endl;

    // display stocks sorted by company name
    bst->inOrder(tDisplay);
}

//**************************************************
// display BST as an indented list
//**************************************************
void StockDB::displayBST() const
{
    bst->printTree(iDisplay);
}

//**************************************************
// display the contents of the hash table
//**************************************************
void StockDB::displayHash() const
{
    hash->printHash();
}

//**************************************************
// load database from a file to internal bst and hash table
//   - input param: filename - database file to load
//   - return true if successful, otherwise, false
//**************************************************
bool StockDB::loadDB(const string& filename)
{
    // Grabbing input file size size
    int numLines = 0;
    string lineCount;
    ifstream lineCheck(filename);
    if (lineCheck.fail())
    {
        cout << "Error opening the input file: \"" << filename << "\"" << endl;
        return false;
    }

    while (getline(lineCheck, lineCount))
        ++numLines;
    lineCheck.close();

    // return true if the input file is empty
    if (numLines == 0) {
        cout << "Input file is empyt: \"" << filename << "\"" << endl;
        return true;
    }

    int hashSize = nextPrime(numLines * 2);
    string symbol, company, date;
    double price, high, low, change, yearHigh, yearLow;
    int volume;

    ifstream inFile(filename);
    if (inFile.fail())
    {
        cout << "Error opening the input file: \"" << filename << "\"" << endl;
        return false;
    }

    // create an empty database
    if (!initDB(hashSize)) {
        cout << "Failed to create an empty StockDB" << endl;
        // close the file handle
        inFile.close();
        return false;
    }

    numLines = 0;
    string line;
    while (getline(inFile, line))
    {
        numLines++;
        stringstream input(line);
        getline(input, symbol, ' ');
        getline(input, company, ';');
        input.ignore();
        getline(input, date, ';');
        // check for negative or non-numeric input data
        // if there is any error loading the rest of the line,
        // continue to next line 
        input >> price;
        if (input.fail() || price < 0) 
        {
            cout << "Error inserting price from line " << numLines << endl; 
            continue; 
        }
        input >> high;
        if (input.fail() || high < 0) 
        {
            cout << "Error inserting high from line " << numLines << endl;
            continue;
        }
        input >> low;
        if (input.fail() || low < 0) 
        {
            cout << "Error inserting low from line " << numLines << endl;
            continue;
        }
        input >> change;
        if (input.fail()) 
        {
            cout << "Error inserting change from line " << numLines << endl;
            continue;
        }
        input >> volume;
        if (input.fail() || volume < 0) 
        {
            cout << "Error inserting high from line " << volume << endl;
            continue;
        }
        input >> yearHigh;
        if (input.fail() || yearHigh < 0) 
        {
            cout << "Error inserting yearHigh from line " << numLines << endl;
            continue;
        }
        input >> yearLow;
        if (input.fail() || yearLow < 0) 
        {
            cout << "Error inserting yearLow from line " << numLines << endl;
            continue;
        }

        Stock* stk = new Stock(symbol, company, date, price, high, low, change, volume, yearHigh, yearLow);
        if (!stk) 
        {
            cout << "Error creating a Stock object from line " << numLines << endl;
            continue;
        }

        // check if a stock with same symbol and date already exists in the hash
        Stock* dataOut;
        if (hash->search(*stk, dataOut) != -1) 
        {
            cout << "Error loading-a stock with the same symbol and date already exists-from line " << numLines << endl;
            delete stk; // free memory
            continue;
        }

        // checking if inserts are successful
        if (!bst->insert(stk))
        {
            cout << "Error inserting item into BST from line " << numLines << "of input file" << endl;
            delete stk; // free memory
            continue;
        }
        if (!hash->insert(stk))
        {
            cout << "Error inserting item into Hash Table from line " << numLines << "of input file" << endl;
            delete stk; // free memory
            continue;
        }

        // reset values for future checks
        price = -1;
        high = -1;
        low = -1;
        change = -1;
        yearHigh = -1;
        yearLow = -1;
        volume = -1;
        symbol = "";
        company = "";
        date = "";
    }
    inFile.close();
    
    //hash->printHash();
    //hash->showStatistics();
    //bst->inOrder(hDisplay);
    //bst->printTree(iDisplay);
    //cout << endl;

    return true;
}

//**************************************************
// add a Stock
// -return true if successful, otherwise, false
//**************************************************
bool StockDB::addStock()
{
    string symbol, company, date;
    double price, high, low, change, yearHigh, yearLow;
    int volume;

    cout << "What is the symbol of the stock you would like to add or \"\" to quit? ";
    string str;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, str);
    str = trim(str);
    if (!str.empty())
    {
        symbol = str;
    }
    else 
    {
        // user entered empty string, quit adding
        return false;
    }

    cout << "What is the name of the company? ";
    //cin >> company; // this will not handle a string with spaces in it
    while (company.empty()) 
    {
        cin.clear();
        getline(cin, str);
        // trim the leading and trailing spaces
        str = trim(str);
        if (!str.empty()) 
        {
            company = str;
        }
    }

    cout << "When is the stock data from (mm/dd/year)? ";
    cin >> date;
    //there are multiple ways to write a date so we won't parse this one

    // check if a stock with same symbol and date already exists in the hash
    Stock dataIn(symbol, "", date, 0, 0, 0, 0, 0, 0, 0);
    Stock* dataOut;
    if (hash->search(dataIn, dataOut) != -1) 
    {
        cout << "Stock with the same symbol and date already exists. Quit adding." << endl;
        hDisplay(*dataOut);
        return false;
    }

    // check for negative or non-numeric input data
    cout << "What is the stock's price? ";
    cin >> price;
    if (cin.fail() || price < 0)
    {
        cout << "Error inserting price. Aborting." << endl;
        // clear buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    cout << "What is the stock's high (for that day)? ";
    cin >> high;
    if (cin.fail() || high < 0)
    {
        cout << "Error inserting high. Aborting." << endl;
        // clear buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    cout << "What is the stock's low (for that day)? ";
    cin >> low;
    if (cin.fail() || low < 0)
    {
        cout << "Error inserting low. Aborting." << endl;
        // clear buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    cout << "How much did the stock's price change (that day)? ";
    cin >> change;
    cout << "What the volume of the stock? ";
    cin >> volume;
    if (cin.fail() || volume < 0)
    {
        cout << "Error inserting volume. Aborting." << endl;
        // clear buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    cout << "What is the stock's year high price? ";
    cin >> yearHigh;
    if (cin.fail() || yearHigh < 0)
    {
        cout << "Error inserting yearHigh. Aborting." << endl;
        // clear buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    cout << "What is the stock's year low price? ";
    cin >> yearLow;
    if (cin.fail() || yearLow < 0)
    {
        cout << "Error inserting yearLow. Aborting." << endl;
        // clear buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    // the database is not yet created
    if (!bst || !hash) {
        // create an empty database
        if (!initDB(HASH_SIZE)) {
            cout << "Failed to create an empty StockDB" << endl;
            return false;
        }
    }

    // rehash if load factor is greater than 75%
    if (hash->getLoadFactor() > 75.0) {
        rehash();
    }

    Stock* stk = new Stock(symbol, company, date, price, high, low, change, volume, yearHigh, yearLow);
    if (!stk)
    {
        cout << "Error creating a Stock object. Aborting. " << endl;
        return false;
    }

    // checking if inserts are successful
    if (!bst->insert(stk))
    {
        cout << "Error inserting provided stock into BST!" << endl;
        delete stk; // free memory
        return false;
    }
    if (!hash->insert(stk))
    {
        cout << "Error inserting provided stock into HashTable!" << endl;
        delete stk; // free memory
        return false;
    }

    // Stock added successfully
    cout << "Added:" << endl;
    hDisplay(*stk);

    return true;
}

//**************************************************
// search Stock by symbol and date
//**************************************************
void StockDB::searchSymbol() const
{
    string symbol;
    string date;

    // get Symbol from user
    string str;
    cout << "Please enter Symbol to search or \"\" to quit: ";

    // clear buffer before getting new line
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, str);
    str = trim(str);
    if (!str.empty()) {
        symbol = str;
    }
    else {
        // user entered empty string, quit searching
        return;
    }
    
    // get date from user
    bool done = false;
    while (!done) {
        string str;
        cout << "Please enter date (mm/dd/year): ";
        // clear buffer before getting new line
        cin.clear();
        getline(cin, str);
        str = trim(str);
        if (!str.empty()) {
            date = str;
            done = true;
        }
        else {
            cout << "Empty date. Try again." << endl;
        }
    }

    // search the symbol and date in the hash table
    Stock dataIn(symbol, "", date, 0, 0, 0, 0, 0, 0, 0);
    Stock* dataOut;
    if (hash->search(dataIn, dataOut) != -1) {
        cout << "Found:" << endl;
        hDisplay(*dataOut);
    }
    else {
        cout << "Not found" << endl;
    }
}

//**************************************************
// delete Stock by symbol and date
//**************************************************
void StockDB::deleteSymbol()
{
    string symbol;
    string date;

    // get Symbol from user
    string str;
    cout << "Please enter Symbol to delete or \"\" to quit: ";

    // clear buffer before getting new line
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, str);
    str = trim(str);
    if (!str.empty()) {
        symbol = str;
    }
    else {
        // user entered empty string, quit searching
        return;
    }

    // get date from user
    bool done = false;
    while (!done) {
        string str;
        cout << "Please enter date (mm/dd/year): ";
        // clear buffer before getting new line
        cin.clear();
        getline(cin, str);
        str = trim(str);
        if (!str.empty()) {
            date = str;
            done = true;
        }
        else {
            cout << "Empty date. Try again." << endl;
        }
    }

    // delete the item in the hash table by matching symbol
    Stock dataIn(symbol, "", date, 0, 0, 0, 0, 0, 0, 0);
    Stock* dataOut = NULL;
    if (hash->remove(dataIn, dataOut)) {
        Stock* b = NULL;
        // remove the item from bst by matching symbol and date
        if (bst->remove(*dataOut, b)) {
            cout << "Deleted:" << endl;
            hDisplay(*dataOut);
            // push the book object to the stack
            stack->push(b);
        }
        else {
            // this should not happen
            cout << "Failed to delete from bst" << endl;
        }
    }
    else {
        cout << "Not found" << endl;
    }
}

//**************************************************
// search Stock by company name
//**************************************************
void StockDB::searchCompany() const
{
    string str;
    cout << "Please enter company name to search or \"\" to quit: ";

    // clear buffer before getting new line
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, str);
    str = trim(str);

    if (!str.empty()) {
        // search the company name in the bst
        Stock dataIn("", str, "", 0, 0, 0, 0, 0, 0, 0);
        LinkedList<Stock> dataList;
        if (bst->search(dataIn, dataList)) {
            cout << "Found: ";
            if (dataList.getLength() > 1) {
                cout << "(" << dataList.getLength() << " stocks)";
            }
            cout << endl;
            const ListNode<Stock>* cur = dataList.getHead()->getNext();
            while (cur) {
                Stock* b = cur->getItem();
                hDisplay(*b);
                cur = cur->getNext();
            }
        }
        else {
            cout << "Not found" << endl;
        }
    }
}

//**************************************************
// delete Stock by company name
//**************************************************
void StockDB::deleteCompany()
{
    string str;
    cout << "Please enter company name to delete or \"\" to quit: ";

    // clear buffer before getting new line
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, str);
    str = trim(str);

    if (!str.empty()) {
        // search the company name in the bst
        Stock dataIn("", str, "", 0, 0, 0, 0, 0, 0, 0);
        LinkedList<Stock> dataList;
        if (bst->search(dataIn, dataList)) {
            cout << "Deleted: ";
            if (dataList.getLength() > 1) {
                cout << "(" << dataList.getLength() << " stocks)";
            }
            cout << endl;
            const ListNode<Stock>* cur = dataList.getHead()->getNext();
            while (cur) {
                Stock* b = cur->getItem();
                Stock* dataOut = NULL;
                // remove the item from bst
                if (bst->remove(*b, dataOut)) {
                    dataOut = NULL;
                    // remove the item from hash
                    if (hash->remove(*b, dataOut)) {
                        hDisplay(*b);
                        // push the book object to the stack
                        stack->push(b);
                    }
                    else {
                        // this should not happen
                        cout << "Failed to delete from hash" << endl;
                    }
                }
                else {
                    // this should not happen
                    cout << "Failed to delete from bst" << endl;
                }
                cur = cur->getNext();
            }
        }
        else {
            cout << "Not found" << endl;
        }
    }
}

//**************************************************
// rehash internal hash table to 2 times of current size
//**************************************************
bool StockDB::rehash()
{
    if (hash) {
        int hashSize = nextPrime(2 * hash->getSize());
        if (!hash->rehash(hashSize)) {
            cout << "Failed to rehash HashTable in BookDB" << endl;
            return false;
        }
        /* DEBUG
        hash->printHash(hDisplay);
        hash->printStatistics();
        cout << endl;
        */
    }

    return true;
}

//**************************************************
// undo delete
//**************************************************
void StockDB::undoDelete()
{
    // Undo delete stack is empty
    if (stack->isEmpty()) {
        cout << "No deletion to undo" << endl;
        return;
    }

    Stock* b = stack->pop();
    if (hash->insert(b) && bst->insert(b)) {
        cout << "Book undeleted:" << endl;
        hDisplay(*b);
    }
    else {
        cout << "Failed to undelete" << endl;
    }
}

//**************************************************
// save DB to a file
// - input param: an option to use default output filename
//                instead of asking user to enter
//                a filename to save to
//**************************************************
void StockDB::saveToFile(bool useDef)
{
    string str;
    if (!useDef) {
        // Ask user to input a filename
        cout << "What is the name of the output file or \"\" to use the default? ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, str);
        str = trim(str);
    }
    // user input an empty string or no user input, then
    // use default filename
    if (str.empty()) {
        str = dbFile;
    }
    string filename = str + "." + dbExtn;

    // save DB to a file
    // if the file already exists, overwrite it
    if (hash->saveToFile(filename)) {
        cout << "Saved Stock database to " << filename << endl;
    }
    else {
        cout << "Error saving Stock database" << endl;
    }
}

//**************************************************
// show statistics of the database
//**************************************************
void StockDB::showStatistics() const
{
    hash->showStatistics();
}

