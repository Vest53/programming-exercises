#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9 // Max number of candidates

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid number of candidates
    if (argc < 2 || argc > MAX + 1)
    {
        printf("Usage: plurality candidate1 candidate2 ...\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    // Get number of voters
    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Keep asking until the user gives a valid vote
        while (!vote(name))
        {
            printf("Invalid vote.\n");
            name = get_string("Vote: ");
        }
    }

    // Print the winner(s)
    print_winner();
    return 0;
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Iterate over each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if candidate's name matches given name
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Increment candidate's votes and return true
            candidates[i].votes++;
            return true;
        }
    }
    // If no match, return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max_votes = 0;

    // Find the maximum number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }

    // Print the candidate(s) with maximum votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
