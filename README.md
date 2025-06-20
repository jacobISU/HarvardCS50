# HarvardCS50

These are all the projects I completed during my time in the course CS50.
All programs have been refactored so they can be ran without the CS50 library.

## Problem Set 0
**ProblemSet0_Scratch.sb3**
  - A small game that can be ran in the Scratch program from MIT.
  - Used to explain the logic of programming in a visual way.
## Problem Set 1

**hello.c**
  - Super simple program that takes in the user's name and says hello to the name input.
  - Used to show how to get user input.
    
**mario.c**
  - Takes a user input from 1 to 8 and then "draws" a mario block pyramid of the user input height in the terminal.
  - Used to learn how to use for and while loops.
    
**credit.c**
  - Takes a user's credit card number as input.
  - Uses Luhn's Algorithm to determine if it is a valid credit card number.
  - If the credit card is valid, determines what kind it is. (e.g. VISA, MASTERCARD)
  - Used to better understand different types such as the difference in int and long.
  - Also a good start to understanding resusable code.

## Problem Set 2

**scrabble.c**
  - Takes in a word for a "Player 1" and "Player 2".
  - Uses scrabble rules to assign individual alphabetic characters values. Whichever player enters the most valuable word wins.
  - Used to learn how to manipulate and use individual characters.

**readability.c**
  - Takes in user input. Specifically text from a book. (e.g. "One fish. Two fish. Red fish. Blue fish.")
  - Uses Coleman-Liau Index to evaluate the text by letters, words, and sentences to determine the text's intended grade level.
  - Used to learn string manipulation.

**substitution.c**
  - Takes in a 26 character, alphabetic, non-repeating characters input as a cipher key. (e.g. "NQXPOMAFTRHLZGECYJIUWSKDVB")
  - Takes in user text and outputs the encrypted text. 
  - Key is used as a new 26 character alphabet. 
  - Finds each character's real alphabetic index, then replaces the text's character with the character from the key. 
    (e.g. 'H' has an index 8 in the alphabet. Index 8 from the key is 'F'. Replace 'H' with 'F')
  - Result will be a fully encrypted text (e.g. "plaintext: Hello" becomes "ciphertext: Folle)
  - This assignment teaches user input from the command line, array manipulation, and more character manipulation.

## Problem Set 3

**TO/DO**
