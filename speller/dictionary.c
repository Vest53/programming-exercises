// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

#define N 26 // Número de buckets

node *table[N]; // Tabela hash
unsigned int word_count = 0; // Contador de palavras


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
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
}

// Hashes word to a number
unsigned int hash(const char *word)
{
  unsigned int hash(const char *word) {
    return tolower(word[0]) - 'a'; // Simples hash baseado na primeira letra
}
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
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


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
  unsigned int size(void) {
    return word_count; // Retorna a contagem de palavras
}
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
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
}
