#include <stdio.h>

int main() {
    int altura;
    char buffer[10];

    while (1) {
        printf("Digite a altura da pirâmide (entre 1 e 8): ");
        fgets(buffer, sizeof(buffer), stdin);

        // Tenta converter a entrada para um inteiro
        if (sscanf(buffer, "%d", &altura) == 1 && altura >= 1 && altura <= 8) {
            break; // Saia do loop se a entrada for válida
        } else {
            printf("Entrada inválida. Tente novamente.\n");
        }
    }

    // Construir a pirâmide
    for (int i = 1; i <= altura; i++) {
        // Imprimir espaços à esquerda
        for (int j = 0; j < altura - i; j++) {
            printf(" ");
        }

        // Imprimir hashes para a primeira pirâmide
        for (int j = 0; j < i; j++) {
            printf("#");
        }

        // Imprimir espaço entre as pirâmides
        printf("  ");

        // Imprimir hashes para a segunda pirâmide
        for (int j = 0; j < i; j++) {
            printf("#");
        }

        // Nova linha após cada nível
        printf("\n");
    }

    return 0;
}
