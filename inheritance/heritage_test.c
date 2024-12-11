// heritage_test.c

#include <stdio.h>
#include "heritage.h" // Inclua o cabeçalho

// Testes
int main(void) {
    srand(time(0));
    person *p = create_family(3);
    print_family(p, 0);
    printf(check_size(p, 3) == 7 ? "size_true\n" : "size_false\n"); // 7 para 3 gerações
    free_family(p);
    return 0;
}
