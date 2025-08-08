WORD_AMOUNT = 100

def get_string(prompt):
    return input(prompt)

def main():
    text = get_string("Text: ")
    letters_sentences = get_letters_and_sentences(text)
    grade = coleman_liau(letters_sentences[0], letters_sentences[1])
    output_reading_level(grade)


def get_letters_and_sentences(text):
    text_length = len(text)

    i = 0
    letters = 0
    words = 0
    sentences = 0

    while (i < text_length):

        if text[i].isspace():
            words += 1
        elif text[i] == "!" or text[i] == "?" or text[i] == ".":
            sentences += 1
        else:
            if text[i].isalpha():
                letters += 1
        i += 1

    words += 1

    # L and S are variables from the Coleman-Liau formula representing Letters and Sentences.
    L = (letters / words) * WORD_AMOUNT
    S = (sentences / words) * WORD_AMOUNT

    return L, S


def coleman_liau(letters, sentences):
    # Coleman-Liau: 0.0588 * L - 0.296 * S - 15.8
    return round(0.0588 * letters - 0.296 * sentences - 15.8)


def output_reading_level(grade):
    if grade >= 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print("Grade", grade)


main()
