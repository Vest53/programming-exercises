#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1) // Alinhamento de 1 byte

typedef struct
{
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BITMAPFILEHEADER;

typedef struct
{
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BITMAPINFOHEADER;

#pragma pack(pop)

void create_bmp(const char *filename, int width, int height, int **matrix)
{
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;

    // Inicializando cabeçalhos
    bfh.bfType = 0x4D42;
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    bfh.bfSize = bfh.bfOffBits + (width * height * 3);

    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = width;
    bih.biHeight = height;
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = 0;
    bih.biSizeImage = 0;
    bih.biXPelsPerMeter = 2835;
    bih.biYPelsPerMeter = 2835;
    bih.biClrUsed = 0;
    bih.biClrImportant = 0;

    // Criando o arquivo BMP
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        fprintf(stderr, "Erro ao criar o arquivo BMP.\n");
        exit(2); // Retornando 2 para indicar erro
    }
    printf("Arquivo BMP criado com sucesso!\n");

    // Escrevendo cabeçalhos no arquivo
    if (fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, file) != 1 ||
        fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, file) != 1)
    {
        fprintf(stderr, "Erro ao escrever cabeçalhos no arquivo BMP.\n");
        fclose(file);
        exit(2); // Retornando 2 para indicar erro
    }

    // Criando a imagem
    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            uint8_t color = matrix[y][x] ? 0 : 255;
            if (fwrite(&color, sizeof(uint8_t), 1, file) != 1 ||
                fwrite(&color, sizeof(uint8_t), 1, file) != 1 ||
                fwrite(&color, sizeof(uint8_t), 1, file) != 1)
            {
                fprintf(stderr, "Erro ao escrever dados de pixel no arquivo BMP.\n");
                fclose(file);
                exit(2); // Retornando 2 para indicar erro
            }
        }
    }

    fclose(file);
}

int main()
{
    int width = 5;
    int height = 5;

    // Alocando a matriz
    int **matrix = malloc(height * sizeof(int *));
    if (matrix == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória para a matriz.\n");
        return 2; // Retornando 2 para indicar erro
    }

    for (int i = 0; i < height; i++)
    {
        matrix[i] = malloc(width * sizeof(int));
        if (matrix[i] == NULL)
        {
            fprintf(stderr, "Erro ao alocar memória para a linha %d.\n", i);
            for (int j = 0; j < i; j++)
            {
                free(matrix[j]);
            }
            free(matrix);
            return 2; // Retornando 2 para indicar erro
        }
    }

    // Preenchendo a matriz
    int example_matrix[5][5] = {
        {0, 1, 1, 1, 0}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {0, 1, 1, 1, 0}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            matrix[i][j] = example_matrix[i][j];
        }
    }

    // Criar o arquivo BMP
    create_bmp("output.bmp", width, height, matrix);

    // Liberar a memória
    for (int i = 0; i < height; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    printf("Arquivo BMP criado com sucesso!\n");
    return 0;
}
