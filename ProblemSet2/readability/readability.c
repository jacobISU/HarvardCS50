#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float get_average_letters(char* text);
float get_average_sentences(char* text);
void determine_level(int index);
int is_word_boundary(char c);

const int per_n_words = 100;

// Based on the Coleman-Liau Index, takes in some text and determines the texts intended reading
// level by grade.
int main(void)
{
    char text[1000];
    int text_length;

    do
    {
        printf("Text: ");
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = '\0'; // remove newline
        text_length = strlen(text);
    }
    while (text_length <= 0);

    // Variable for the Coleman-Liau index.
    //  index = 0.0588 * L - 0.296 * S - 15.8
    float L = get_average_letters(text);
    float S = get_average_sentences(text);
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    determine_level(index);
}

// Gets the average amount of letters per word then simulates 100 words.
float get_average_letters(char* text)
{
    float word_count = 0;
    float letter_count = 0;
    int text_length = strlen(text);
    int isWord;

    // Counts each character individually and determines if it is a letter or the end to a word.
    for (int i = 0; i < text_length + 1; i++)
    {
        // if a character and nothing else
        if (isalpha(text[i]))
        {
            letter_count++;
        }

        isWord = is_word_boundary(text[i]);

        if (isWord == 0)
        {
            word_count++;
        }
    }

    return (letter_count / word_count) * per_n_words;
}

// Gets the average amount of sentences per word then simulates 100 words.
float get_average_sentences(char* text)
{
    // Get average amount of sentences in 100 words.
    float word_count = 0;
    float sentence_count = 0;
    int text_length = strlen(text);
    int isWord;

    // if a sentence by appropriate punctuation.
    for (int i = 0; i < text_length + 1; i++)
    {
        switch (text[i])
        {
            case '.':
            case '!':
            case '?':
                sentence_count++;
                break;
        }

        isWord = is_word_boundary(text[i]);

        if (isWord == 0)
        {
            word_count++;
        }
    }

    return (sentence_count / word_count) * per_n_words;
}

// Judges by the index value what reading level the text is meant for.
void determine_level(int index)
{
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Identifies if a character indicates the end of a word.
int is_word_boundary(char c)
{
    // if char is end of a word, return "true"
    switch (c)
    {
        case ' ':
        case '\0':
            return 0;
            break;
        // else return "false"
        default:
            return 1;
            break;
    }
}