#include <stdio.h>
#include <string.h>

#define MAX_CANDIDATES 100
#define MAX_NAME_LENGTH 50

// Define the Candidate structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    int votes;
} Candidate;

// Function prototypes
int vote(Candidate candidates[], int candidate_count, char *name);
void print_winner(Candidate candidates[], int candidate_count);
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

    // Run the election
    run_election(candidates, candidate_count, voter_count);

    return 0;
}

// Function to run the election
void run_election(Candidate candidates[], int candidate_count, int voter_count) {
    // Simulated votes
    char *votes[] = {"Alice", "Bob", "Alice", "Charlie", "Alice"};

    // Count the votes
    for (int i = 0; i < voter_count; i++) {
        vote(candidates, candidate_count, votes[i]);
    }

    // Display results
    printf("\nElection Results:\n");
    for (int i = 0; i < candidate_count; i++) {
        printf("%s: %d votes\n", candidates[i].name, candidates[i].votes);
    }

    // Print the winner
    print_winner(candidates, candidate_count);
}

// Function to register a vote
int vote(Candidate candidates[], int candidate_count, char *name) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(candidates[i].name, name) == 0) {
            candidates[i].votes++;
            return 1; // Valid vote
        }
    }
    return 0; // Invalid candidate
}

// Function to print the winner(s)
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
