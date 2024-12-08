#include <stdio.h>
#include <string.h>

#define MAX_CANDIDATES 100
#define MAX_NAME_LENGTH 50

int main() {
    char candidates[MAX_CANDIDATES][MAX_NAME_LENGTH];
    int votes[MAX_CANDIDATES] = {0};
    int num_candidates, num_voters;

    // Input number of candidates
    printf("Enter the number of candidates: ");
    scanf("%d", &num_candidates);
    getchar(); // consume newline

    // Input candidate names
    for (int i = 0; i < num_candidates; i++) {
        printf("Enter the name of candidate %d: ", i + 1);
        fgets(candidates[i], MAX_NAME_LENGTH, stdin);
        candidates[i][strcspn(candidates[i], "\n")] = 0; // remove newline
    }

    // Input number of voters
    printf("Enter the number of voters: ");
    scanf("%d", &num_voters);
    getchar(); // consume newline

    // Capture votes
    for (int i = 0; i < num_voters; i++) {
        char vote[MAX_NAME_LENGTH];
        printf("Voter %d, vote for a candidate (enter the name): ", i + 1);
        fgets(vote, MAX_NAME_LENGTH, stdin);
        vote[strcspn(vote, "\n")] = 0; // remove newline

        // Check if the candidate exists and count the vote
        int found = 0;
        for (int j = 0; j < num_candidates; j++) {
            if (strcmp(vote, candidates[j]) == 0) {
                votes[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Candidate not found. Vote not counted.\n");
        }
    }

    // Determine the winner
    int max_votes = 0;
    int winner_index = -1;
    for (int i = 0; i < num_candidates; i++) {
        if (votes[i] > max_votes) {
            max_votes = votes[i];
            winner_index = i;
        }
    }

    // Display results
    printf("\nElection Results:\n");
    for (int i = 0; i < num_candidates; i++) {
        printf("%s: %d votes\n", candidates[i], votes[i]);
    }

    if (winner_index != -1) {
        printf("\nThe winner is: %s with %d votes.\n", candidates[winner_index], max_votes);
    }

    return 0;
}
