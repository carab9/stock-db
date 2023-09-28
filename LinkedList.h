// Specification file for the LinkedList class
// It is a single linked list class with a sentinel node

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "ListNode.h"

template<class ItemType>
class LinkedList
{
private:
    ListNode<ItemType> *head;
    int length;

public:
    LinkedList();   // constructor
    ~LinkedList();  // destructor

    // Linked list operations
    int getLength() const {return length;}
    void insertNode(ItemType*);
    bool deleteNode(const ItemType&, ItemType*&);
    bool searchList(const ItemType&, ItemType*&) const;
    void displayList() const;

     // gettter
    const ListNode<ItemType>* getHead() const {return head;}
};

//**************************************************
// Constructor
// This function allocates and initializes a sentinel node
//      A sentinel (or dummy) node is an extra node added before the first data record.
//      This convention simplifies and accelerates some list-manipulation algorithms,
//      by making sure that all links can be safely dereferenced and that every list
//      (even one that contains no data elements) always has a "first" node.
//**************************************************
template<class ItemType>
LinkedList<ItemType>::LinkedList()
{
    head = new ListNode<ItemType>; // head points to the sentinel node
    head->setNext(NULL);
    length = 0;
}

//**************************************************
// Destructor
// This function deletes every node in the list.
//**************************************************
template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
    ListNode<ItemType>* pCur;     // To traverse the list
    ListNode<ItemType>* pNext;    // To hold the address of the next node

    // Position nodePtr: skip the head of the list
    pCur = head->getNext();
    // While pCur is not at the end of the list...
    while (pCur != NULL)
    {
        // Save a pointer to the next node.
        pNext = pCur->getNext();

        // Delete the current node.
        delete pCur;

        // Position pCur at the next node.
        pCur = pNext;
    }

    delete head; // delete the sentinel node
}

//**************************************************
// The insertNode function inserts a new node in a
// sorted linked list
// - input param: the pointer to the data to be inserted
//**************************************************
template<class ItemType>
void LinkedList<ItemType>::insertNode(ItemType* dataIn)
{
    ListNode<ItemType>* newNode;  // A new node
    ListNode<ItemType>* pCur;     // To traverse the list
    ListNode<ItemType>* pPre;     // The previous node

    // Allocate a new node and store num there.
    newNode = new ListNode<ItemType>(dataIn);
 
    // Initialize pointers
    pPre = head;
    pCur = head->getNext();

    // Find location: skip all nodes less than the dataIn
    while (pCur && *(newNode->getItem()) > *(pCur->getItem()))
    {
        pPre = pCur;
        pCur = pCur->getNext();
    }

    // Insert the new node between pPre and pCur
    pPre->setNext(newNode);
    newNode->setNext(pCur);

    // Update the counter
    length++;
}

//**************************************************
// The deleteNode function searches for a node
// in a sorted linked list; if found, the node is
// deleted from the list and from memory, returns true
// and copies the data in that node to the output parameter
// - input param: target data
//**************************************************
template<class ItemType>
bool LinkedList<ItemType>::deleteNode(const ItemType& target, ItemType*& dataOut)
{
    ListNode<ItemType>* pCur;       // To traverse the list
    ListNode<ItemType>* pPre;       // To point to the previous node
    bool deleted = false;

    // Initialize pointers
    pPre = head;
    pCur = head->getNext();

    // Find node containing the target: Skip all nodes less than the target
    while (pCur != NULL && *(pCur->getItem()) < target)
    {
        pPre = pCur;
        pCur = pCur->getNext();
    }

    // If found, delete the node
    if (pCur && *(pCur->getItem()) == target)
    {
        dataOut = pCur->getItem();
        pPre->setNext(pCur->getNext());
        delete pCur;
        deleted = true;
        length--;
    }

    return deleted;
}

//**************************************************
// The searchList function looks for a target item
// in the sorted linked list: if found, returns true
// and copies the data in that node to the output parameter
// - input param: target data
//**************************************************
template<class ItemType>
bool LinkedList<ItemType>::searchList(const ItemType& target, ItemType*& dataOut) const
{
    ListNode<ItemType>* pCur;       // To traverse the list
    ListNode<ItemType>* pPre;       // To point to the previous node
    bool found = false;

    // Initialize pointers
    pPre = head;
    pCur = head->getNext();

    // Find node containing the target: Skip all nodes less than the target
    while (pCur != NULL && *(pCur->getItem()) < target)
    {
        pPre = pCur;
        pCur = pCur->getNext();
    }

    // If found, return the node
    if (pCur && *(pCur->getItem()) == target)
    {
        dataOut = pCur->getItem();
        found = true;
    }

    return found;
}

//**************************************************
// displayList shows the value
// stored in each node of the linked list
// pointed to by head, except the sentinel node
//**************************************************
template<class ItemType>
void LinkedList<ItemType>::displayList() const
{
    ListNode<ItemType>* pCur;  // To move through the list

    // Position pCur: skip the head of the list.
    pCur = head->getNext();

    // While pCur points to a node, traverse the list.
    while (pCur)
    {
        // Display the value in this node using operator<< overloading 
        cout << *(pCur->getItem());

        // Move to the next node.
        pCur = pCur->getNext();
    }
    cout << endl;
}


#endif // LINKED_LIST_H
