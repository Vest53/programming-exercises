#include <stdio.h>
#include <string.h>

#define MAX_CANDIDATES 9
#define MAX_NAME_LENGTH 50

// Define the Candidate structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    int votes;
} Candidate;

// Function prototypes
int vote(Candidate candidates[], int candidate_count, char *name);
void print_winner(Candidate candidates[], int candidate_count);

int main() {
    Candidate candidates[MAX_CANDIDATES];
    int candidate_count;

    // Prompt for the number of candidates
    printf("Enter the number of candidates (up to %d): ", MAX_CANDIDATES);
    if (scanf("%d", &candidate_count) != 1 || candidate_count < 1 || candidate_count > MAX_CANDIDATES) {
        printf("Invalid number of candidates.\n");
        return 1;
    }

    // Initialize the candidates
    for (int i = 0; i < candidate_count; i++) {
        printf("Enter the name of candidate %d: ", i + 1);
        scanf("%49s", candidates[i].name); // Limit input
        candidates[i].votes = 0;
    }

    int voter_count;
    printf("Enter the number of voters: ");
    if (scanf("%d", &voter_count) != 1) {
        printf("Invalid number of voters.\n");
        return 1;
    }

    // Voting
    for (int i = 0; i < voter_count; i++) {
        char name[MAX_NAME_LENGTH];
        printf("Enter the name of the candidate to vote for: ");
        scanf("%49s", name); // Limit input

        if (!vote(candidates, candidate_count, name)) {
            printf("Invalid vote for %s.\n", name);
        }
    }

    // Show results
    printf("\nElection Results:\n");
    for (int i = 0; i < candidate_count; i++) {
        printf("%s: %d votes\n", candidates[i].name, candidates[i].votes);
    }

    // Print the winner
    print_winner(candidates, candidate_count);

    return 0;
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

    // Find the maximum number of votes
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > max_votes) {
            max_votes = candidates[i].votes;
        }
    }

    // Print all candidates with maximum votes
    printf("Winner(s):\n");
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes == max_votes) {
            printf("%s\n", candidates[i].name);
        }
    }
}
