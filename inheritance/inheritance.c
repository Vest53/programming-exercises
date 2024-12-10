#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOOD_TYPES 16

// Função para gerar tipos sanguíneos possíveis
void generate_blood_types(const char *parent1, const char *parent2) {
    char *blood_types[MAX_BLOOD_TYPES];
    int count = 0;

    // Gerar combinações possíveis
    for (int i = 0; i < strlen(parent1); i++) {
        for (int j = 0; j < strlen(parent2); j++) {
            char combination[3];
            combination[0] = parent1[i];
            combination[1] = parent2[j];
            combination[2] = '\0';

            // Verifica se já existe
            int exists = 0;
            for (int k = 0; k < count; k++) {
                if (strcmp(blood_types[k], combination) == 0) {
                    exists = 1;
                    break;
                }
            }

            // Se não existe, adiciona à lista
            if (!exists) {
                blood_types[count] = malloc(3 * sizeof(char)); // Aloca memória para a nova combinação
                if (blood_types[count] != NULL) {
                    strcpy(blood_types[count], combination); // Copia a combinação
                    count++;
                }
            }

            // Inverte a ordem
            combination[1] = parent2[(j + 1) % 2]; // Troca para o segundo alelo
            if (!exists) {
                blood_types[count] = malloc(3 * sizeof(char));
                if (blood_types[count] != NULL) {
                    strcpy(blood_types[count], combination);
                    count++;
                }
            }
        }
    }

    // Exibir resultados
    printf("Possíveis tipos sanguíneos dos filhos:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", blood_types[i]);
        free(blood_types[i]); // Libera a memória alocada
    }
}

int main() {
    char parent1[3], parent2[3];

    // Entrada dos tipos sanguíneos dos pais
    printf("Digite o tipo sanguíneo do primeiro pai (ex: AO, BO, AB): ");
    scanf("%2s", parent1);
    printf("Digite o tipo sanguíneo do segundo pai (ex: AO, BO, AB): ");
    scanf("%2s", parent2);

    // Gerar e exibir os tipos sanguíneos possíveis
    generate_blood_types(parent1, parent2);

    return 0; // Indica sucesso
}
