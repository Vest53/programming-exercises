import string


def count(text):
    letters = 0
    words = 0
    sentences = 0
    in_word = False

    for char in text:
        # Contar letras
        if char.isalpha():
            letters += 1

        # Contar palavras
        if char in string.whitespace or char == text[-1]:
            if in_word:
                words += 1
                in_word = False  # Fim de uma palavra
        else:
            in_word = True  # Dentro de uma palavra

        # Contar sentenças
        if char in {'.', '!', '?'}:
            sentences += 1

    # Se o último caractere era parte de uma palavra, contar
    if in_word:
        words += 1

    return letters, words, sentences


def calculate_grade(letters, words, sentences):
    # Fórmula de Coleman-Liau
    L = (letters / words) * 100  # Letras por 100 palavras
    S = (sentences / words) * 100  # Sentenças por 100 palavras
    index = 0.0588 * L - 0.296 * S - 15.8  # Calcular o índice

    return round(index)  # Arredondar para o inteiro mais próximo


def main():
    # Solicitar ao usuário que insira o texto
    text = input("Enter the text: ")

    # Contar letras, palavras e sentenças
    letters, words, sentences = count(text)

    # Calcular a nota de legibilidade
    grade = calculate_grade(letters, words, sentences)

    # Exibir o resultado
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


if __name__ == "__main__":
    main()
