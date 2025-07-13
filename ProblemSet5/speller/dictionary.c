// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100;

// Hash table
node *table[N];

// Dictionary word count
int words_in_dictionary = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int word_length = strlen(word);
    char buffer[LENGTH];

    for (int i = 0; i < word_length; i++)
    {
        buffer[i] = tolower(word[i]);
    }

    // add null byte to end of character array.
    buffer[word_length] = '\0';

    // Get index in dictionary from hash function
    unsigned int index = hash(buffer);

    // Get head of linked list
    node *current = table[index];

    // Word doesn't exist.
    if (current == NULL)
    {
        return false;
    }

    // While the word from text doesn't equal the word from the node.
    while (strcasecmp(word, current->word) != 0)
    {
        if (current->next == NULL)
        {
            // Word doesn't exists.
            return false;
        }
        else
        {
            current = current->next;
        }
    }

    // Word is in dictionary.
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Analyze up to 6 chars and establish where in the hash they exist.
    unsigned int sum = 0;
    int number_of_chars_to_analyze = 6;
    for (int i = 0; i < number_of_chars_to_analyze && word[i + 1] != '\0'; i++)
    {
        sum += toupper(word[i]) - 'A';
    }

    return sum % N;
    // return toupper(word[0]) - 'A'; // Original hash function to make better.
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        // No file found
        return false;
    }

    // Store each word in the file here.
    char word[LENGTH];

    // fscanf arguments are (file, the word from file, the array to store the word).
    while (fscanf(source, "%s", word) != EOF)
    {
        // Increment global variable for words in dictionary
        words_in_dictionary++;

        // Create a new node for each word
        node *current_node = malloc(sizeof(node));
        if (current_node == NULL)
        {
            // failed to create node.
            return false;
        }

        // Copy word into node's word.
        strcpy(current_node->word, word);

        // Hash word to obtain a hash value
        unsigned int index = hash(current_node->word);

        // Insert node into hash table at that location
        if (table[index] == NULL)
        {
            // If the linked list is empty
            current_node->next = NULL;
            table[index] = current_node;
        }
        else
        {
            // If the linked list has nodes already in it.
            current_node->next = table[index];
            table[index] = current_node;
        }
    }

    // Close the dictionary file.
    fclose(source);

    // load successful
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words_in_dictionary;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // iterate through hash table
    for (int i = 0; i < N; i++)
    {
        // head node
        node *current = table[i];

        // traverse down linked list of nodes
        while (current != NULL)
        {
            node *tmp = current;
            current = current->next;
            free(tmp);
        }

        // set that index to NULL
        table[i] = NULL;
    }

    // unload successful
    return true;
}
