import re
from cs50 import get_string

while True:
    text = get_string("Text: ")
    if len(text) > 0:
        break


def count_letters():
    return sum(c.isalpha() for c in text)


def count_words():
    return len(re.findall(r'\b[\w\'-]+\b', text))


def count_sentences():
    # If the next character after ".", "!" and "?" is an uppercase letter then it will be counted as a new sentence
    return len(re.split(r'(?<=[.!?])\s+(?=[A-Z])', text))


def main():
    letters = count_letters()
    words = count_words()
    sentences = count_sentences()

    # Calculate the Coleman-Liau index
    L = float(letters / words * 100)
    S = float(sentences / words * 100)
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Output the grade level
    if (index > 16):
        return ("Grade 16+")
    elif (index < 1):
        return ("Before Grade 1")
    return (f"Grade {index}")


main()
