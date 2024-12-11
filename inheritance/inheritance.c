// heritage.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heritage.h" // Inclua o cabeçalho

person *create_family(int generations) {
    person *new_person = malloc(sizeof(person));
    if (new_person == NULL) {
        return NULL;
    }

    if (generations > 1) {
        new_person->parents[0] = create_family(generations - 1);
        new_person->parents[1] = create_family(generations - 1);
        new_person->alleles[0] = new_person->parents[0]->alleles[rand() % 2];
        new_person->alleles[1] = new_person->parents[1]->alleles[rand() % 2];
    } else {
        new_person->parents[0] = NULL;
        new_person->parents[1] = NULL;
        new_person->alleles[0] = "ABO"[rand() % 3];
        new_person->alleles[1] = "ABO"[rand() % 3];
    }
    return new_person;
}

void free_family(person *p) {
    if (p == NULL) return;
    free_family(p->parents[0]);
    free_family(p->parents[1]);
    free(p);
}

void print_family(person *p, int generation) {
    if (p == NULL) return;
    printf("Geração %d: Tipo sanguíneo: %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

int check_size(person *p, int n) {
    if (p == NULL) return 0;
    return 1 + check_size(p->parents[0], n) + check_size(p->parents[1], n);
}


