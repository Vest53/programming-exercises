#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define HEADER_SIZE 44

// Função para alterar o volume
void change_volume(const char *input_file, const char *output_file, float volume_factor)
{
    FILE *infile = fopen(input_file, "rb");
    if (infile == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada.\n");
        exit(1);
    }

    // Ler o cabeçalho
    uint8_t header[HEADER_SIZE];
    fread(header, sizeof(uint8_t), HEADER_SIZE, infile);

    // Criar e abrir o arquivo de saída
    FILE *outfile = fopen(output_file, "wb");
    if (outfile == NULL)
    {
        fclose(infile);
        fprintf(stderr, "Erro ao criar o arquivo de saída.\n");
        exit(1);
    }

    // Escrever o cabeçalho no novo arquivo
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, outfile);

    // Ler e modificar as amostras de áudio
    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, infile) == 1)
    {
        // Alterar o volume
        sample *= volume_factor;

        // Garantir que a amostra permaneça dentro dos limites de 16 bits
        if (sample > 32767)
        {
            sample = 32767;
        }
        else if (sample < -32768)
        {
            sample = -32768;
        }

        // Escrever a amostra modificada no arquivo de saída
        fwrite(&sample, sizeof(int16_t), 1, outfile);
    }

    // Fechar os arquivos
    fclose(infile);
    fclose(outfile);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Uso: %s <arquivo_entrada.wav> <arquivo_saida.wav> <fator_volume>\n",
                argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];
    float volume_factor = atof(argv[3]);

    // Alterar o volume
    change_volume(input_file, output_file, volume_factor);

    printf("Volume modificado com sucesso!\n");
    return 0;
}
