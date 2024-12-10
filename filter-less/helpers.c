#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1) // Alinhamento de 1 byte

typedef struct {
    uint16_t bfType;      // Tipo do arquivo
    uint32_t bfSize;      // Tamanho do arquivo em bytes
    uint16_t bfReserved1; // Reservado
    uint16_t bfReserved2; // Reservado
    uint32_t bfOffBits;   // Offset até os dados da imagem
} BITMAPFILEHEADER;

typedef struct {
    uint32_t biSize;          // Tamanho da estrutura
    int32_t  biWidth;         // Largura da imagem
    int32_t  biHeight;        // Altura da imagem
    uint16_t biPlanes;        // Número de planos
    uint16_t biBitCount;      // Número de bits por pixel
    uint32_t biCompression;    // Compressão
    uint32_t biSizeImage;     // Tamanho da imagem
    int32_t  biXPelsPerMeter;  // Resolução horizontal
    int32_t  biYPelsPerMeter;  // Resolução vertical
    uint32_t biClrUsed;       // Cores na paleta
    uint32_t biClrImportant;   // Cores importantes
} BITMAPINFOHEADER;

#pragma pack(pop)

void create_bmp(const char *filename, int width, int height, int **matrix) {
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;

    // Inicializando cabeçalhos
    bfh.bfType = 0x4D42; // 'BM'
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    bfh.bfSize = bfh.bfOffBits + (width * height * 3); // 3 bytes por pixel (RGB)

    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = width;
    bih.biHeight = height;
    bih.biPlanes = 1;
    bih.biBitCount = 24; // 24 bits por pixel (RGB)
    bih.biCompression = 0; // Sem compressão
    bih.biSizeImage = 0; // Pode ser 0 para imagens não comprimidas
    bih.biXPelsPerMeter = 2835; // 72 DPI
    bih.biYPelsPerMeter = 2835; // 72 DPI
    bih.biClrUsed = 0; // Usar toda a paleta
    bih.biClrImportant = 0; // Todas as cores são importantes

    // Criando o arquivo BMP
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Erro ao criar o arquivo BMP.\n");
        exit(1);
    }

    // Escrevendo cabeçalhos no arquivo
    fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, file);
    fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, file);

    // Criando a imagem (invertendo a matriz para corresponder à ordem correta)
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            uint8_t color = matrix[y][x] ? 0 : 255; // Preto se 1, branco se 0
            fwrite(&color, sizeof(uint8_t), 1, file); // Blue
            fwrite(&color, sizeof(uint8_t), 1, file); // Green
            fwrite(&color, sizeof(uint8_t), 1, file); // Red
        }
    }

    fclose(file);
}

int main() {
    // Exemplo de matriz 5x5
    int width = 5;
    int height = 5;
    int **matrix = malloc(height * sizeof(int *));
    for (int i = 0; i < height; i++) {
        matrix[i] = malloc(width * sizeof(int));
    }

    // Preenchendo a matriz (exemplo de imagem)
    int example_matrix[5][5] = {
        {0, 1, 1, 1, 0},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0}
    };

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            matrix[i][j] = example_matrix[i][j];
        }
    }

    // Criar o arquivo BMP
    create_bmp("output.bmp", width, height, matrix);

    // Liberar a memória
    for (int i = 0; i < height; i++) {
        free(matrix[i]);
    }
    free(matrix);

    printf("Arquivo BMP criado com sucesso!\n");
    return 0;
}
