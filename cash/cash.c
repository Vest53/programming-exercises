
#include <stdio.h>

int main() {
    int change;

    do {
        printf("Change owed: ");

        if (scanf("%d", &change) != 1) {
            while (getchar() != '\n');
            change = -1;
        }

        if (change < 1) {
            printf("Please enter a value greater than 0.\n");
        }
    } while (change < 1);// Repeat until input is valid


// Variables for counting coins
    int coins = 0;

// Available currencies
    int coinsAvailable[] = {25, 10, 5, 1};
    int numCoins = sizeof(coinsAvailable) / sizeof(coinsAvailable[0]);

// Calculate the minimum number of coins
    for (int i = 0; i < numCoins; i++) {
        while (change >= coinsAvailable[i]) {
            change -= coinsAvailable[i];
            coins++;
        }
    }


// Print the minimum number of coins
    printf("%d\n", coins);

    return 0;
}
