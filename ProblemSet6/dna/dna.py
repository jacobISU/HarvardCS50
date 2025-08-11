import csv
import sys


def main():

    # TODO: Check for command-line usage
    validate_arguments(sys.argv)

    # TODO: Read database file into a variable
    database = read_database(sys.argv[1])

    # TODO: Read DNA sequence file into a variable
    dna_sequence = read_dna(sys.argv[2])

    # TODO: Find longest match of each STR in DNA sequence
    results = get_dna_strs(database[0], dna_sequence)
    dna_results = results[0]
    number_of_keys = results[1]

    # TODO: Check database for matching profiles
    find_a_match(database, dna_results, number_of_keys)

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


def validate_arguments(arguments):
    if len(arguments) != 3:
        print("Wrong number of command-line arguments.")
        sys.exit()
    if not arguments[1].endswith('.csv'):
        print("First argument must be a .csv file.")
        sys.exit()
    if not arguments[2].endswith('.txt'):
        print("Second argument must be a .txt file.")
        sys.exit()


def read_database(database_csv):
    database = []
    with open(database_csv, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            database.append(row)
    return database


def read_dna(dna_txt):
    dna_file = open(dna_txt, 'r', encoding=None)
    dna_sequence = dna_file.read()
    dna_file.close()
    return dna_sequence


def get_dna_strs(first_row, dna_sequence):
    dna_results = {}
    number_of_keys = -1  # Starts at -1 to remove the 'name' key from being compared to matches.
    for col in first_row:
        dna_results[col] = str(longest_match(dna_sequence, col))
        number_of_keys += 1

    return [dna_results, number_of_keys]


def find_a_match(database, dna_results, number_of_keys):
    for row in database:
        matches = 0
        name = row['name']
        for key in dna_results:
            if row[key] == dna_results[key]:
                matches += 1
            if matches == number_of_keys:
                print(name)
                return

    print("No match")
    return


main()
