def count_letters(text):
    # count the number of letters
    cnt = 0
    for c in text:
        if c.isalpha():
            cnt += 1
    return cnt


def count_sentences(text):
    # count the number of sentences
    cnt = 0
    for c in text:
        if c in ['!', '.', '?']:
            cnt += 1
    return cnt


def main():
    # get user input
    text = input("Text: ")

    # count the number of letters
    num_letter = count_letters(text)

    # count the number of words
    words = text.split()
    num_word = len(words)

    # count the number of sentences
    num_sentence = count_sentences(text)

    # apply Coleman-Liau formula
    L = num_letter / num_word * 100
    S = num_sentence / num_word * 100
    index = 0.0588 * L - 0.296 * S - 15.8

    # evaluate the Grade
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


if __name__ == '__main__':
    main()

