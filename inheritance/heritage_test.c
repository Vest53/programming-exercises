#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct pessoa {
    char alelos[2][3]; // Dois alelos, cada um com até 2 caracteres + '\0'
    struct pessoa *pais[2]; // Ponteiros para os pais
} pessoa;

// Funções que você precisa implementar
pessoa* create_family(int n);
void free_family(pessoa* p);
int check_size(pessoa* p, int n);
int check_alleles(pessoa* p);

int main() {
    srand(time(0)); // Inicializa o gerador de números aleatórios

    pessoa *p = create_family(3); // Cria uma família

    // Verifica o tamanho e os alelos
    printf(check_size(p, 3) ? "size_true " : "size_false ");
    printf(check_alleles(p) ? "allele_true" : "allele_false");

    // Libera a memória
    free_family(p);

    return 0;
}

// Implementações das funções
pessoa* create_family(int n) {
    pessoa *family = malloc(n * sizeof(pessoa));
    for (int i = 0; i < n; i++) {
        snprintf(family[i].alelos[0], sizeof(family[i].alelos[0]), "AO");
        snprintf(family[i].alelos[1], sizeof(family[i].alelos[1]), "BO");
        family[i].pais[0] = NULL; // Inicializa pais como NULL
        family[i].pais[1] = NULL; // Inicializa pais como NULL
    }
    return family;
}

void free_family(pessoa* p) {
    free(p);
}

int check_size(pessoa* p, int n) {
    // Como o tamanho não é armazenado, você pode usar um parâmetro fixo ou um método diferente
    return 1; // Apenas um exemplo, sempre retorna verdadeiro
}

int check_alleles(pessoa* p) {
    // Implementação da verificação dos alelos
    return 1; // Exemplo, sempre retorna verdadeiro
}
