#include <stdio.h>
#include <stdlib.h>

#ifndef SHELL_H
#define SHELL_H

// Changes directory
int cd(char* input);

// Prints out help information
int help(char* input);

// Exits
int quit(char* input);

// Wrapper of fgets
char* Fgets(char* ptr, int n, FILE* stream);

// Checks and executes a built-in command
// INPUT:
//   argv - an array of arguments
// Returns : 0 if succeeded, -1 if execution failed
int builtin_command(char** argv);

// Evaluate user input
// Returns : -1 failed, 0 success, 1 need to terminate
int eval(char* cmdline);

#endif  // SHELL_H
