
#include <stdio.h>

int main() {
    int height;
    char buffer[10]; // To store user input

// Request the height of the pyramid from the user
    while (1) {
        printf("Digite a altura da pirâmide: ");
        fgets(buffer, sizeof(buffer), stdin); // Read input as string

        //Attempts to convert the input to an integer
        if (sscanf(buffer, "%d", &height) != 1 || height < 1) {
            printf("Please enter a positive integer greater than 0.\n");
        } else {
            break; //Exit the loop if the input is valid

        }
    }

    // Loop for each row of the pyramid

    for (int i = 1; i <= height; i++) {
        // Print the blanks

        for (int j = i; j < height; j++) {
            printf(" ");
        }
        // Print the hashes

        for (int j = 1; j <= i; j++) {
            printf("#");
        }
        // New line after each line of the pyramid
        printf("\n");
    }

    return 0;
}
