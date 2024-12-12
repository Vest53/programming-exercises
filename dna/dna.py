import csv
import sys


def longest_match(sequence, subsequence):
    """Retorna o número máximo de vezes que a subsequência se repete consecutivamente na sequência."""
    max_count = 0
    subseq_length = len(subsequence)
    sequence_length = len(sequence)

    for i in range(sequence_length):
        count = 0
        # Continue contando enquanto a subsequência se repetir
        while sequence[i:i + subseq_length] == subsequence:
            count += 1
            i += subseq_length
        max_count = max(max_count, count)

    return max_count


def load_database(filename):
    """Carrega o banco de dados de perfis de DNA a partir de um arquivo CSV."""
    try:
        with open(filename) as file:
            reader = csv.DictReader(file)
            database = []
            for row in reader:
                database.append(row)
        return database
    except FileNotFoundError:
        print(f"Erro: O arquivo {filename} não foi encontrado.")
        sys.exit(1)


def load_sequence(filename):
    """Carrega a sequência de DNA a partir de um arquivo de texto."""
    try:
        with open(filename) as file:
            return file.read().strip()
    except FileNotFoundError:
        print(f"Erro: O arquivo {filename} não foi encontrado.")
        sys.exit(1)


def find_matching_profile(database, str_counts):
    """Encontra o perfil correspondente na base de dados."""
    for profile in database:
        match = True
        for str_name in str_counts:
            # Compare inteiros
            if int(profile[str_name]) != str_counts[str_name]:
                match = False
                break
        if match:
            return profile['name']
    return "No match"


def main():
    # Verifique se os argumentos foram passados corretamente
    if len(sys.argv) != 3:
        print("Uso: python dna.py <database.csv> <sequence.txt>")
        sys.exit(1)

    # Carregar o banco de dados e a sequência
    database = load_database(sys.argv[1])
    sequence = load_sequence(sys.argv[2])

    # Definir os STRs que queremos verificar
    str_names = database[0].keys()
    str_counts = {}

    # Calcular o número máximo de repetições para cada STR
    for str_name in str_names:
        if str_name != 'name':  # Ignorar o campo 'name'
            str_counts[str_name] = longest_match(sequence, str_name)

    # Encontrar o perfil correspondente
    matching_profile = find_matching_profile(database, str_counts)

    # Exibir o resultado
    print(matching_profile)


if __name__ == "__main__":
    main()
