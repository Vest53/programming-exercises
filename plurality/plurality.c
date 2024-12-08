#include <stdio.h>
#include <string.h>

#define MAX_CANDIDATES 9
#define MAX_NAME_LENGTH 50

// Define a estrutura do Candidato
typedef struct
{
    char name[MAX_NAME_LENGTH];
    int votes;
} Candidate;

// Prototipagem das funções
int vote(Candidate candidates[], int candidate_count, char *name);
void print_winner(Candidate candidates[], int candidate_count);

int main()
{
    Candidate candidates[MAX_CANDIDATES];
    int candidate_count;

    // Solicita o número de candidatos
    printf("Informe o número de candidatos (até %d): ", MAX_CANDIDATES);
    if (scanf("%d", &candidate_count) != 1 || candidate_count < 1 ||
        candidate_count > MAX_CANDIDATES)
    {
        printf("Número inválido de candidatos.\n");
        return 1;
    }

    // Inicializa os candidatos
    for (int i = 0; i < candidate_count; i++)
    {
        printf("Informe o nome do candidato %d: ", i + 1);
        scanf("%49s", candidates[i].name); // Limita a entrada
        candidates[i].votes = 0;
    }

    int voter_count;
    printf("Informe o número de eleitores: ");
    if (scanf("%d", &voter_count) != 1)
    {
        printf("Número inválido de eleitores.\n");
        return 1;
    }

    // Votação
    for (int i = 0; i < voter_count; i++)
    {
        char name[MAX_NAME_LENGTH];
        printf("Informe o nome do candidato para votar: ");
        scanf("%49s", name); // Limita a entrada

        if (!vote(candidates, candidate_count, name))
        {
            printf("Voto inválido para %s.\n", name);
        }
    }

    // Mostra os resultados
    printf("\nResultados da eleição:\n");
    for (int i = 0; i < candidate_count; i++)
    {
        printf("%s: %d votos\n", candidates[i].name, candidates[i].votes);
    }

    // Imprime o vencedor
    print_winner(candidates, candidate_count);

    return 0;
}

// Função para registrar um voto
int vote(Candidate candidates[], int candidate_count, char *name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return 1; // Voto válido
        }
    }
    return 0; // Candidato inválido
}

// Função para imprimir o(s) vencedor(es)
void print_winner(Candidate candidates[], int candidate_count)
{
    int max_votes = 0;

    // Encontra o número máximo de votos
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }

    // Imprime todos os candidatos com votos máximos
    printf("Vencedor(es):\n");
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
