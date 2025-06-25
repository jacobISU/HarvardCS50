#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    //50 character length for candidate name.
    char name[50];
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(char* name);
void print_winner(void);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i].name, argv[i + 1]);
        candidates[i].votes = 0;
    }

    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        char name[50];
        printf("Vote: ");
        scanf("%s", name);

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(char *name)
{
    // Find candidate "name" in candidate array and keep index.
    // If found, increment candidate vote by same index and return true.
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Uses a Selection Sort algorithm to sort the candidates array by number of votes.
    for (int i = 0; i < candidate_count; i++)
    {
        // Smallest number to analyze is always at the start of the array where the number hasn't
        // been compared yet.
        candidate smallest = candidates[i];
        int smallest_index = i;

        // Iterate through to find and hold smallest number.
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (candidates[j].votes < smallest.votes)
            {
                smallest = candidates[j];
                smallest_index = j;
            }
        }

        // After finding the smallest number of votes in the candidate array, swap with appropriate
        // "smallest index".
        candidate hold = candidates[i];
        candidates[i] = smallest;
        candidates[smallest_index] = hold;
    }

    // Print every candidate name with the same vote score as the highest.
    int winning_votes = candidates[candidate_count - 1].votes;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == winning_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
