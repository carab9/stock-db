// Specification file for the StockDB class
// StockDB class have many functions for managing
// stock database, such as show menu, run main
// menu for user to display DB, search, add, and
// delete stocks, load DB, and save DB to file, etc.

#ifndef Stock_DB_H_
#define Stock_DB_H_

// Forward Declaration
class Stock;

template<class ItemType>
class BinarySearchTree;

template<class ItemType>
class HashTable;

template<class ItemType>
class Stack;

class StockDB
{
private:
    // BST and hash table
    BinarySearchTree<Stock>* bst;
    HashTable<Stock>* hash;

    // Undo delete stack
    Stack<Stock>* stack;

    // default DB output filename
    string dbFile;

    // default DB extension
    string dbExtn;

    // default hash size
    static const int HASH_SIZE = 101;

    // default DB output filename
    const string DEF_DB_FILENAME = "outStockDB";

    // default DB file extension
    const string DEF_DB_FILEEXTN = "txt";

private:
    // free database memory
    void freeDB();

    // create an empty DB
    bool initDB(int hashSize);

public:
    StockDB();
    ~StockDB();

    // setters
    void setDBFile(const string& name) {dbFile = name;}
    void setDBExtn(const string& ext) {dbExtn = ext;}

    // getters
    string getDBFile() const {return dbFile;}
    string getDBExtn() const {return dbExtn;}

    // show main menu to user
    void showMenu() const;

    // run main menu loop
    void mainMenu();

    // display sorted data by company name
    // as a table, with header and footer included
    void displayDB() const;

    // display BST as an indented list
    void displayBST() const;

    // display the contents of the hash table
    void displayHash() const;

    // load database from a file to internal bst and hash table
    bool loadDB(const string& filename);

    // add a stock
    bool addStock();

    // search stock by symbol and date
    void searchSymbol() const;

    // delete stock by symbol and date
    void deleteSymbol();

    // search stock by company name
    void searchCompany() const;

    // delete stock by company name
    void deleteCompany();

    // rehash internal hash table to 2 times of current size
    bool rehash();

    // undo delete
    void undoDelete();

    // save DB to a file
    // ask user to input a filename if useDef is false
    // otherwise, use the default output DB filename
    void saveToFile(bool useDef = false);

    // show statistics
    void showStatistics() const;

};

#endif // Stock_DB_H_

