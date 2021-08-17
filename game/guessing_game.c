#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "guessing_game.h"

#define MAX 99
#define MIN 1
#define INPUT_LENGTH 4
#define GUESS_TIMES 10

// define some global variables to represent the range
int lower = MIN;
int higher = MAX;

bool isDigit(char c);

bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

int GenerateRandom() {
  srand(time(0));
  return rand() % MAX + MIN;
}

int ConvertInput(char* input) {
  if (input == NULL || strlen(input) > INPUT_LENGTH - 1) return -1;

  // single digit
  if (strlen(input) == 1) {
    if (isDigit(input[0])) return (input[0] - '0');
  } else {
    if (isDigit(input[0]) && isDigit(input[1]))
      return (input[0] - '0') * 10 + (input[1] - '0');
  }

  return -1;  // invalid
}

void ChangeLower(int num) {
  lower = num;
}

void ChangeHigher(int num) {
  higher = num;
}

int main() {
  char* input = (char*) malloc(sizeof(char) * (INPUT_LENGTH));
  int num;
  int target = GenerateRandom();
  int i = GUESS_TIMES;

  printf("--- You have %d times to guess a number between %d and %d.\n ---",
         GUESS_TIMES, MIN, MAX);

  while (i > 0) {
    printf("Please guess a number between %d and %d inclusive\n> ",
           lower, higher);

    fgets(input, INPUT_LENGTH, stdin);

    num = ConvertInput(input);

    if (num == target) {
      printf("Congratulations! The number is %d\n", target);
      break;
    } else if (num < lower || num > higher) {
      printf("Please try another input, your guess is not within range.\n");
      continue;
    } else {
      if (num >= MIN && num < target) {
        ChangeLower(num + 1);
      } else {
        ChangeHigher(num - 1);
      }
      printf("Remaining guesses: %d\n", --i);
    }
  }

  if (i == 0) printf("You failed, the number is %d\n", target);
  free((void*) input);
}
