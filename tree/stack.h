#include <stdbool.h>
#include "linkedlist.h"
#include "tree.h"

#ifndef STACK_H
#define STACK_H

typedef struct Stack {
  Node* top;
  Node* bottom;
  int size;
} Stack;

// Creates an empty stack
// Returns a stack
Stack* CreateStack();

// Destroys a stack
// INPUT:
//   stack - the stack to be destroyed
void DestroyStack(Stack* stack);

// Checks if the stack is empty
// INPUT:
//   stack - a stack
// Returns true if the stack is empty, false otherwise
bool IsEmptyStack(Stack* stack);

// Removes and returns the element on the top of the stack
// INPUT:
//    stack - a given stack to remove elements from
// Returns the element on the top if the stack is not empty
//    otherwise return NULL
TreeNode* Pop(Stack* stack);

// Returns the element on the top of the stack without removal
// INPUT:
//   stack - a given stack
// Returns the element on the top if the stack is not empty,
//   otherwise return NULL
TreeNode* Peek(Stack* stack);

// Adds a tree_node to the top of the stack
// INPUT:
//   stack - a given stack to be added to
//   tree_node - a tree node to be added to the stack
void Push(Stack* stack, TreeNode* tree_node);

#endif  // STACK_H
