#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Para time()

// Definição do tipo pessoa
typedef struct {
    char alelo1[3];
    char alelo2[3];
} pessoa;

// Funções que você precisa implementar
pessoa* create_family(int n);
void free_family(pessoa* p);
int check_size(pessoa* p, int n);
int check_alleles(pessoa* p);

int main() {
    srand(time(0)); // Corrigido para usar time()

    pessoa *p = create_family(3); // Chama a função para criar uma família

    // Verifica o tamanho e os alelos
    printf(check_size(p, 3) ? "size_true " : "size_false ");
    printf(check_alleles(p) ? "allele_true" : "allele_false");

    // Libera a memória
    free_family(p);

    return 0;
}

// Implementações das funções (exemplo)
pessoa* create_family(int n) {
    pessoa *family = malloc(n * sizeof(pessoa));
    // Inicialização de alelos aleatórios (exemplo)
    for (int i = 0; i < n; i++) {
        snprintf(family[i].alelo1, sizeof(family[i].alelo1), "AO");
        snprintf(family[i].alelo2, sizeof(family[i].alelo2), "BO");
    }
    return family;
}

void free_family(pessoa* p) {
    free(p);
}

int check_size(pessoa* p, int n) {
    return sizeof(p) / sizeof(pessoa) == n; // Apenas um exemplo
}

int check_alleles(pessoa* p) {
    // Implementação da verificação dos alelos
    return 1; // Exemplo, sempre retorna verdadeiro
}
