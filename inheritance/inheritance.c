#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição do tipo person
typedef struct person {
    struct person *parents[2]; // Dois ponteiros para os pais
    char alleles[2]; // Dois alelos
} person;

// Funções
person *create_family(int generations);
void free_family(person *p);
void print_family(person *p, int generation);

int main(void) {
    // Semeia o gerador de números aleatórios
    srand(time(0));

    // Cria uma nova família com três gerações
    person *p = create_family(3);

    // Imprime a árvore genealógica dos tipos sanguíneos
    print_family(p, 0);

    // Libera a memória
    free_family(p);

    return 0; // Indica sucesso
}

person *create_family(int generations) {
    // Aloca memória para uma nova pessoa
    person *p = malloc(sizeof(person));
    if (p == NULL) {
        return NULL; // Retorna NULL se a alocação falhar
    }

    // Se não existem mais gerações, define alelos aleatórios
    if (generations > 0) {
        // Chama recursivamente para criar os pais
        p->parents[0] = create_family(generations - 1);
        p->parents[1] = create_family(generations - 1);

        // Define alelos aleatórios
        p->alleles[0] = "ABO"[rand() % 3]; // Alelos podem ser 'A', 'B' ou 'O'
        p->alleles[1] = "ABO"[rand() % 3]; // Alelos podem ser 'A', 'B' ou 'O'
    } else {
        // Se não houver mais gerações, define alelos como 'O' por padrão
        p->alleles[0] = 'O';
        p->alleles[1] = 'O';
        p->parents[0] = NULL; // Sem pais
        p->parents[1] = NULL; // Sem pais
    }

    return p; // Retorna o ponteiro para a nova pessoa
}

void free_family(person *p) {
    if (p == NULL) return; // Verifica se o ponteiro é NULL

    // Chama recursivamente a função para liberar os pais
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Libera a memória da pessoa atual
    free(p);
}

void print_family(person *p, int generation) {
    if (p == NULL) return; // Verifica se o ponteiro é NULL

    // Imprime os alelos da pessoa atual
    printf("Geração %d: Tipo sanguíneo: %c%c\n", generation, p->alleles[0], p->alleles[1]);

    // Chama recursivamente para imprimir os pais
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}
