// Specification file for the BinarySearchTree class
// It is derived from the abstract base class, BinaryTree class
// It use a special comparison function to order the binary nodes in BST
// BinarySearchTree stores a function pointer of the comparison
// function when the constructor is called
// BinarySearchTree only stores the pointers to the data object
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

// Forward declaration
template<class ItemType>
class LinkedList;

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
    // function pointer
    // compare two ItemType object function pointer
    int (*comp)(const ItemType& b1, const ItemType& b2);

public:
    // constructor
    // the constructor takes a function pointer which is used 
    // in comparision of two objects for BST ordering
    BinarySearchTree(int c(const ItemType& b1, const ItemType& b2)) : BinaryTree<ItemType>() {comp = c;}

    // insert a node at the correct location
    bool insert(ItemType* dataIn);

    // find a target node
    bool search(const ItemType& target, ItemType*& dataOut) const;

    // find a list of nodes that matched target node
    bool search(const ItemType& target, LinkedList<ItemType>& dataList);

    // remove a node if found
    bool remove(const ItemType& target, ItemType*& dataOut);

private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
   
    // search for target node in treePtr subtree
    BinaryNode<ItemType>* _search(BinaryNode<ItemType>* treePtr, const ItemType& target) const; 

    // search for a list of nodes that matched target node in treePtr subtree
    void _search(BinaryNode<ItemType>* treePtr, const ItemType& target,
                 LinkedList<ItemType>& dataList) const;

    // internal remove node: locate and delete target node in nodePtr subtree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType& target,
                                  BinaryNode<ItemType>*& targetNodePtr);

    // remove the target node from tree, called by internal remove node
    BinaryNode<ItemType>* _removeNode(BinaryNode<ItemType>* nodePtr);

    // remove the leftmost node in the subtree of nodePtr (smallest)
    BinaryNode<ItemType>* _removeLeftmostNode(BinaryNode<ItemType>* nodePtr);

    // remove the rightmost node in the subtree of nodePtr (largest)
    BinaryNode<ItemType>* _removeRightmostNode(BinaryNode<ItemType>* nodePtr);
};

//**************************************************
// Insert a node at the correct location
// - input param: the pointer to the data to be inserted
// - return true 
//**************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(ItemType* dataIn)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(dataIn);
    this->rootPtr = _insert(this->rootPtr, newNodePtr);
    return true;
}

//**************************************************
// Find a target node
// - it calls the private _search function that returns a node pointer or NULL
// - if found, it copies data from that node and sends it back to the caller 
//   via the output parameter, and returns true, otherwise it returns false.
//**************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::search(const ItemType& target, ItemType*& dataOut) const
{
    BinaryNode<ItemType>* targetNodePtr = _search(this->rootPtr, target);
    if (targetNodePtr) {
        dataOut = targetNodePtr->getItem();
        return true;
    }
    else {
        return false;
    }
}

//**************************************************
// Find a list of nodes that matched target node
// - input param: target data
// - return true if found, otherwise, false
//   return a list of nodes that matched the target
//   in the output parameter
//**************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::search(const ItemType& target, LinkedList<ItemType>& dataList)
{
    _search(this->rootPtr, target, dataList);
    if (dataList.getLength()) {
        return true;
    }
    else {
        return false;
    }
}

//**************************************************
// Remove a node if found
// - input param: target data
// - return true if found, otherwise false
//   return the data found via output parameter
//**************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& target, ItemType*& dataOut)
{
    BinaryNode<ItemType>* targetNodePtr = nullptr;
    this->rootPtr = _remove(this->rootPtr, target, targetNodePtr);
    if (targetNodePtr) {
        dataOut = targetNodePtr->getItem();
        // delete the actual memory of the node
        delete targetNodePtr;
        return true;
    }
    else {
        return false;
    }
}

//**************************************************
// Implementation of the insert operation : resursive
// Insert newNode in nodePtr subtree
// - input params: pointer to the node of the substree to insert
//                 pointer to the node to be inserted
// - return the node of the substree to insert
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
    if (!nodePtr) // == NULL
    {
        nodePtr = newNodePtr;
        return nodePtr;
    }
       
    //if (*nodePtr->getItem() > *newNodePtr->getItem()) {
    if (comp(*nodePtr->getItem(), *newNodePtr->getItem()) > 0) {
        nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
    }
    else {
        nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
    }

    return nodePtr;
}

//**************************************************
// Implementation of the search operation: recursive
// - input params: pointer to the node of the substree to search
//                 target data
// - return NULL if target not found, otherwise
// - return a pointer to the node that matched the target
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_search(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType& target) const
{
    if (!nodePtr) // == NULL
    {
        return nullptr;
    }
        
    ItemType* item = nodePtr->getItem();
    BinaryNode<ItemType>* found = nullptr;

    //if (*item == target) {
    if (comp(*item, target) == 0) {
        // target node found
        found = nodePtr;
    }
    else {
        //if (*item > target) {
        if (comp(*item, target) > 0) {
            found = _search(nodePtr->getLeftPtr(), target);
        }
        else {
            found = _search(nodePtr->getRightPtr(), target);
        }
    }

    return found;
}

