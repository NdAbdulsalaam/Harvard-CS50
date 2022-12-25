import csv
import sys


def main():
    # TODO: Check for command-line usage
    # print(f"total argv: {len(sys.argv)}")
    if len(sys.argv) != 3:
        sys.exit("Usage: dna.py DATA.CSV SEQUENCE.TXT")

    dna_database = sys.argv[1]
    sequence_file = sys.argv[2]

    # TODO: Read database file into a variable
    with open(dna_database, "r") as file:
        database = csv.DictReader(file)
        STRs = database.fieldnames[1:]
        # print(f"dna_database: {STRs}")

    # TODO: Read DNA sequence file into a variable
    with open(sequence_file, "r") as file:
        sequence = file.read()
        # print(f"sequence: {sequence}")

    # TODO: Find longest match of each STR in DNA sequence
    dna_count = {}
    for STR in STRs:
        dna_count[STR] = longest_match(sequence, STR)

    # TODO: Check database for matching profiles
    with open(dna_database, "r") as file:
        database = csv.DictReader(file)
        person = ""
        for row in database:
            if match(STRs, dna_count, row):
                person = row["name"]
                print(person)
        if len(person) == 0:
            print("No match")


def match(STRs, dna_count, row):
    for STR in STRs:
        if dna_count[STR] != int(row[STR]):
            return False
    return True


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)
    # print(f"first {subsequence_length, sequence_length}")

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
        # print(count)
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


if __name__ == "__main__":
    main()
