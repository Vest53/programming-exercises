#include <stdio.h>
#include "inheritance.c" // Inclua o cabeçalho correto

// Testes
void run_tests() {
    person *p = create_family(3);
    printf(check_size(p, 3) == 7 ? "size_true\n" : "size_false\n"); // 7 para 3 gerações
    free_family(p);
}

int main() {
    run_tests();
    return 0;
}
