## 1. program description and general summary
This program mimics the operation system interface, Shell. It supports the
following behaviors,
- cd : changes current working directory
- ls : prints out all the subdirectories and files under the current working
directory
- help : prints out all the information about supported commands
- quit : quits the mini shell program
- game : plays a random number guessing game


## 2. Command Name, usage, and sample output
- `cd` : change current working directory to a given directory
-- Usage: `cd <path>`
-- Sample output:
```
k-sea-shell > cd ../lab10
original working directory: /home/rainbowh/CS5008/rainbowh_CS5008/a10
success, current working directory: /home/rainbowh/CS5008/rainbowh_CS5008/lab10

k-sea-shell > cd ../lab20
original working directory: /home/rainbowh/CS5008/rainbowh_CS5008/lab10
no such path exists, change directory failed

k-sea-shell > cd .
original working directory: /home/rainbowh/CS5008/rainbowh_CS5008/lab10
success, current working directory: /home/rainbowh/CS5008/rainbowh_CS5008/lab10
```

- `quit` : terminates and exits the k-sea shell.
-- Usage: `quit`
-- Sample output:
`k-sea-shell > quit`

- `game` : plays a random number guessing game
-- Usage : `game`
-- Sample output :
```
k-sea-shell > game
--- You will have 10 times to guess a number between 1 and 99.  Good luck---
Please guess a number between 1 and 99 inclusive
> 10
Remaining guesses: 9
Please guess a number between 11 and 99 inclusive
> 80
Remaining guesses: 8
Please guess a number between 11 and 79 inclusive
> 50
Remaining guesses: 7
Please guess a number between 11 and 49 inclusive
> 35
Remaining guesses: 6
Please guess a number between 11 and 34 inclusive
> 25
Remaining guesses: 5
Please guess a number between 11 and 24 inclusive
> 18
Remaining guesses: 4
Please guess a number between 11 and 17 inclusive
> 14
Congratulations! The number is 14
```

- `help` : displays information of all the supported commands
-- Usage : `help`
-- Sample output:
```
k-sea-shell > help
Here are all the commands supported in our k-sea-shell:
* cd <path> : changes working directory to a given directory.
* help : prints out all the commands supported in ksea-shell.
* quit : terminates the ksea-shell and exits.
* game : plays a number guessing game.
* ls : displays all the files and subdirectories under the current working
directory.
--------
```

- `ls` : displays all the files and subdirectories under the current working
directory
-- Usage : `ls`
-- Sample output:
```
k-sea-shell > ls
./
./tree.h
./tree.c
./stack.h
./stack.c
./sample2/
./sample2/s2_1.c
./sample1/
./sample1/s1_2.c
./sample1/s1_1.c
./queue.h
./queue.c
./linkedlist.h
./linkedlist.c
./files.h
./files.c
./README.md
./Makefile
```

## 3. Files and subdirectories
- shell.c : the main program
- shell.h : header file for shell.c
- /game : subdirectory to store the related files for  `game` function
- /tree : subdirectory to store the related files for `ls` function

## 4. Compile and run mini-shell:
- before compiling shell : compile the game and tree subprograms, please see
the readme file under the /game and /tree subdirectories.
- compile shell : `gcc shell.c -g -o shell` or `make all`.
- run shell : `./shell` or `make run`.
