#include <stdio.h>

int main() {
    int change;

    do {
        printf("Change owed: ");
        scanf("%d", &change);

        if (change < 1) {
            printf("Please enter a value greater than 0.\n");
        }
    } while (change < 1);


    int coins = 0;

    int coinsAvailable[] = {25, 10, 5, 1};
    int numCoins = sizeof(coinsAvailable) / sizeof(coinsAvailable[0]);

    for (int i = 0; i < numMoedas; i++) {
        while (change >= coinsAvailable[i]) {
            change -= coinsAvailable[i];
            coins++;
        }
    }

    printf("%d\n", coinns);

