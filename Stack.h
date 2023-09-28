// Specification file for the Stack class

#ifndef STACK_H_
#define STACK_H_

#include <iostream>
using namespace std;

template <class ItemType>
class Stack
{
private:
    // Structure for the stack nodes
    struct StackNode
    {
      ItemType* value;   // Value in the node
      StackNode *next;  // Pointer to next node
    };

    StackNode *top;     // Pointer to the stack top
    int length;

public:
    // Constructor
    Stack() { top = NULL; length = 0; }

    // Destructor
    ~Stack();

    // Stack operations:
    bool push(ItemType*);
    ItemType* pop();
    ItemType* peek()
    {
        return top->value;
    }
    bool isEmpty()
    {
        return (length == 0);
    }
    int getLength()
    {
       return length;
    }
};

//**************************************************
// inserts the argument onto the stack
//**************************************************
template <class ItemType>
bool Stack<ItemType>::push(ItemType* item)
{
    StackNode* newNode; // Pointer to a new node

    // Allocate a new node and store num there.
    newNode = new StackNode;
    if (!newNode)
        return false;
    newNode->value = item;

    // Update links and counter
    newNode->next = top;
    top = newNode;
    length++;

    return true;
}

//**************************************************
// deletes the value at the top of the stack and
// returns it. Assume stack is not empty
//**************************************************
template <class ItemType>
ItemType* Stack<ItemType>::pop()
{
    StackNode* currNode = top;
    ItemType* item = currNode->value;
    // Update the top of the stack to next node
    top = currNode->next;
    length--;
    delete currNode;
    return item;
}

//**************************************************
// Destructor
//**************************************************
template <class ItemType>
Stack<ItemType>::~Stack()
{
    StackNode* currNode;

    // Position nodePtr at the top of the stack.
    currNode = top;

    // Traverse the list deleting each node.
    while (currNode)
    {
        top = currNode->next;
        delete currNode;
        currNode = top;
    }
}

#endif
