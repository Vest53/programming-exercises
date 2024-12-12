def main():
    # Solicita o valor do troco ao usuário
    while True:
        try:
            change = float(input("Change owed: "))
            if change < 0:
                print("Please enter a value greater than 0.")
            else:
                break  # Sai do loop se a entrada for válida
        except ValueError:
            print("Invalid input. Please enter a positive number.")

    # Converte o valor de troco para centavos
    change = round(change * 100)

    # Variável para contar as moedas
    coins = 0

    # Denominações disponíveis
    coins_available = [25, 10, 5, 1]

    # Calcula o número mínimo de moedas
    for coin in coins_available:
        while change >= coin:
            change -= coin
            coins += 1

    # Imprime o número mínimo de moedas
    print(coins)

# Chama a função principal
if __name__ == "__main__":
    main()
