#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512       // Tamanho do bloco de leitura
#define JPEG_HEADER 0xffd8ff // Cabeçalho JPEG

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Verifica se o usuário forneceu o nome do arquivo
    if (argc != 2)
    {
        fprintf(stderr, "Uso: ./recover <cartão de memória>\n");
        return 1;
    }

    // Abre o arquivo de entrada
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", argv[1]);
        return 2;
    }

    BYTE buffer[BLOCK_SIZE]; // Buffer para armazenar blocos lidos
    FILE *img = NULL;        // Ponteiro para a imagem JPEG
    int jpg_count = 0;       // Contador de JPEGs encontrados

    // Loop para ler o cartão de memória em blocos
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // Verifica se encontramos um cabeçalho JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {

            // Se já tivermos aberto uma imagem, feche-a
            if (img != NULL)
            {
                fclose(img);
            }

            // Cria um novo arquivo JPEG
            char filename[8];
            sprintf(filename, "%03d.jpg", jpg_count);
            img = fopen(filename, "w");

            if (img == NULL)
            {
                fprintf(stderr, "Erro ao criar o arquivo %s.\n", filename);
                fclose(card);
                return 3;
            }

            jpg_count++;
        }

        // Se uma imagem JPEG estiver aberta, escreva os dados
        if (img != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }
    }

    // Fecha os arquivos abertos
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);

    return 0; // Indica sucesso
}
