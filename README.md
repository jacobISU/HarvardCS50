# HarvardCS50

These are all the projects I completed during my time in the course CS50.  
All programs have been refactored so they can be ran without the CS50 library.  

## Problem Set 0
**ProblemSet0_Scratch.sb3**
  - A small game that can be ran in the Scratch program from MIT.
  - Used to explain the logic of programming in a visual way.
## Problem Set 1

**me**
**Folder Contents: hello.c**  
**To build with VSCode, Powershell, and gcc: gcc hello.c -o hello**  
**To run: "./hello"**
  - Super simple program that takes in the user's name and says hello to the name input.
  - Used to show how to get user input.
    
**mario**  
**Folder Contents: mario.c**  
**To build with VSCode, Powershell, and gcc: gcc mario.c -o mario**  
**To run: "./mario"**
  - Takes a user input from 1 to 8 and then "draws" a mario block pyramid of the user input height in the terminal.
  - Used to learn how to use for and while loops.
    
**credit**  
**Folder Contents: credit.c**  
**To build with VSCode, Powershell, and gcc: gcc credit.c -o credit**  
**To run: "./credit"**
  - Takes a user's credit card number as input.
  - Uses Luhn's Algorithm to determine if it is a valid credit card number.
  - If the credit card is valid, determines what kind it is. (e.g. VISA, MASTERCARD)
  - Used to better understand different types such as the difference in int and long.
  - Also a good start to understanding resusable code.

## Problem Set 2

**scrabble**  
**Folder Contents: scrabble.c**  
**To build with VSCode, Powershell, and gcc: gcc scrabble.c -o scrabble**  
**To run: "./scrabble"**
  - Takes in a word for a "Player 1" and "Player 2".
  - Uses scrabble rules to assign individual alphabetic characters values. Whichever player enters the most valuable word wins.
  - Used to learn how to manipulate and use individual characters.

**readability**  
**Folder Contents: readability.c**  
**To build with VSCode, Powershell, and gcc: gcc readability.c -o readability**  
**To run: "./readability"**
  - Takes in user input. Specifically text from a book. (e.g. "One fish. Two fish. Red fish. Blue fish.")
  - Uses Coleman-Liau Index to evaluate the text by letters, words, and sentences to determine the text's intended grade level.
  - Used to learn string manipulation.

