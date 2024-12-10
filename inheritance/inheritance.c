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
int check_size(person *p); // Nova função para verificar o tamanho

int main(void) {
    // Semeia o gerador de números aleatórios
    srand(time(0));

    // Cria uma nova família com três gerações
    person *p = create_family(3);

    // Imprime a árvore genealógica dos tipos sanguíneos
    print_family(p, 0);

    // Verifica o tamanho da família
    printf(check_size(p) == 7 ? "size_true\n" : "size_false\n");

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

    // Se existem gerações, cria pais e herda alelos
    if (generations > 0) {
        p->parents[0] = create_family(generations - 1);
        p->parents[1] = create_family(generations - 1);

        // Define alelos herdados aleatoriamente dos pais
        p->alleles[0] = p->parents[0]->alleles[rand() % 2]; // Alelo de um dos pais
        p->alleles[1] = p->parents[1]->alleles[rand() % 2]; // Alelo de outro pai
    } else {
        // Se não houver mais gerações, define alelos aleatórios
        p->alleles[0] = "ABO"[rand() % 3]; // Alelos podem ser 'A', 'B' ou 'O'
        p->alleles[1] = "ABO"[rand() % 3]; // Alelos podem ser 'A', 'B' ou 'O'
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

int check_size(person *p) {
    if (p == NULL) return 0; // Se não houver pessoa, retorna 0
    // Conta a pessoa atual e soma os pais
    return 1 + check_size(p->parents[0]) + check_size(p->parents[1]);
}
