#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <locale.h>

#include "tree.h"
#include "queue.h"
#include "stack.h"

void PrintFormat(TreeNode* node);

void PrintFormat(TreeNode* node) {
  int i = node->level;
  printf("%lc", 0x251d);
  while (i > 0) {
    printf("%lc%lc", 0x2500, 0x2500);
    i--;
  }
}

void BuildTree(Queue* queue) {
  if (IsEmptyQueue(queue)) return;

  // takes the first node from queue
  TreeNode* parent_node = Dequeue(queue);

  // terminate if dir_node is null
  if (parent_node == NULL) return;

  // the parent node should be a directory with empty name
  int dir_length = strlen(parent_node->path);
  char* dir = (char*) malloc(sizeof(parent_node->path[0]) * (dir_length + 1));

  snprintf(dir, dir_length + 1, "%s", parent_node->path);

  struct stat s;
  struct dirent **namelist;
  int num_files;

  // get number of files in this directory
  num_files = scandir(dir, &namelist, 0, alphasort);

  if (num_files < 0) {
    // error : no such directory
    perror("scandir");
    printf("dir: %s\n", dir);
    return;
  } else {
    // traverse every subdir/file in this directory
    int i = 0;
    while (i < num_files) {
      // Ignore dotfiles, such as .emacs
      if (namelist[i]->d_name[0] == '.') {
        free(namelist[i]);
        i++;
        continue;
      }

      // copy file name
      char* file_name = (char*) malloc(sizeof(char) *
                                       (strlen(namelist[i]->d_name) + 1));
      snprintf(file_name, strlen(namelist[i]->d_name) + 1, "%s",
               namelist[i]->d_name);

      // concat dir and file name
      int length = strlen(dir) + strlen(file_name);
      char* directory = (char*) malloc(((length + 3) * sizeof(char)));
      if (directory == NULL) {
        printf("Couldn't malloc for filecrawler.directory\n");
        return;
      }

      // Copy the path and file name into the "directory" string
      snprintf(directory, length + 3, "%s/%s", dir, file_name);

      // Create TreeNode for every subdir/file
      TreeNode* child_node;

      // Use stat() to get info about the given directory (or file)
      if (0 == stat(directory, &s)) {
        if (S_ISDIR(s.st_mode)) {  // This is a directory
          // Create a treenode for a directory, with empty name
          child_node = AddChild(parent_node, directory, NULL);

          // prints
          // PrintFormat(child_node);
          // printf("Directory: %s\n", directory);

          // put the new TreeNode into the queue for further processing
          Enqueue(queue, child_node);
          BuildTree(queue);
        } else {  // This is a file
          // create a treenode for a file, with valid file name
          child_node = AddChild(parent_node, dir, file_name);

          // prints
          // PrintFormat(child_node);
          // printf("File: %s/%s\n", dir, file_name);
        }
      } else {
        printf("no stat; %s\n", directory);
      }
      free(namelist[i]);
      i++;

      // free
      free(file_name);
      free(directory);
    }
  }

  free(namelist);
  free(dir);
}

void TraverseTree(Stack* stack, TreeNode* root) {
  if (root == NULL) return;

  // preorder traversal
  Push(stack, root);
  TreeNode* curr;
  TreeNode* curr_child;

  while (!IsEmptyStack(stack)) {
    curr = Pop(stack);
    // prints the current node
    PrintFormat(curr);
    PrintTreeNode(curr);

    // push all children to stack
    curr_child = curr->children;

    while (curr_child != NULL) {
      Push(stack, curr_child);
      curr_child = curr_child->siblings;
    }
  }
}

int main(int argc, char* argv[]) {
  // too many or too few arguments
  if (argc < 0 || argc > 2) {
    printf("Please provide only one directory path\n");
    return 1;
  }

  char* dir;

  if (argc == 1) {
    // use default dir, current "."
    const char* curr_dir = ".";
    dir = (char*) curr_dir;
  } else {
    // receives user input
    dir = argv[1];
  }

  setlocale(LC_ALL, "");
  Queue* queue = CreateQueue();

  TreeNode* root = CreateTreeNode((char*) dir, NULL);
  // printf("--- tree building: start--- \n");
  // printf("root directory: %s\n\n", root->path);

  // put first directory to queue
  Enqueue(queue, root);

  // Build tree with queue
  BuildTree(queue);
  // printf("--- tree building: end ---\n\n\n");

  // destroy queue
  DestroyQueue(queue);

  // Traverse tree using stack
  Stack* stack = CreateStack();
  // printf("--- tree traversal : start ---\n");
  TraverseTree(stack, root);
  // printf("--- tree traversal : end ---\n");

  // destroy stack and tree
  DestroyStack(stack);
  DestroyTreeNode(root);
}
