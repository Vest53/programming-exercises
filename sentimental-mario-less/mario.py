# Função principal
def main():
    while True:
        # Solicita a altura da pirâmide
        height = input("Digite a altura da pirâmide (1-8): ")

        # Tenta converter a entrada para um inteiro
        try:
            height = int(height)
            if height < 1 or height > 8:
                raise ValueError
            break  # Sai do loop se a entrada for válida
        except ValueError:
            print("Por favor, digite um número inteiro entre 1 e 8.")

    # Loop para cada linha da pirâmide
    for i in range(1, height + 1):
        # Imprime os espaços em branco
        print(" " * (height - i), end="")  # Imprime os espaços sem nova linha
        # Imprime os hashes
        print("#" * i)  # Imprime os hashes e pula para a próxima linha

# Chama a função principal
if __name__ == "__main__":
    main()
