// Specification file for the ListNode class
// It is the list node class used by LinkedList class
// Each list node stores a pointer to the item object 
// instead of the whole item object

#ifndef LISTNODE_H_
#define LISTNODE_H_

template<class ItemType>
class ListNode
{
private:
    ItemType* item;    // store data (a pointer to data object)
    ListNode* next;    // a pointer to the next node in the list

public:
    // constructor
    ListNode() {item = NULL; next = NULL;}
    ListNode(ItemType* dataIn, ListNode* nt = NULL) {item = dataIn; next = nt;}
    
    // setters
    // set the forw pointer
    void setNext(ListNode* nextPtr) { next = nextPtr; }

    // getters
    // return pointer in the next node
    ListNode* getNext() const {return next;}
    // return data object in the listnode
    ItemType* getItem() const {return item;}
};


#endif // LISTNODE_H_
