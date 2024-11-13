#include <stdio.h>

int main() {
    int height, i, j;

    printf("Enter the height of the pyramid: ");
    scanf("%d", &height);

    for (i = 1; i <= height; i++) {
        for (j = i; j < height; j++) {
            printf(" ");
        }
        for (j = 1; j <= i; j++) {
            printf("#");
        }
        printf("\n");
    }

    return 0;
}
