#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef GUESS_H
#define GUESS_H

// Generates a random number within the given range
int GenerateRandom();

// Converts user input string to a valid interger
int ConvertInput(char* input);

// Changes the lower limit of the range
void ChangeLower(int lower);

// Changes the upper limit of the range
void ChangeHigher(int higher);

#endif  // GUESS_H
