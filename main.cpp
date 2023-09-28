// Stock Database main file main.cpp

#include <iostream>
using namespace std;

#include "StockDB.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Stock DB input filename is needed in the command line argument." << endl;
        return 0;
    }

    // get the Stock DB input filename
    string filename = argv[1];

    // create a StockDB, load DB, and run main menu
    StockDB stockDB;
    if (stockDB.loadDB(filename)) {
        cout << "Stock database " << filename << " loaded." << endl; 
        stockDB.mainMenu();
    }
    else {
        cout << "Failed to load Stock database " << filename << endl;
    }
    
    return 0;
}

