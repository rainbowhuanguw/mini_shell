#include "stack.h"

Stack* CreateStack() {
  Stack* stack = (Stack*) malloc(sizeof(Stack));
  stack->top = NULL;
  stack->bottom = NULL;
  stack->size = 0;
}

void DestroyStack(Stack* stack) {
  if (stack == NULL) return;
  Node* curr = stack->top;
  Node* next;
  while (curr != NULL) {
    next = curr->next;
    DestroyNode(curr);
    curr = next;
  }
  free((void*) stack);
}

bool IsEmptyStack(Stack* stack) {
  return stack == NULL || (stack->size == 0 && stack->top == NULL);
}

TreeNode* Pop(Stack* stack) {
  if (stack == NULL || IsEmptyStack(stack)) return NULL;

  Node* top = stack->top;

  if (stack->size == 1) {
    // reset top and bottom
    stack->top = NULL;
    stack->bottom = NULL;
  } else {
    // reset top
    stack->top = stack->top->prev;
    stack->top->next = NULL;
  }
  // decrement size
  stack->size--;

  // Destroy stack node
  TreeNode* tree_node = top->data;
  DestroyNode(top);
  return tree_node;
}

TreeNode* Peek(Stack* stack) {
  if (stack == NULL || IsEmptyStack(stack)) return NULL;

  Node* top = stack->top;
  return top->data;
}

void Push(Stack* stack, TreeNode* tree_node) {
  if (stack == NULL || tree_node == NULL) return;

  Node* node = CreateNode(tree_node);
  if (IsEmptyStack(stack)) {
    // set top and bottom
    stack->top = node;
    stack->bottom = node;
  } else {
    // set top
    stack->top->next = node;
    node->prev = stack->top;
    stack->top = node;
  }
  // increment size
  stack->size++;
}
