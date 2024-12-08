#include <stdio.h>
#include <string.h>
#include "plurality.c"  // Inclui a funcionalidade principal

#define MAX_CANDIDATES 9

int main(int argc, char *argv[]) {
    Candidate candidates[MAX_CANDIDATES];
    int candidate_count = 3; // Exemplo de configuração de candidatos

    // Inicializa os candidatos
    strcpy(candidates[0].name, "Alice");
    candidates[0].votes = 0;

    strcpy(candidates[1].name, "Bob");
    candidates[1].votes = 0;

    strcpy(candidates[2].name, "Charlie");
    candidates[2].votes = 0;

    // Exemplo de votação
    vote(candidates, candidate_count, "Alice");  // Voto válido
    vote(candidates, candidate_count, "Bob");    // Voto válido
    vote(candidates, candidate_count, "Alice");  // Voto válido
    vote(candidates, candidate_count, "David");   // Voto inválido

    // Imprime os resultados
    printf("Votos:\n");
    printf("Alice: %d\n", candidates[0].votes);
    printf("Bob: %d\n", candidates[1].votes);
    printf("Charlie: %d\n", candidates[2].votes);

    // Imprime o vencedor
    print_winner(candidates, candidate_count);

    return 0;
}
