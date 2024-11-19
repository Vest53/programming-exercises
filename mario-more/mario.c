#include <stdio.h>

int main()
{
    int height;
    char buffer[10];

    while (1)
    {
        printf("Enter the height of the pyramid (between 1 and 8): ");
        fgets(buffer, sizeof(buffer), stdin);

        // Try to convert the input to an integer
        if (sscanf(buffer, "%d", &height) == 1 && height >= 1 && height <= 8)
        {
            break; // Exit the loop if the input is valid
        }
        else
        {
            printf("Invalid input. Please try again.\n");
        }
    }

    // Build the pyramid
    for (int i = 1; i <= height; i++)
    {
        // Print leading spaces
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }

        // Print hashes for the first pyramid
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // Print space between the pyramids
        printf("  ");

        // Print hashes for the second pyramid
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // New line after each level
        printf("\n");
    }

    return 0;
}
