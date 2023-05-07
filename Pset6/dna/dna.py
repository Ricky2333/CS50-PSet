import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit()

    # TODO: Read database file into a variable
    database = []
    database_header = []
    with open(sys.argv[1], "r") as file:
        # get the header(STRs) of database
        database_header = file.readline().strip().split(",")[1:]
        file.seek(0)
        # get the database
        reader = csv.DictReader(file)
        for person in reader:
            database.append(person)
        # line 24 can replace line 21-22
        # database = list(reader)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        seq = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    cur_record = {}
    for subseq in database_header:
        cur_record[subseq] = longest_match(seq, subseq)

    # TODO: Check database for matching profiles
    for record in database:
        flag = True
        for key in cur_record:
            if str(cur_record[key]) != record[key]:
                flag = False
        if flag == True:
            print(record["name"])
            return
    print("No match")


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


main()
