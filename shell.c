#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include "shell.h"

#define MAXARGS 5
#define MAXLINE 81
#define DELIM " "
#define STOP_FLAG 99
#define SUCCESS_FLAG 0
#define FAILURE_FLAG -1

// All the commands supported
char* commands[] = {"cd", "help", "quit", "game", "ls"};
char* built_ins[] = {"cd", "help", "quit"};
char* externals[] = {"game", "ls"};
char* file_paths[] = {"/home/rainbowh/CS5008/rainbowh_CS5008/a10/game/guess",
                      "/home/rainbowh/CS5008/rainbowh_CS5008/a10/tree/tree"};
char* ls_args[] = {"."};

// ----- private methods -----
// Trims a string input, removes leading and trailing spaces,
// and trailing new line symbols
void Trim(char* buffer, char* input);

// Splits a string input by delimeters
void Split(char** buffer, char* input, char* delim);

// Checks if a command is an external command
int IsExternalCommand(char* input);

void Trim(char* buffer, char* input) {
  int length = strlen(input);
  if (length <= 1) return;  // empty

  int left = 0, right = length - 1;
  // skips leading spaces
  while (left <= right && input[left] == ' ') {
    left++;
  }
  // skips trailing spaces and newline
  while (right >= left && (input[right] == ' ' || input[right] == '\n')) {
    right--;
  }

  if (left > right) return;  // empty

  // copy modified input
  snprintf(buffer, right - left + 2, "%s", input + left);
}

void Split(char** buffer, char* input, char* delim) {
  char* ptr = NULL;
  ptr = strtok(input, delim);

  int i = 0;  // buffer index
  while (i < sizeof(buffer) && ptr != NULL) {
    buffer[i++] = ptr;
    ptr = strtok(NULL, delim);
  }
}

int IsExternalCommand(char* input) {
  int i;
  for (i = 0; i < (sizeof(externals) / sizeof(char))
           && externals[i] != NULL; i++) {
    if (strcmp(input, externals[i]) == 0) return SUCCESS_FLAG;
  }
  return FAILURE_FLAG;
}

// Change directory
int cd(char* input) {
  // empty input
  if (input == NULL || strlen(input) == 0) return SUCCESS_FLAG;

  // get the dir before change
  char original[MAXLINE];
  getcwd(original, sizeof(original));
  printf("original working directory: %s\n", original);

  int res = chdir(input);

  if (res < 0) {
    // change directory failed
    printf("no such path exists, change directory failed\n");
    return FAILURE_FLAG;
  } else {
    // change directory succeeded
    char modified[MAXLINE];
    getcwd(modified, sizeof(modified));
    printf("success, current working directory: %s\n", modified);
    return SUCCESS_FLAG;
  }
}

// Prints out help message
int help(char* input) {
  printf("Here are all the commands supported in our k-sea-shell: \n");
  printf("* cd <path> : changes working directory to a given directory.\n");
  printf("* help : prints out all the commands supported in ksea-shell.\n");
  printf("* quit : terminates the ksea-shell and exits\n");
  printf("* game : plays a number guessing game.\n");
  printf("* ls : prints out all the files in the current directory and all the \
 files under the nested directories under this directory.");
  printf("--------\n");

  return SUCCESS_FLAG;
}

// Exits from the current process
int quit(char* input) {
  // sends back signal but do not terminate
  // needs to be freed
  return STOP_FLAG;
}


// Command function pointers here
int (*command_functions[])(char* input) = {cd, help, quit};


// Wrapper of fork(). Checks for fork errors, quits on error.
pid_t Fork(void) {
  pid_t pid;
  if ((pid = fork()) < 0) {
    fprintf(stderr, "%s: %s\n", "fork error", strerror(errno));
    exit(0);
  }
  return pid;
}

// Wrapper of fgets. Checks and quits on Unix error.
char* Fgets(char* ptr, int n, FILE* stream) {
  if (((ptr = fgets(ptr, n, stream)) == NULL) && ferror(stream)) {
    fprintf(stderr, "%s\n", "fgets error");
    exit(0);
  }
  return ptr;
}

// Executes if the given argument is a built-in command
int builtin_command(char** argv) {
  int i;
  int res;

  // Traverse built-in commands, not all commands
  for (i = 0; i < (sizeof(built_ins) / sizeof(built_ins[0]))
           && built_ins[i] != NULL; i++) {
    res = strcmp(built_ins[i], argv[0]);
    if (res == 0) {
      // call the corresponding function
      command_functions[i](argv[1]);

      // if this is the quit command, return stop flag
      if (strcmp("quit", argv[0]) == 0)
        return STOP_FLAG;
      // otherwise return success flag
      return SUCCESS_FLAG;
    }
  }
  return FAILURE_FLAG;  // not a built-in command, execution failed
}

// Creates new processes to execute external supported commands
int external_command(char** argv) {
  int i;
  int res;

  pid_t pid;
  int child_status;

  // Traverse external commands
  for (i = 0; i < (sizeof(externals) / sizeof(char*)) &&
           externals[i] != NULL; i++) {
    res = strcmp(externals[i], argv[0]);

    if (res == 0) {  // found command
      pid = Fork();
      // execute in child
      if (pid == 0) {
        if (strcmp(externals[i], "ls") == 0) {
          // accepts arguments
          res = execve(file_paths[i], ls_args, NULL);
        } else {
          res = execve(file_paths[i], NULL, NULL);
        }
        exit(res);
      } else {
        wait(&child_status);  // wait for child
        return res;
      }
    }
  }

  return FAILURE_FLAG;
}

int eval(char *cmdline) {
  // Argument list execve()
  char** argv = calloc(MAXARGS, sizeof(char*));
  // Holds modified command line
  char* buf = calloc(MAXLINE, sizeof(char));

  // Modifies command line by removing leading, trailing spaces and newline
  // put modified string into buf
  Trim(buf, cmdline);

  // Split buf into args
  Split(argv, buf, DELIM);

  if (argv[0] == NULL) {
    free((void*) buf);
    free((void*) argv);
    return FAILURE_FLAG;  // Ignore empty lines
  }

  int builtin, external;
  builtin = builtin_command(argv);

  if (builtin == FAILURE_FLAG) {  // built-in commands will be run here
    // Check that the command/program exists in Unix (ie /bin/) OR (see below)
    // Create a child process

    external = external_command(argv);
    // error message, not a supported command
    if (external == FAILURE_FLAG) {
      printf("Command not found -- Did you mean something else? \n");
      return FAILURE_FLAG;
    }
  }

  // free
  free((void*) buf);
  free((void*) argv);

  if (builtin == STOP_FLAG) return STOP_FLAG;
  return SUCCESS_FLAG;
}

int main() {
  char* cmdline = calloc(MAXLINE, sizeof(char));  // command line buffer
  int status = 0;  // marks the appearance of quit()

  while (1 && status != STOP_FLAG) {
    // Print command prompt
    printf("k-sea-shell > ");
    // Read input from user
    Fgets(cmdline, MAXLINE, stdin);
    // If we get the eof, quit the program/shell
    if (feof(stdin))
      status = STOP_FLAG;

    // Otherwise, evaluate the input and execute.
    status = eval(cmdline);
  }

  // free
  free((void*) cmdline);
  exit(0);
}