//**************************************************
// Implementation of the search operation: recursive
// - input params: pointer to the node of the substree to search
//                 target data
// - return a list of nodes that matched the target
//   in the output parameter
//**************************************************
template<class ItemType>
void BinarySearchTree<ItemType>::_search(BinaryNode<ItemType>* nodePtr, const ItemType& target,
                                         LinkedList<ItemType>& dataList) const
{
    if (!nodePtr) // == NULL
    {
        return;
    }

    ItemType* item = nodePtr->getItem();
    BinaryNode<ItemType>* found = nullptr;

    //if (*item > target) {
    if (comp(*item, target) > 0) {
        _search(nodePtr->getLeftPtr(), target, dataList);
    }
    else {
        //if (*item == target) {
        if (comp(*item, target) == 0) {
            // target node found
            dataList.insertNode(item);
        }
        // continue on to the right subtree
        _search(nodePtr->getRightPtr(), target, dataList);
    }
}

//**************************************************
// Implementation of the delete operation : resursive
// - input params: pointer to the node of the substree to 
//                 search for removing target node
// - return the replacing node pointer if the root of the
//          substree to search and remove machtes the target, 
//          otherwise, the pointer to the node of the substree
//          to search for removing target node
//   return a pointer to the node that matched the target
//          to remove via output parameter
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType& target,
                                                          BinaryNode<ItemType>*& targetNodePtr)
{
    if (!nodePtr) // == NULL
    {
        return nullptr;
    }

    ItemType* item = nodePtr->getItem();

    if (*item == target) {
       // target node found
        targetNodePtr = nodePtr;

        // remove the target node from the substree
        BinaryNode<ItemType>* replacingNodePtr = _removeNode(nodePtr);

        // return the replacing node pointer to the caller
        return replacingNodePtr;
    }
    else {
        //if (*item > target) {
        if (comp(*item, target) > 0) {
            nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, targetNodePtr));
        }
        else {
            nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, targetNodePtr));
        }
    }

    return nodePtr;
}

//**************************************************
// Remove a target node from the subtree
// This function doest not delete the actual memory of the node
// It just removes the node from the subtree
// - input param: the pointer to the node to remove from the subtree
// - return the pointer of the replacing node
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_removeNode(BinaryNode<ItemType>* nodePtr)
{   
   if (nodePtr->isLeaf()) {  // has no children, a leaf node
        return nullptr;
    }
    else if (nodePtr->getLeftPtr() && !nodePtr->getRightPtr()) {  // has left child only
        // find the largest child in the left substree of nodePtr
        BinaryNode<ItemType>* rightmost = _removeRightmostNode(nodePtr->getLeftPtr());
        // connect the rightmost node with the sub-trees of the targest node
        if (nodePtr->getLeftPtr() != rightmost) {
             rightmost->setLeftPtr(nodePtr->getLeftPtr());
        }
        rightmost->setRightPtr(nodePtr->getRightPtr());
        return rightmost;
    }
    else if (nodePtr->getRightPtr()) {  // has right child only or two children
        // find the smallest child in the right substree of nodePtr
        BinaryNode<ItemType>* leftmost = _removeLeftmostNode(nodePtr->getRightPtr());
        // connect the leftmost node with the sub-trees of the targest node
        if (nodePtr->getRightPtr() != leftmost) {
            leftmost->setRightPtr(nodePtr->getRightPtr());
        }
        leftmost->setLeftPtr(nodePtr->getLeftPtr());
        return leftmost;
    }

    return nullptr;
}

//**************************************************
// remove the leftmost node in the subtree of nodePtr (smallest)
// It just removes the node from the subtree
// - input param: the pointer to the node of the substree to remove
// - return the leftmost node to replace the node to remove
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_removeLeftmostNode(BinaryNode<ItemType>* nodePtr)
{
    if (!nodePtr) {
        return nullptr;
    }

    if (nodePtr->getLeftPtr() == nullptr) {
        // current node does not have a left child, it is the leftmost node
        return nodePtr;
    }
    
    BinaryNode<ItemType>* leftmost = _removeLeftmostNode(nodePtr->getLeftPtr());

    // set the left child of the parent node of the leftmost node 
    // to the right child of the leftmost node
    if (nodePtr->getLeftPtr() == leftmost) {
        nodePtr->setLeftPtr(leftmost->getRightPtr());
    }

    return leftmost;
}

//**************************************************
// remove the rightmost node in the subtree of nodePtr (largest)
// It just removes the node from the subtree
// - input param: the pointer to the node of the substree to remove
// - return the rightmost node
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_removeRightmostNode(BinaryNode<ItemType>* nodePtr)
{
    if (!nodePtr) {
        return nullptr;
    }

    if (nodePtr->getRightPtr() == nullptr) {
        // current node does not have a right child, it is the rightmost node
        return nodePtr;
    }

    BinaryNode<ItemType>* rightmost = _removeRightmostNode(nodePtr->getRightPtr());

    // set the right child of the parent node of the rightmost node
    // to the left child of the rightmost node
    if (nodePtr->getRightPtr() == rightmost) {
        nodePtr->setRightPtr(rightmost->getLeftPtr());
    }

    return rightmost;
}

#endif
