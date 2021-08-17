#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tree.h"
#include "linkedlist.h"

#ifndef QUEUE_H
#define QUEUE_H

// doubly linked list as queue
typedef struct queue {
  int size;
  Node* head;
  Node* tail;
} Queue;

// Creates an empty queue
// returns: an empty queue
Queue* CreateQueue();

// Destroys a queue
// INPUT:
//   queue - the queue to be destroyed
void DestroyQueue(Queue* queue);

// Checks if a queue is empty
// INPUT:
//   queue - a queue to be check
bool IsEmptyQueue(Queue* queue);

// Adds a tree node to the tail of the queue
// INPUT:
//   queue - a queue the node to be inserted to
//   node - a given node to insert to queue
void Enqueue(Queue* queue, TreeNode* node);

// Removes the first element of the queue
// INPUT:
//   queue - a given queue
// Returns: a treeNode
TreeNode* Dequeue(Queue* queue);

#endif  // QUEUE_H
