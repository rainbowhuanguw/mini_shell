#include <string.h>

#include "tree.h"

// private function declaration
void SetTreeNodeLevel(TreeNode* node, int level);

TreeNode* CreateTreeNode(char* path, char* name) {
  TreeNode* tree_node = (TreeNode*) malloc(sizeof(TreeNode));

  if (path != NULL) {
    tree_node->path = (char*) malloc(sizeof(path[0]) * (strlen(path) + 1));
    snprintf(tree_node->path, strlen(path) + 1, "%s", path);
  } else {
    tree_node->path = NULL;
  }

  // name can sometimees be NULL
  if (name != NULL) {
    tree_node->name = (char*) malloc(sizeof(name[0]) * (strlen(name) + 1));
    snprintf(tree_node->name, strlen(name) + 1, "%s", name);
  } else {
    tree_node->name = NULL;
  }

  tree_node->children = NULL;
  tree_node->siblings = NULL;
  tree_node->level = 0;

  return tree_node;
}

void SetTreeNodeLevel(TreeNode* node, int level) {
  node->level = level;
}

TreeNode* AddChild(TreeNode* root, char* path, char* name) {
  if (root == NULL) return NULL;

  int parent_level = root->level;
  TreeNode* child = CreateTreeNode(path, name);

  TreeNode* curr_child = root->children;

  if (curr_child == NULL) {
    // first child of this node
    root->children = child;
  } else {
    // has existing children
    while (curr_child != NULL && curr_child->siblings != NULL) {
      curr_child = curr_child->siblings;
    }
    curr_child->siblings = child;
  }

  // sets child level
  SetTreeNodeLevel(child, parent_level + 1);

  return child;
}

void DestroyTreeNode(TreeNode* root) {
  // base case1: terminate when the current node is null
  if (root == NULL) return;

  // free children and siblings recursively
  DestroyTreeNode(root->children);
  DestroyTreeNode(root->siblings);

  // base case2: free current node when it has no children or siblings
  if (root->path != NULL) {
    free((void*) root->path);
  }
  if (root->name != NULL) {
    free((void*) root->name);
  }
  free((void*) root);
}

void PrintTreeNode(TreeNode* root) {
  if (root == NULL) {
    printf("Null");
  } else {
    printf("%s/", root->path);
    if (root->name != NULL)
      printf("%s", root->name);
  }
  printf("\n");
}
