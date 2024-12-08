#include <stdio.h>
#include <string.h>

// Assuming the maximum number of candidates and their structure are defined in plurality.c
#define MAX_CANDIDATES 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int votes;
} Candidate;

// Declaration of the function to simulate the election
void run_election(Candidate candidates[], int candidate_count, int voter_count);

int main() {
    Candidate candidates[MAX_CANDIDATES];
    int candidate_count = 3;

    // Initialize candidates
    strcpy(candidates[0].name, "Alice");
    candidates[0].votes = 0;

    strcpy(candidates[1].name, "Bob");
    candidates[1].votes = 0;

    strcpy(candidates[2].name, "Charlie");
    candidates[2].votes = 0;

    // Simulate a fixed number of voters
    int voter_count = 5;

    // Run the election with fixed votes for testing
    run_election(candidates, candidate_count, voter_count);

    return 0;
}

// Function to run the election
void run_election(Candidate candidates[], int candidate_count, int voter_count) {
    // Simulated votes
    char* votes[] = {"Alice", "Bob", "Alice", "Charlie", "Alice"};

    // Count the votes
    for (int i = 0; i < voter_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if (strcmp(votes[i], candidates[j].name) == 0) {
                candidates[j].votes++;
                break;
            }
        }
    }

    // Display results
    printf("\nElection Results:\n");
    for (int i = 0; i < candidate_count; i++) {
        printf("%s: %d votes\n", candidates[i].name, candidates[i].votes);
    }

    // Determine winner
    int max_votes = 0;
    int winner_index = -1;
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > max_votes) {
            max_votes = candidates[i].votes;
            winner_index = i;
        }
    }

    if (winner_index != -1) {
        printf("\nThe winner is: %s with %d votes.\n", candidates[winner_index].name, max_votes);
    }
}
