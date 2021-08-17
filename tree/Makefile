all: main

main: linkedlist.h tree.h queue.h stack.h files.h linkedlist.c tree.c queue.c \
 stack.c files.c
	 gcc -g linkedlist.c tree.c queue.c stack.c files.c -o tree

run: main
	./tree .

clean:
	rm -rf *~ tree
