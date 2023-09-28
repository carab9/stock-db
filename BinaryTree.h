// Specification file for the BinaryTree class
// It is the abstract base class for BinarySearchTree class
 
#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include "BinaryNode.h"

template<class ItemType>
class BinaryTree
{
protected:
    BinaryNode<ItemType>* rootPtr; // pointer to root node
    int count;                     // number of nodes in tree

public:
    // constructors and destructor
    BinaryTree() {rootPtr = 0; count = 0;}
    virtual ~BinaryTree() {destroyTree(rootPtr);}
   
    // common functions for all binary trees
    bool isEmpty() const {return count == 0;}
    int getCount() const {return count;}
    void clear() {destroyTree(rootPtr); rootPtr = 0; count = 0;}
    void preOrder(void visit(ItemType&)) const {_preorder(visit, rootPtr);}
    void inOrder(void visit(ItemType&)) const {_inorder(visit, rootPtr);}
    void postOrder(void visit(ItemType&)) const {_postorder(visit, rootPtr);}
    void printTree(void visit(ItemType&, int)) const {_printTree(visit, rootPtr, 1);}
    void printLeaf(void visit(ItemType&)) const {_printLeaf(visit, rootPtr);}

    // abstract functions to be implemented by derived class
    virtual bool insert(ItemType*) = 0;
    virtual bool remove(const ItemType &, ItemType*&) = 0;
    virtual bool search(const ItemType &, ItemType*&) const = 0;

private:   
    // delete all nodes from the tree
    void destroyTree(BinaryNode<ItemType>* nodePtr);

    // internal traverse
    void _preorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const;
    void _inorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const;
    void _postorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const;
    void _printTree(void visit(ItemType&, int), BinaryNode<ItemType>* nodePtr, int level) const;
    void _printLeaf(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const;
}; 

//**************************************************
// Destroy the entire tree
// - input param: the pointer to the node of the subtree to destroy
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr) // != NULL
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        //cout << "DEBUG - Destructor: Now deleting " << nodePtr->getItem().getName() << endl;
        delete nodePtr;
    }
}  

//**************************************************
// Preorder Traversal
// - input param: function pointer to process item when visited, and
//                the pointer to the node of the subtree to process
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr) // != NULL
    {
        ItemType* item = nodePtr->getItem();
        visit(*item);
        _preorder(visit, nodePtr->getLeftPtr());
        _preorder(visit, nodePtr->getRightPtr());
    }
}

//**************************************************
// Inorder Traversal
// - input param: function pointer to process item when visited, and
//                the pointer to the node of the subtree to process
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr) // != NULL
    {
        ItemType* item = nodePtr->getItem();
        _inorder(visit, nodePtr->getLeftPtr());
        visit(*item);
        _inorder(visit, nodePtr->getRightPtr());
    }
}  

//**************************************************
// Postorder Traversal
// - input param: function pointer to process item when visited, and
//                the pointer to the node of the subtree to process
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const
{
     if (nodePtr) // != NULL
    {
        ItemType* item = nodePtr->getItem();
        _postorder(visit, nodePtr->getLeftPtr());
        _postorder(visit, nodePtr->getRightPtr());
        visit(*item);
    }
}  

//**************************************************
// Prints tree as an indented list
// - input param: function pointer to print item when visited, 
//                the pointer to the node of the subtree to print
//                the current level of the tree for visit function
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::_printTree(void visit(ItemType&, int), BinaryNode<ItemType>* nodePtr, int level) const
{
    if (nodePtr) // != NULL
    {
        ItemType* item = nodePtr->getItem();
        visit(*item, level);
        _printTree(visit, nodePtr->getRightPtr(), level + 1);
        _printTree(visit, nodePtr->getLeftPtr(), level + 1);
    }
}

//**************************************************
// Prints leaf nodes of the tree
// - input param: function pointer to print item when visited, and
//                the pointer to the node of the subtree to print
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::_printLeaf(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr) // != NULL
    {
        if (nodePtr->isLeaf()) {
            ItemType* item = nodePtr->getItem();
            visit(*item);
        }
        else {
            _printLeaf(visit, nodePtr->getRightPtr());
            _printLeaf(visit, nodePtr->getLeftPtr());
        }
    }
}

#endif // BINARY_TREE_H_
