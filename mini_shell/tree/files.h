#include "tree.h";
#include "stack.h"

#ifndef FILES_H
#define FILES_H
// Builds a tree by breadth first traverse using a queue
// INPUT:
//  queue - a queue for BFS
void BuildTree(Queue* queue);


// Traverses a tree by depth first search with a stack
// INPUT:
//  root - root node of a tree
//  stack - a stack for DFS
void TraverseTree(Stack* stack, TreeNode* root);

#endif