**substitution**  
**Folder Contents: substitution.c**  
**To build with VSCode, Powershell, and gcc: gcc substitution.c -o substitution**  
  - Takes in a 26 character, alphabetic, non-repeating characters input as a cipher key. (e.g. "./substitution NQXPOMAFTRHLZGECYJIUWSKDVB")
  - Takes in user text and outputs the encrypted text. 
  - Key is used as a new 26 character alphabet. 
  - Finds each character's real alphabetic index, then replaces the text's character with the character from the key. 
    (e.g. 'H' has an index 8 in the alphabet. Index 8 from the key is 'F'. Replace 'H' with 'F')
  - Result will be a fully encrypted text (e.g. "plaintext: Hello" becomes "ciphertext: Folle)
  - This assignment teaches user input from the command line, array manipulation, and more character manipulation.

## Problem Set 3
**sort.txt**
  - No file included because of the nature of this assignment.
  - Read text file for more information.
  - This assignment was used to teach the time complexities of different sorting algorithms and how long they take based on best or worst case scenarios. 

**plurality**  
**Folder Contents: plurality.c**  
**To build with VSCode, Powershell, and gcc: gcc plurality.c -o plurality**
  - This is a program that takes in a maximum of 9 candidates, the user then can vote for the candidates, and produce a winner(s).
  - In the command line, run the program with 1 to 9 candidate names. (e.g. "./plurality Alice Bob Dan)
  - Then enter the amount of voters you want voting for the candidates. These voters will be prompted for a name of a candidate they want to vote for.
  - The winner(s) are printed out in the ended.
  - The assignment teaches how structs are used and how the new type's data is manipulated.
  - Also this is an excercise to use a sorting algorithm to help print the appropriate winners.

  **tideman**  
  **Folder Contents: tideman.c**  
  **To build with VSCode, Powershell, and gcc: gcc tideman.c -o tideman**
  - This program implements the Tideman (Ranked Pairs) voting system.
  - In command line, run the program with up to 1 to 9 candidates. (e.g. "./tideman Alice Bob Charlie")
  - Then enter the amount of voters that are going to vote. (e.g. "Number of voters: 3")
  - Then as the voter, vote for your candidates by rank. (e.g. "Rank 1: Alice, Rank 2: Bob, Rank 3: Charlie")
  - Accepts ranked votes to determine a winner by sorting pairs of candidates by "strength of victory".
  - A pair is locked into a directed graph if the pair(edge) does not create a cycle in the graph.
  - This assignment teaches 2D arrays, graph theory and cycle detection, More sorting algorithms.
  - Difficult.

  ## Problem Set 4

  **volume**  
  **Folder Contents: input.wav, output.wav, volume.c**  
  **To build with VSCode, Powershell, and gcc: gcc volume.c -o volume**
  - This program manipulates a .WAV file.
  - Reads in and copies the .WAV header file and writes it to a new output file. (e.g. "./volume input.wav output.wav 0.2")
  - Reads in samples of the .WAV file, manipulates the sample (e.g. "0.2 for quieter"), then writes the manipulated samples to the same new output file.
  - This assignment is an introduction to syntax regarding memory in C and Binary File I/O as well as Low-level data types like uint8_t.

  **filter-more**  
  **Folder Contents: images(courtyard.bmp, stadium.bmp, tower.bmp, yard.bmp), bmp.h, filter.c, helper.c, helpers.h**  
  **To build with VSCode, Powershell, and gcc: gcc -o filter filter.c helpers.c -lm**
  - This program takes a .BMP image and manipulates the pixels to make a new image with grayscale(-g), reflection(-r), blur(-b), and edge detection(-e).
  - In command line, run the program with ./filter flag image output. (e.g. "./filter -g images/yard.bmp out.bmp")
  - Based on flag, manipulates pixels accordingly.
    - Greyscale - averages the RGB values then redistributes them to the same pixel.
    - Reflection - Swaps the first and last pixel until the image is swapped.
    - Blur - Takes the average of each RGB value surrounding the pixel then puts that RGB value into its respective color.
    - Edge Detection - Uses Sobel's Filter Algorithm to highlight edges on the picture.
      - Applies a gx and gy kernel to each pixel in a 3x3 grid.
      - Takes the weighted sum for gx and gy(horizontal and vertical).
      - Combines gx and gy by taking the square root of (gx^2 + gy^2). Rounds it to the closest int. Sets bounds to 0 to 255 for RGB.
      - Then finally, sets that color value to that result.
  - This assignment teaches 2D array manipulation in the form of an image, pixel manipulation using a box blur algorithm and Sobel filter algorithm.
  - Also teaches the idea behind memory, reading in files, writing files, and different structs integrating with the Main file(filter.c).  

  **recover**  
  **Folder Contents: recover.c, card.raw**  
  **To build with VSCode, Powershell, and gcc: gcc -o recover recover.c**
  > **Note:** Will output 50 .jpg files when ran with the card.raw from CS50.
  - This program takes in a .raw file and forensically recovers all .jpg files in the unprocessed data.
  - In command line, run the program with ./recover file.raw (e.g. "./recover card.raw")
  - The program will iterate through every byte of data until the first four bytes are 0xff, 0xd8, 0xff, and (0xe0 to 0xef).
  - This indicates a .jpg file and will start to write to an out put file.
  - Every .jpg output file is named from 0 to 999. (e.g. card.raw has 50 .jpg files so 000.jpg is the first and 049.jpg is the last)
  - This assignment teaches typedef aliases like "uint8_t" from the "stdint.h" library. Open, Read, Write binary files in C (file I/O functions).
  - Also teaches low-level file analysis and recovery such as identifying file format such as a .jpg file with its signiture.      

  ## Problem Set 5

  **inheritance**  
  **Folder Contents: inheritance.c**  
  **To build with VSCode, Powershell, and gcc: gcc -o inheritance inheritance.c**
  - This program creates a virtual family tree based on blood types and reveals each generations blood types according to their parents.
  - Such as a child could have a blood type of 'AB' which would mean one parent could have 'AA' while the other has 'BB'.
  - No command line or user inputs.
  - This assignment teaches how you can use memory dynamically to create data structures.
  - Easy due to comments. 

