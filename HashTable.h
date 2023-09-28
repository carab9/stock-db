// Specification file for the HashTable class
// It is the hash table class which contains an array of HashNodes
//

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <string>
using std::string;

#include "HashNode.h"

template<class ItemType>
class HashTable
{
private:
    const int HASH_SIZE = 101;
    HashNode<ItemType>* hashAry;
    int hashSize;
    int count;

    // hash function pointer
    int (*h)(const ItemType& key, int size);

public:
    // the constructor takes a hash function pointer
    // used by the hash table
    HashTable(int hf(const ItemType& key, int size)) 
    {
        hashSize = HASH_SIZE; 
        hashAry = new HashNode<ItemType>[hashSize];
        count = 0; 
        h = hf;
    }
    HashTable(int n, int hf(const ItemType& key, int size))
    {
        hashSize = n; 
        hashAry = new HashNode<ItemType>[hashSize];
        count = 0; 
        h = hf;
    }
    ~HashTable();

    int getCount() const {return count;}
    int getSize() const {return hashSize;}
    double getLoadFactor() const {return 100.0 * count / hashSize;}
    bool isEmpty() const {return count == 0;}
    bool isFull() const {return count == hashSize;}
    
    // insert, remove, search fuctions
    bool insert(ItemType* dataIn);
    bool remove(const ItemType &key, ItemType*& dataOut);
    int  search(const ItemType &key, ItemType*& dataOut);

    // show the statistics of the hash table
    void showStatistics() const;

    // rehash the hash table to a new size
    bool rehash(int n);

    // print the hash
    void printHash() const;

    // save the items in the hash table to a file
    bool saveToFile(const string& filename); 
};

//**************************************************
// Destructor
//**************************************************
template<class ItemType>
HashTable<ItemType>::~HashTable() 
{
    // delete all the items in the hash array
    for (int i = 0; i < hashSize; i++) {
        if (hashAry[i].getOccupied()) {
            const LinkedList<ItemType>& items = hashAry[i].getItems();
            const ListNode<ItemType>* cur = items.getHead()->getNext();
            while (cur) {
                ItemType* item = cur->getItem();
                // free item object
                delete item;
                cur = cur->getNext();
            }
        }
    }

    // delete the hash array
    delete[] hashAry; 
}

//**************************************************
// Insert an item into the hash table
// - input param: the pointer to the data to be inserted
// - return true 
//**************************************************
template<class ItemType>
bool HashTable<ItemType>::insert(ItemType* dataIn)
{
    // get the index to the hash table from the key 
    int index = h(*dataIn, hashSize);
    
    if (!hashAry[index].getOccupied()) {
        // first insertion for the index
        count++;
    }

    // add the item to the item list of the hash node
    hashAry[index].addItem(dataIn);

    return true;
}

//**************************************************
// Removes the item with the matching key from the hash table
// - input param: target data
// - return true if found, otherwise, false
//   copies data in the hash node to dataOut
//**************************************************
template<class ItemType>
bool HashTable<ItemType>::remove(const ItemType &key, ItemType*& dataOut)
{
    // get the index to the hash table from the key 
    int index = h(key, hashSize);

    // delete the item from the item list of the hash node
    if (hashAry[index].deleteItem(key, dataOut)) {
        if (!hashAry[index].getOccupied()) {
            // the hash node has no item
            count--;
        }
        return true;
    }

    return false;
 }

//**************************************************
//   hash search
// - input param: target data
//   if found:
//      - copy data to dataOut
//      - returns the number of collisions for this key
//   if not found, returns -1
//***************************************************
template<class ItemType>
int HashTable<ItemType>::search(const ItemType &key, ItemType*& dataOut)
{
    // get the index to the hash table from the key 
    int index = h(key, hashSize);

    // search the item from the item list of the hash node
    if (hashAry[index].searchItem(key, dataOut)) {
   	int nCol = hashAry[index].getNoCollisions();
        return nCol;
    }

    return -1;
}

//**************************************************
// show the statistics of the hash table
//**************************************************
template<class ItemType>
void HashTable<ItemType>::showStatistics() const
{
    int noCollisions = 0;
    int maxItems = 0;
    int maxNodes = 0;
    for (int i = 0; i < hashSize; i++) {
        if (hashAry[i].getOccupied()) {
            if (hashAry[i].getNoCollisions() > 0) {
                noCollisions += hashAry[i].getNoCollisions();
            }
            int noItems = hashAry[i].getItems().getLength();
            if (noItems) {
                if (maxItems == noItems) {
                    maxNodes++;
                }
                else if (maxItems < noItems) {
                    maxItems = noItems;
                    maxNodes = 1;
                }
            }
        }
    }

    cout << "Load factor: " << getLoadFactor() << endl;
    cout << "Total number of collisions: " << noCollisions << endl;
    cout << "Length of the longest linked list: " << maxItems << endl;
    cout << "Number of linked lists with the longest length: " << maxNodes << endl;
}

//**************************************************
// rehash the hash table to a new size
//**************************************************
template<class ItemType>
bool HashTable<ItemType>::rehash(int n)
{
    if (n <= hashSize) {
        return false;
    }

    HashNode<ItemType>* newHashAry = new HashNode<ItemType>[n];
    int cnt = 0;

    // re-insert all the items in the hash array to the new hash array
    for (int i = 0; i < hashSize; i++) {
        if (hashAry[i].getOccupied()) {
            const LinkedList<ItemType>& items = hashAry[i].getItems();
            const ListNode<ItemType>* cur = items.getHead()->getNext();   
            while (cur) {
                ItemType* item = cur->getItem();
                int index = h(*item, n);
                if (!newHashAry[index].getOccupied()) {
                    // first insertion for the index
                    cnt++;
                }
                newHashAry[index].addItem(item);
                cur = cur->getNext();
            }
        }
    }

    // delete the old hash node array
    delete [] hashAry;

    // update new hash node array, hash size and count
    hashAry = newHashAry;
    hashSize = n;
    count = cnt;

    return true;
}

//**************************************************
// print the contents of the hash table
//**************************************************
template<class ItemType>
void HashTable<ItemType>::printHash() const
{
    cout << "Hash size: " << hashSize << endl;
    for (int i = 0; i < hashSize; i++) {
        if (hashAry[i].getOccupied()) {
            cout << "Hash index: " << i << ", ";
            cout << "No. collisions: " << hashAry[i].getNoCollisions() << endl;
            hashAry[i].getItems().displayList();
        }
    }
}

//**************************************************
// save the items in the hash table to a file
// - input param: output filename
// - return true if successful, otherwise, false
//**************************************************
template<class ItemType>
bool HashTable<ItemType>::saveToFile(const string& filename)
{
    // open an output file to write
    ofstream outFile(filename);
    if (outFile.fail()) {
        return false;
    }

    // iterate through all the items in the hash array and write
    // them to an output file
    for (int i = 0; i < hashSize; i++) {
        if (hashAry[i].getOccupied()) {
            const LinkedList<ItemType>& items = hashAry[i].getItems();
            const ListNode<ItemType>* cur = items.getHead()->getNext();
            while (cur) {
                ItemType* item = cur->getItem();
                outFile << (*item);
                cur = cur->getNext();
            }
        }
    }

    // close the file handle
    outFile.close();

    return true;
}


#endif // HASH_TABLE_H_
