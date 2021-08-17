## 1. Program description and general summary
This program is a random number guessing game. The user is given ten times to
 guess a random number between 1 to 99. The program prints out success or failure
 depending on whether the user can guess the random number correctly within ten trials.

## 2. Compile and run program
- compile : `gcc -g guessing_game.c -o guess` or `make all`
- run :  `./guess` or `make run`

## 3. Files
- guessing_game.c : main program
- guessing_game.h : header for the main program

## 4. Sample output
- If the user fails to guess the correct number,
```
You failed, the number is 31
```
- If the user types in invalid inputs, e.g non-digits or numbers outside of the
defined value range,
```
Please try another input, your guess is not within range.
```
- If the user can guess the number within ten times,
```
Congratulations! The number is 23
```
- sample game simulation:
```
-bash-4.2$ ./guess
--- You have 10 times to guess a number between 1 and 99.
 ---Please guess a number between 1 and 99 inclusive
> 10
Remaining guesses: 9
Please guess a number between 11 and 99 inclusive
> 13
Remaining guesses: 8
Please guess a number between 14 and 99 inclusive
> 15
Remaining guesses: 7
Please guess a number between 16 and 99 inclusive
> 17
Remaining guesses: 6
Please guess a number between 18 and 99 inclusive
> 20
Remaining guesses: 5
Please guess a number between 21 and 99 inclusive
> 24
Remaining guesses: 4
Please guess a number between 21 and 23 inclusive
> 22
Remaining guesses: 3
Please guess a number between 23 and 23 inclusive
> 23
Congratulations! The number is 23
```
