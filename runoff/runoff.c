#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9 // Max number of candidates

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Number of voters
int voter_count;

// Function prototypes
void vote(int voter);
void tabulate(void);
bool print_winner(void);
void eliminate(void);

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
        vote(i);
    }

    // Conduct runoff until a winner is found
    while (true)
    {
        tabulate();

        if (print_winner())
        {
            break;
        }

        eliminate();
    }
    return 0;
}

// Function for voters to cast their votes
void vote(int voter)
{
    // Array to hold the voter's preferences
    int preferences[MAX];

    // Get the voter's ranked preferences
    for (int i = 0; i < candidate_count; i++)
    {
        string name = get_string("Rank %i: ", i + 1);

        // Check if the candidate exists
        bool found = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (strcmp(candidates[j].name, name) == 0)
            {
                preferences[i] = j;
                found = true;
                break;
            }
        }

        // If candidate not found, ask for input again
        if (!found)
        {
            printf("Invalid vote. Please choose a valid candidate.\n");
            i--; // Decrement i to repeat this iteration
        }
    }
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
            // Get the voter's preferences
            if (candidates[j].eliminated == false)
            {
                candidates[j].votes++;
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

// Eliminate the candidate with the least votes
void eliminate(void)
{
    int min_votes = voter_count; // Start with max possible votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }
    }

    // Eliminate all candidates with the minimum vote count
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min_votes)
        {
            candidates[i].eliminated = true;
        }
    }
}
