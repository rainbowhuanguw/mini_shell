## 1. program description and general summary
The program builds an N-ary tree from an existing directory with breadth-first
search and traverses this tree with depth-first search. Finally, it displays
the directory tree in a tree structure.

## 2. compile/run commands
- `make all`: to compile the main file
- `make run`: run the main program on the current directory (".")
- `./main <path>`: run the main on a custom path
- `./main`:  run the main on the default path, current ".", same as `make run`

## 3. example input/output
```
┝./
┝──./tree.h
┝──./tree.c
┝──./stack.h
┝──./stack.c
┝──./sample2/
┝────./sample2/s2_1.c
┝──./sample1/
┝────./sample1/s1_2.c
┝────./sample1/s1_1.c
┝──./README.md
┝──./queue.h
┝──./queue.c
┝──./Makefile
┝──./main
┝──./linkedlist.h
┝──./linkedlist.c
┝──./files.h
┝──./files.c
```

## 4. file description
- linkedlist.h & linkedlist.c : provides linked list implementations used
in stack and queue
- stack.h & stack.c : implements stack data structure with doubly linked list
- queue.h & queue.c : implements queue data structure with doubly linked list
- tree.h & tree.c : implements N-ary tree
- files.h & files.c : main program that builds and traverses the tree

## 5. external library usage
- sys/stat.h : to process directories
- locale.h : uses UTF-8 characters in printing the tree
