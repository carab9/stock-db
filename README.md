# stock-db

This project is a stock database management tool using a list of data structures such as templated binary search tree, hash table, linked list, and stack. The main program reads a stock database text file (stocksDB.txt), creates a list of Stock class objects, and inserts the pointers of the Stock objects into two data structures: a BinarySearchTree and a HashTable. Then it displays the main menu with several options for users to manage the stock database. 

The BinarySearchTree (BST) orders the Stock objects by their company names, and the HashTable indexes the Stock objects by the unique key for a stock, that is, the stock symbol plus the date. There are two ways to search the StockDB database from the main menu. One way is by company name, hence the BST will be used to search, and the other way is by stock symbol and date, hence the HashTable will be used to search. The HashTable uses LinkedList to resolve conflicts.

When a Stock gets deleted, its pointer is stored in a Stack class object, so there is a chance to undo the delete. The HashTable will automatically rehash the size if its load factor is greater than 75%.

The Stock objects get deleted when the main StockDB object's destructor is called during the shutdown of the main program. The HashTable destructor is called inside the StockDB destructor and it will delete the Stock objects. Also, the Stock objects (from the menu's delete a stock option) saved in the Stack object will be deleted in the destructor of StockDB to free up the memory.

The main menu options:

T - Display data sorted by Company Name

P - Primary key search (by Symbol + Date)

S - Secondary key search (by Company Name)

A - Add a new stock

D - Delete a stock (by Symbol + Date)

E - Delete a stock (by Company Name)

F - Save to file

G - Undo delete

O - Show statistics

Q - Quit

There are also two hidden options:

H - display BST as an indented list

t - display the contents of the hash table

## Architecture

Main menu structure

![image](https://github.com/carab9/stock-db/blob/main/stockdb_menu_structure.jpg?raw=true)

Data diagram

![image](https://github.com/carab9/stock-db/blob/main/stockdb_data_diagram.jpg?raw=true)

Class diagram

![image](https://github.com/carab9/stock-db/blob/main/stockdb_class_diagram.jpg?raw=true)

## Requirements

C++ and C++ libararies: fstream, sstream.

## Techical Skills:

C++, C++ templates, data structures: stack, linked list, hash table, binary search tree (insert, delete and search operations) file IO.

## Results

Main menu

![image](https://github.com/carab9/stock-db/blob/main/stockdb1.png?raw=true)

Menu option

T - Display data sorted by Company Name

![image](https://github.com/carab9/stock-db/blob/main/stockdb2.png?raw=true)

Menu option

O - Show statistics

F - Save to file

![image](https://github.com/carab9/stock-db/blob/main/stockdb3.png?raw=true)

Menu option

S - Secondary key search (by Company Name)

E - Delete a stock (by Company Name)

G - Undo delete

![image](https://github.com/carab9/stock-db/blob/main/stockdb4.png?raw=true)

Menu hidden option

H - display BST as an indented list

![image](https://github.com/carab9/stock-db/blob/main/stockdb5.png?raw=true)

Menu hidden option

t - display the contents of the hash table

![image](https://github.com/carab9/stock-db/blob/main/stockdb6.png?raw=true)

