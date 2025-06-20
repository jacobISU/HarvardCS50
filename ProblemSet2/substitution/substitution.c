#include <ctype.h>
#include <stdio.h>
#include <string.h>

int validate_argument(int argc, char* argv[]);
int find_alphabet_index(char c);

// This is a substitution cipher to encrypt and print a user's text with a 26-character key from the
// command-line.
int main(int argc, char* argv[])
{
    char* key;

    // Checks if command-line argument is valid by meeting the specifications.
    int validation_result = validate_argument(argc, argv);

    if (validation_result > 0)
    {
        // Terminate program if error was detected.
        return 1;
    }
    else
    {
        // Key is valid.
        key = argv[1];
    }

    // Ask the user for plain text to encrypt.
    char plain_text[1024];
    printf("plaintext: ");
    fgets(plain_text, sizeof(plain_text), stdin);
    plain_text[strcspn(plain_text, "\n")] = '\0';

    const int text_length = strlen(plain_text);
    char cipher_text[text_length + 1];

    // Encryption Start
    for (int i = 0; i < text_length; i++)
    {
        // Locate where character index is in the alphabet.
        int index = find_alphabet_index(plain_text[i]);

        // if not an alphabetic character keep character the same.
        if (index == 27)
        {
            cipher_text[i] = plain_text[i];
        }
        else
        {
            // Keeps the capitolization of the plain text provided by the user.
            if (isupper(plain_text[i]))
            {
                cipher_text[i] = toupper(key[index]);
            }
            else
            {
                cipher_text[i] = tolower(key[index]);
            }
        }
    }

    cipher_text[text_length] = '\0';
    printf("ciphertext: %s\n", cipher_text);

    return 0;
}

// Checks if only one argument was provided and that it meets the standards of the program.
// Has atleast 26 characters, Has only alphabetic letters, and has no repeat characters of the same
// letter.
int validate_argument(int argc, char* argv[])
{
    // Only runs with one command-line argument.
    if (argc != 2)
    {
        printf("Error: Must input atleast one argument for key.\n");
        return 1;
    }

    // Command-line argument must be 26 characters
    // AND only alphabetic
    // AND no repeat characters.
    int argument_length = strlen(argv[1]);
    char unique_chars[26];
    int empty_index = 0;
    int char_count = 0;

    // returns a error number if specifications are violated.
    for (int i = 0; i < argument_length; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Error: Argument must only contain alphabetic characters.\n");
            return 3;
        }

        int unique_char_length = strlen(unique_chars);

        for (int j = 0; j < empty_index; j++)
        {
            if (argv[1][i] == toupper(unique_chars[j]) || argv[1][i] == tolower(unique_chars[j]))
            {
                printf("Error: Argument must not contain repeated characters.\n");
                return 4;
            }
        }

        unique_chars[empty_index] = argv[1][i];
        empty_index++;
        char_count++;
    }

    if (char_count != 26)
    {
        printf("Error: Argument must be 26 characters long.\n");
        return 2;
    }

    // If no errors are detected meaning argument is valid.
    return 0;
}

// Finds the non-case sensitive alphabetical index of the specific character of the plain text.
int find_alphabet_index(char c)
{
    char* upper_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* lower_alphabet = "abcdefghijklmnopqrstuvwxyz";
    const int ALPHABET_SIZE = 26;
    const int NOT_IN_ALPHABET = 27;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (c == upper_alphabet[i] || c == lower_alphabet[i])
        {
            return i;
        }
    }

    // If character not found in upper or lower alphabet.
    return NOT_IN_ALPHABET;
}
