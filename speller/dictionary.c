#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

#define LENGTH 45 // Máximo de caracteres em uma palavra
#define N 26 // Número de buckets

typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
} node;

node *table[N]; // Tabela hash
unsigned int word_count = 0; // Contador de palavras

bool load(const char *dictionary) {
    FILE *file = fopen(dictionary, "r");
    if (file == NULL) {
        return false; // Retorna falso se o arquivo não puder ser aberto
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%45s", word) != EOF) {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL) {
            return false; // Retorna falso se a alocação falhar
        }
        strcpy(new_node->word, word);
        new_node->next = NULL;

        unsigned int index = hash(word);
        new_node->next = table[index];
        table[index] = new_node;
        word_count++;
    }
    fclose(file);
    return true; // Retorna verdadeiro se carregado com sucesso
}

bool check(const char *word) {
    unsigned int index = hash(word);
    node *cursor = table[index];

    while (cursor != NULL) {
        if (strcasecmp(cursor->word, word) == 0) {
            return true; // Palavra encontrada
        }
        cursor = cursor->next;
    }
    return false; // Palavra não encontrada
}

unsigned int size(void) {
    return word_count; // Retorna a contagem de palavras
}

bool unload(void) {
    for (int i = 0; i < N; i++) {
        node *cursor = table[i];
        while (cursor != NULL) {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp); // Libera cada nó
        }
    }
    return true; // Retorna verdadeiro após liberar toda a memória
}

unsigned int hash(const char *word) {
    return tolower(word[0]) - 'a'; // Simples hash baseado na primeira letra
}
