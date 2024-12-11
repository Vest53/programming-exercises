#include <stdio.h>
#include "inheritance.c" // Inclua o cabeçalho correto

// Testes
int main() {
    // Criar uma família e verificar o tamanho
    person *p = create_family(3);
    printf(check_size(p, 3) == 7 ? "size_true\n" : "size_false\n"); // 7 para 3 gerações
    free_family(p); // Libera a memória
    return 0;
}
