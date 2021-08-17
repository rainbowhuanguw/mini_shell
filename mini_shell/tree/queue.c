#include "queue.h"
#include "linkedlist.h"

Queue* CreateQueue() {
  Queue* queue = (Queue*) malloc(sizeof(Queue));
  queue->head = NULL;
  queue->tail = NULL;
  queue->size = 0;
}

bool IsEmptyQueue(Queue* queue) {
  return (queue == NULL || (queue->size == 0 && queue->head == NULL));
}
void DestroyQueue(Queue* queue) {
  if (queue == NULL) return;
  Node* curr = queue->head;
  Node* next;

  while (curr != NULL) {
    next = curr->next;
    DestroyNode(curr);  // destroy queue nodes but keeps tree nodes
    curr = next;
  }

  free((void*) queue);
}

void Enqueue(Queue* queue, TreeNode* tree_node) {
  if (queue == NULL || tree_node == NULL) return;

  Node* queue_node = CreateNode(tree_node);

  if (IsEmptyQueue(queue)) {
    // set head and tail if empty
    queue->head = queue_node;
    queue->tail = queue_node;
  } else {
    // set tail
    queue->tail->next = queue_node;
    queue_node->prev = queue->tail;
    queue->tail = queue_node;
  }
  // increment size
  queue->size++;
}

TreeNode* Dequeue(Queue* queue) {
  if (queue == NULL || IsEmptyQueue(queue)) return NULL;

  Node* first = queue->head;
  Node* next = first->next;

  if (queue->size == 1) {
    // reset head and tail if there is one element
    queue->head = NULL;
    queue->tail = NULL;
  } else {
    // reset head
    queue->head = next;
    first->next = NULL;
    next->prev = NULL;
  }
  // decrement size
  queue->size--;

  TreeNode* first_node = first->data;

  // destroys queue node
  DestroyNode(first);

  return first_node;
}
