#include <stdio.h>
#include <ctype.h>
#include <string.h>

int get_score(char* word);
char* to_lowercase(char* word);
void determine_winner(int player1_score, int player2_score);

int main(void)
{
    char player1[100]; // assuming maximum word length of 100 characters
    char player2[100]; // assuming maximum word length of 100 characters

    do
    {
        printf("Player 1: ");
        fgets(player1, sizeof(player1), stdin);
        player1[strcspn(player1, "\n")] = '\0'; // remove newline if present
    }
    while (strlen(player1) <= 0);

    do
    {
        printf("Player 2: ");
        fgets(player2, sizeof(player2), stdin);
        player2[strcspn(player2, "\n")] = '\0'; // remove newline if present
    }
    while (strlen(player2) <= 0);

    int player1_score = get_score(player1);
    int player2_score = get_score(player2);

    determine_winner(player1_score, player2_score);
    return 0;
}

// Iterates through each character of the word and adds to the respective players total score.
int get_score(char* word)
{
    const int VOWEL = 1;
    const int COMMON = 2;
    const int GOOD = 3;
    const int GREAT = 4;
    const int BEST = 5;
    const int RARE = 8;
    const int SUPERRARE = 10;

    int word_score = 0;
    char* lowercase_word = to_lowercase(word);
    int word_length = strlen(lowercase_word);

    for (int i = 0; i < word_length; i++)
    {
        switch (lowercase_word[i])
        {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'l':
            case 'n':
            case 'r':
            case 's':
            case 't':
                word_score += VOWEL; //1
                break;

            case 'd':
            case 'g':
                word_score += COMMON; //2
                break;

            case 'b':
            case 'c':
            case 'm':
            case 'p':
                word_score += GOOD; //3
                break;

            case 'f':
            case 'h':
            case 'v':
            case 'w':
            case 'y':
                word_score += GREAT; //4
                break;

            case 'k':
                word_score += BEST; //5
                break;

            case 'j':
            case 'x':
                word_score += RARE; //8
                break;

            case 'q':
            case 'z':
                word_score += SUPERRARE; //10
                break;
        }
    }

    return word_score;
}

// Takes a string and makes it all lowercase.
char* to_lowercase(char* word)
{
    int word_length = strlen(word);
    for (int i = 0; i < word_length; i++)
    {
        if (isupper(word[i]))
        {
            word[i] = tolower(word[i]);
        }
    }

    return word;
}

// Compares scores and decides the win conditions for the game of scrabble.
void determine_winner(int player1_score, int player2_score)
{
    if (player1_score > player2_score)
    {
        printf("Player 1 wins!\n");
    }
    else if (player2_score > player1_score)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}