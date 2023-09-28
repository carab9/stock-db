// Specification file for the HashNode class
// It is the hash node class used by HashTable class
// It uses lined list to resolve collisions

#ifndef HASH_NODE_H_
#define HASH_NODE_H_

#include "LinkedList.h"

template<class ItemType>
class HashNode
{
private:
    LinkedList<ItemType> items;  // list of items
    int occupied;                // 0 or 1
    int noCollisions;            // #items-1

public:
    // constructors
    HashNode() {occupied = 0; noCollisions = 0;}

    // getters
    const LinkedList<ItemType>& getItems() const {return items;}
    int getOccupied() const {return occupied;}
    int getNoCollisions() const {return noCollisions;}

    // other functions
    bool addItem(ItemType*);
    bool deleteItem(const ItemType&, ItemType*&);
    bool searchItem(const ItemType&, ItemType*&);
};

//**************************************************
// Add an item to the item list of the hash node
// - input param: the pointer to the data to be inserted
// - return true 
//**************************************************
template<class ItemType>
bool HashNode<ItemType>::addItem(ItemType* dataIn)
{
    // add the item to the list    
    items.insertNode(dataIn);

    if (!occupied) {
        // first item in the list
        occupied = 1;
    }
    else {
        // increment the num of collisions
        noCollisions++;
    }
    return true;
}

//**************************************************
// Delete an item from the item list of the hash node
// - input param: target data
// - return true if found, otherwise false
//   return the data found via output parameter
//**************************************************
template<class ItemType>
bool HashNode<ItemType>::deleteItem(const ItemType& target, ItemType*& dataOut)
{
    // the hash node is empty
    if (!occupied) {
        return false;
    }

    // delete the item from the list
    if (items.deleteNode(target, dataOut)) {
        if (noCollisions > 0) {
            noCollisions--;
        }
        // deleted the last item
        if (items.getLength() == 0) {
            occupied = 0;
        }          
        return true;
    }

    return false;
}

//**************************************************
// Search an item in the item list of the hash node
// - input param: target data
// - return true if found, otherwise false
//   return the data found via output parameter
//**************************************************
template<class ItemType>
bool HashNode<ItemType>::searchItem(const ItemType& target, ItemType*& dataOut)
{
    // the hash node is empty
    if (!occupied) {
        return false;
    }

    if (items.searchList(target, dataOut)) {
        // this item is in the item list
        return true;
    }

    return false;
}

#endif // HASH_NODE_H_
