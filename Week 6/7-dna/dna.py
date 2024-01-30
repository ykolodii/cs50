import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Your input should match the following: python dna.py database/filename.csv sequence/filename.txt")
        sys.exit(1)

    # Read database file into a variable
    database_file = sys.argv[1]
    with open(database_file, 'r') as db_file:
        db_reader = csv.DictReader(db_file)
        database = list(db_reader)
    
    # Read DNA sequence file into a variable
    sequence_file = sys.argv[2]
    with open(sequence_file, 'r') as seq_file:
        sequence = seq_file.read().strip()

    # Find longest match of each STR in DNA sequence
    strs_from_first_line = db_reader.fieldnames[1:]
    matches = {str: longest_match(sequence, str) for str in strs_from_first_line}

    # Check database for matching profiles
    for row in database:
        if all(int(row[str]) == matches[str] for str in strs_from_first_line):
            print(row['name'])
            return
    
    # If no match found
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
