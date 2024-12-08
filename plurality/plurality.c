#include <stdio.h>
#include <string.h>
#include "plurality.c"  // Include your main functionality

#define MAX_CANDIDATES 100

int vote(Candidate candidates[], int candidate_count, char *name);
void print_winner(Candidate candidates[], int candidate_count);

int main(int argc, char *argv[]) {
    Candidate candidates[MAX_CANDIDATES];
    int candidate_count = 3;

    // Initialize candidates
    strcpy(candidates[0].name, "Alice");
    candidates[0].votes = 0;

    strcpy(candidates[1].name, "Bob");
    candidates[1].votes = 0;

    strcpy(candidates[2].name, "Charlie");
    candidates[2].votes = 0;

    // Example of calling the vote function
    vote(candidates, candidate_count, "Alice");
    vote(candidates, candidate_count, "Bob");
    vote(candidates, candidate_count, "Alice");

    // Check if the votes are counted correctly
    printf("Votes for Alice: %d\n", candidates[0].votes);
    printf("Votes for Bob: %d\n", candidates[1].votes);
    printf("Votes for Charlie: %d\n", candidates[2].votes);

    // Print the winner
    print_winner(candidates, candidate_count);

    return 0;
}

// Function definitions as needed
int vote(Candidate candidates[], int candidate_count, char *name) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(candidates[i].name, name) == 0) {
            candidates[i].votes++;
            return 1; // Valid vote
        }
    }
    return 0; // Invalid candidate
}

void print_winner(Candidate candidates[], int candidate_count) {
    int max_votes = 0;

    // Find the maximum votes
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > max_votes) {
            max_votes = candidates[i].votes;
        }
    }

    // Print all candidates with max votes
    printf("Winner(s):\n");
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes == max_votes) {
            printf("%s\n", candidates[i].name);
        }
    }
}
