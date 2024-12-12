#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9          // Max number of candidates
#define MAX_VOTERS 100 // Max number of voters

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Preferences array
int preferences[MAX_VOTERS][MAX];

// Number of candidates
int candidate_count;

// Number of voters
int voter_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid number of candidates
    if (argc < 2 || argc > MAX + 1)
    {
        printf("Usage: runoff candidate1 candidate2 ...\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    // Get number of voters
    voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            if (!vote(i, j, name))
            {
                printf("Invalid vote. Please choose a valid candidate.\n");
                j--; // Decrement j to repeat this iteration
            }
        }
    }

    // Conduct runoff until a winner is found
    while (true)
    {
        tabulate();
        if (print_winner())
        {
            break;
        }
        int min = find_min();
        if (is_tie(min))
        {
            print_winner(); // Print all remaining candidates
            break;
        }
        eliminate(min);
    }
    return 0;
}

// Vote function
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Count votes for non-eliminated candidates
void tabulate(void)
{
    // Reset vote counts
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
    }

    // Count votes based on preferences
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Check if the candidate is not eliminated
            if (!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes++;
                break; // Only count the first non-eliminated candidate
            }
        }
    }
}

// Print the winner of the election
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if this candidate has more than half the votes
        if (candidates[i].votes > voter_count / 2)
        {
            printf("The winner is: %s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Find the minimum votes among non-eliminated candidates
int find_min(void)
{
    int min_votes = MAX_VOTERS; // Start with a large number
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }
    }
    return min_votes;
}

// Check if there is a tie
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false; // Not a tie
        }
    }
    return true; // All remaining candidates have the same number of votes
}

// Eliminate candidates with the minimum number of votes
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}
