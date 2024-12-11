// heritage.h

#ifndef HERITAGE_H
#define HERITAGE_H

typedef struct person {
    struct person *parents[2];
    char alleles[2];
} person;

person *create_family(int generations);
void free_family(person *p);
void print_family(person *p, int generation);
int check_size(person *p, int n); // Declaração da função

#endif // HERITAGE_H
