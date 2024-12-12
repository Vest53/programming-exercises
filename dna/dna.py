import csv

def longest_match(sequence, subsequence):
    max_count = 0
    subseq_length = len(subsequence)
    sequence_length = len(sequence)

    for i in range(sequence_length):
        count = 0
        while sequence[i:i + subseq_length] == subsequence:
            count += 1
            i += subseq_length
        max_count = max(max_count, count)

    return max_count

def load_database(filename):
    with open(filename) as file:
        reader = csv.DictReader(file)
        database = []
        for row in reader:
            database.append(row)
    return database

def load_sequence(filename):
    with open(filename) as file:
        return file.read().strip()

def find_matching_profile(database, str_counts):
    for profile in database:
        match = True
        for str_name in str_counts:
            if int(profile[str_name]) != str_counts[str_name]:
                match = False
                break
        if match:
            return profile['name']
    return "No match"

def main():
    # Carregar o banco de dados e a sequência
    database = load_database("database.csv")
    sequence = load_sequence("sequence.txt")

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
