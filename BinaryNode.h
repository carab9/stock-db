// Specification file for the BinaryNode class
// It is the binary node class used by BinaryTree class 
// Each binary node stores a pointer to the item object
// instead of the whole item object

#ifndef BINARY_NODE_H_
#define BINARY_NODE_H_

template<class ItemType>
class BinaryNode
{
private:
    ItemType*       item;                 // Data portion (a pointer to data object)
    BinaryNode<ItemType>* leftPtr;        // Pointer to left child
    BinaryNode<ItemType>* rightPtr;       // Pointer to right child

public:
    // constructors
    BinaryNode(ItemType* anItem) {item = anItem; leftPtr = 0; rightPtr = 0;}
    BinaryNode(ItemType* anItem,
               BinaryNode<ItemType>* left,
               BinaryNode<ItemType>* right) {item = anItem; leftPtr = left; rightPtr = right;}
    
    // setters
    void setItem(ItemType* anItem) {item = anItem;}
    void setLeftPtr(BinaryNode<ItemType>* left) {leftPtr = left;}
    void setRightPtr(BinaryNode<ItemType>* right) {rightPtr = right;}
    
    // getters
    ItemType* getItem() const {return item;}
    BinaryNode<ItemType>* getLeftPtr() const {return leftPtr;}
    BinaryNode<ItemType>* getRightPtr() const {return rightPtr;}

    // other functions
    bool isLeaf() const {return (leftPtr == 0 && rightPtr == 0);}
};

#endif // BINARY_NODE_H_
