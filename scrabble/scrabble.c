#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Function to calculate the score of a word
int calculateScore(const char *word)
{
    int score = 0;
    int values[] = {
        0,  // Index 0 is not used
        1,  // A
        3,  // B
        3,  // C
        2,  // D
        1,  // E
        4,  // F
        2,  // G
        4,  // H
        1,  // I
        8,  // J
        5,  // K
        1,  // L
        3,  // M
        1,  // N
        1,  // O
        3,  // P
        10, // Q
        1,  // R
        1,  // S
        1,  // T
        1,  // U
        4,  // V
        4,  // W
        8,  // X
        4,  // Y
        10  // Z
    };

    for (int i = 0; i < strlen(word); i++)
    {
        char letter = toupper(word[i]); // Convert to uppercase
        if (letter >= 'A' && letter <= 'Z')
        {
            score += values[letter - 'A' + 1]; // Add the letter's score
        }
    }
    return score;
}

int main()
{
    char player1Word[100];
    char player2Word[100];

    // Prompt player 1 for input
    printf("Player 1, enter your word: ");
    scanf("%s", player1Word);

    // Prompt player 2 for input
    printf("Player 2, enter your word: ");
    scanf("%s", player2Word);

    // Calculate each player's score
    int player1Score = calculateScore(player1Word);
    int player2Score = calculateScore(player2Word);

    // Display the result
    printf("Player 1 Score: %d\n", player1Score);
    printf("Player 2 Score: %d\n", player2Score);

    if (player1Score > player2Score)
    {
        printf("Player 1 wins!\n");
    }
    else if (player2Score > player1Score)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("It's a tie!\n");
    }

    return 0;
}
