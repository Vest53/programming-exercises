#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define o número de gerações a serem simuladas
#define GENERATIONS 3

// Define a estrutura para representar uma pessoa
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

// Prototipação de funções
person *create_family(int generations);
void free_family(person *p);
char random_allele(void);
void print_family(person *p, int generation);

// Função principal
int main(void)
{
    // Semeia o gerador de números aleatórios
    srand(time(0));

    // Cria uma nova família com três gerações
    person *p = create_family(GENERATIONS);

    // Imprime a árvore genealógica dos tipos sanguíneos
    print_family(p, 0);

    // Libera a memória
    free_family(p);
}

// Cria uma nova família
person *create_family(int generations)
{
    // Aloca memória para uma nova pessoa
    person *new_person = malloc(sizeof(person));

    // Se não há mais gerações, gera alelos aleatórios
    if (generations == 1)
    {
        new_person->parents[0] = NULL;
        new_person->parents[1] = NULL;
        new_person->alleles[0] = random_allele();
        new_person->alleles[1] = random_allele();
    }
    else
    {
        // Cria dois novos pais recursivamente
        new_person->parents[0] = create_family(generations - 1);
        new_person->parents[1] = create_family(generations - 1);

        // Atribui alelos com base nos pais
        new_person->alleles[0] = new_person->parents[0]->alleles[rand() % 2];
        new_person->alleles[1] = new_person->parents[1]->alleles[rand() % 2];
    }

    // Retorna a nova pessoa criada
    return new_person;
}

// Libera a memória alocada para uma família
void free_family(person *p)
{
    // Caso base: se a pessoa é NULL, retorna
    if (p == NULL)
    {
        return;
    }

    // Libera recursivamente os pais
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Libera a pessoa atual
    free(p);
}

// Gera um alelo aleatório
char random_allele(void)
{
    // Gera um número aleatório entre 0 e 2
    int r = rand() % 3;

    // Retorna o alelo correspondente
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}

// Imprime a árvore genealógica dos tipos sanguíneos
void print_family(person *p, int generation)
{
    // Caso base: se a pessoa é NULL, retorna
    if (p == NULL)
    {
        return;
    }

    // Imprime os alelos da pessoa
    printf("Generation %d: %c%c\n", generation, p->alleles[0], p->alleles[1]);

    // Chama recursivamente para imprimir os pais
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}
