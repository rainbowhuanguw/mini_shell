#include "linkedlist.h"

Node* CreateNode(TreeNode* data) {
  Node* node = (Node*) malloc(sizeof(Node));
  node->data = data;
  node->prev = NULL;
  node->next = NULL;
}

void DestroyNode(Node* node) {
  // frees the Node, not the data it contains
  if (node == NULL) return;
  free((void*) node);
}
