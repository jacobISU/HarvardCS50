#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
char *candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

bool dfs(int root, int current, bool visited[]);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];
        char name[100];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            printf("Rank %i: ", j + 1);
            scanf("%s", name);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, char *name, int ranks[])
{
    // Sets the array ranks[] to the order in which the voter votes.
    // (e.g. Alice Bob Charlie is {0,1,2} while Charlie Alice Bob is {2,0,1})
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // returns true if votes are valid with updated ranks array.
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Takes the updated ranks array for the ith voter as input.
    // Iterates through the ranks array grabbing the ith and ith + 1 ranks. (e.g. Charlie, Alice,
    // Bob would produce ranks[] = {2, 0, 1} so i would be 2 and i + 1 would be 0 the first
    // iteration.) Increment preference[i][j] to show that candidate rank[i] is prefered over
    // candidate rank[j]. (e.g. Charlie is preferred over Alice and Bob. Alice is prefered over Bob)
    // 0 1 0
    // 0 0 0
    // 1 1 0
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    // preferences 2D array is now set.
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        pair versus;

        for (int j = 0; j < candidate_count; j++)
        {
            // Only evaluates the preferrences in front of the ith ranked candidate.
            // (e.g. 2 0 1 means 2 wont evaluate 2 but 0 and 1. 0 wont evaluate 2 or 0 but will do
            // 1)
            if (i < j)
            {
                // Checks which candidate is preferred over the other by iterating through the
                // preferences 2D array. (e.g. First iteration: preferences[0][1] vs
                // preferences[1][0] would show that Alice is preferred over Bob and therefore the
                // winner is i - "Alice" and loser is j - "Bob")
                if (preferences[i][j] > preferences[j][i])
                {
                    versus.winner = i;
                    versus.loser = j;

                    // Add the new pair and increment the size of the pairs array.
                    pairs[pair_count] = versus;
                    pair_count++;
                }
                // (e.g. Second Iteration: preferences[0][2] vs preferences[2][0] would show that
                // Charlie is preferred over Alice and therefore the winner is j - "Charlie" and
                // loser is i - "Alice"))
                else if (preferences[i][j] < preferences[j][i])
                {
                    versus.winner = j;
                    versus.loser = i;

                    // Add the new pair and increment the size of the pairs array.
                    pairs[pair_count] = versus;
                    pair_count++;
                }
            }
        }
    }

    // Pair array is now set.
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Iterate through all pairs in pairs array.
    for (int i = 0; i < pair_count; i++)
    {
        // The difference between the votes preferred over the other is the strength of victory.
        // (e.g. in a vote of Charlie, Alice, Bob, The first pair is Winner: 0 and Loser: 1 which
        // produces a preference[0][1] - preference[1][0] which is 1 - 0 = 1. So victory of strength
        // is 1 for first pair.)
        // Iterate through each pair to compare the victory strength of the jth pair with the
        // strength of the jth+1 pair(Next pair).
        for (int j = 0; j < pair_count; j++)
        {
            int k = j + 1;
            int strength_j = preferences[pairs[j].winner][pairs[j].loser] -
                             preferences[pairs[j].loser][pairs[i].winner];
            int strength_k = preferences[pairs[k].winner][pairs[k].loser] -
                             preferences[pairs[k].loser][pairs[k].winner];

            // If the j strength is smaller then the k strength, bubble the smaller strength down
            // the array. Descending order.
            if (strength_j < strength_k)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[k];
                pairs[k] = temp;
            }
        }
    }

    // Pair array is now sorted.
    // (e.g. a vote of Charlie, Alice, Bob would produce a sorted pairs array of {[0,1], [2,0], and
    // [2,1]} which all have the victory strength of 1)
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    // Iterate through pairs array.
    for (int i = 0; i < pair_count; i++)
    {
        // Initialize all cells in visited array to false.
        bool visited_array[MAX];
        for (int j = 0; j < candidate_count; j++)
        {
            visited_array[j] = false;
        }

        // Depth-First Search used to detect a cycle in the "graph".
        // (e.g. In a vote of Charlie, Alice, Bob, candidate node would be 0, current node would be
        // 1, and visited array would be all false.) If a cycle is not detected, lock in the pair in
        // the 2D array locked.
        if (!dfs(pairs[i].winner, pairs[i].loser, visited_array))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// DFS method that returns true if a cycle is detected.
// (e.g. If Candidate 0 is in the visited array, then an arrow points back to 0, meaning a cycle.)
bool dfs(int root, int current, bool visited[])
{
    // If current node in question has already been visited, don't traverse.
    if (visited[current])
    {
        return false;
    }

    // If source is same as current then cycle detected
    if (current == root)
    {
        return true;
    }

    // Set unvisited node to visited.
    visited[current] = true;

    // Iterate through all candidates.
    for (int i = 0; i < candidate_count; i++)
    {
        // If the locked[][] truth table(graph) has a true(edge to other candidate) in the
        // candidates row, then visit the node with recursive call.
        if (locked[current][i])
        {
            // visit the node that the true (edge) points to and see if a neighbor of it creates a
            // cycle.
            if (dfs(root, i, visited))
            {
                // Cycle was detected.
                return true;
            }
        }
    }

    // no cycle was detected.
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool root = true;

        for (int j = 0; j < candidate_count; j++)
        {
            // Checking the locked[][] table by column to see if any edges are pointing to it.
            // (e.g. the 2d locked array, a truth table(graph) that looks like this...
            // 0 1 0
            // 0 0 0
            // 1 0 0
            // Since locked[2][0] has a 1(true), Candidate 0(Alice) is being pointed to by
            // 2(Charlie)) This results in Candidate 0(Alice) is not the root and checks the next
            // ith candidate.
            if (locked[j][i])
            {
                root = false;
                break;
            }
        }

        // If no true's were detected in the Candidates column meaning that no arrows are pointing
        // to them. They are the source and the winner.
        if (root)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
