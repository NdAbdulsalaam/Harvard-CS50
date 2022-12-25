# TODO
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) != 1:
        sys.exit("Usage: python readability.py")

    # Get input
    user_input = input("Text: ")

    # Perform counts
    letters = count_letters(user_input)
    words = len(user_input.split())
    sentences = count_sentences(user_input)

    # Outputs the grade level as defined by the Coleman-Liau index
    index = coleman_index(letters, words, sentences)
    if index < 1:
        print("Before Grade 1")
    elif index >= 1 and index <= 16:
        print(f"Grade {index}")
    else:
        print("Grade 16+\n")


def count_letters(user_input):
    counter = 0
    for letter in user_input:
        if letter.isalpha():
            counter += 1
    return counter


def count_sentences(user_input):
    counter = 0
    for letter in user_input:
        if letter in [".", "?", "!"]:
            counter += 1
    return counter


def coleman_index(letters, words, sentences):
    """
    index = 0.0588 * L - 0.296 * S - 15.8
    where L is the average number of letters per 100 words in the text,
    and S is the average number of sentences per 100 words in the text.

    """
    letters_per_100words = letters / words * 100
    sentences_per_100words = sentences / words * 100
    index = round(0.0588 * letters_per_100words - 0.296 * sentences_per_100words - 15.8)
    return index


if __name__ == "__main__":
    main()