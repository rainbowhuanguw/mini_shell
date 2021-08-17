#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// doubly linked list node
typedef struct node {
  TreeNode* data;
  struct node* next;
  struct node* prev;
} Node;

// Creates a linked list node given a treenode
// INPUT:
//   data - a given tree node
// Returns: a node
Node* CreateNode(TreeNode* data);

// Destroys a node by freeing all the memory allocated to it
// INPUT:
//   node - a node to be destroyed;
void DestroyNode(Node* node);

#endif  // LINKEDLIST_H
