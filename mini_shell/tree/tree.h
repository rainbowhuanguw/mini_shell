#include <stdio.h>
#include <stdlib.h>

#ifndef TREE_H
#define TREE_H

typedef struct treeNode {
  char* path;
  char* name;
  struct treeNode* children;
  struct treeNode* siblings;
  int level;
} TreeNode;

// Creates a tree node
// INPUT:
//   path - path name
//   name - file name
// Returns: a new treenode
TreeNode* CreateTreeNode(char* path, char* name);

// Adds a child to the current tree node
// INPUT:
//   path - child file path
//   name - child file name
// Returns: the child node being added to tree
TreeNode* AddChild(TreeNode* root, char* path, char* name);

// Frees the memory alloc'd for the given root
// INPUT:
//   root - a given tree node
void DestroyTreeNode(TreeNode* root);

// Prints a tree node
void PrintTreeNode(TreeNode* root);

#endif
