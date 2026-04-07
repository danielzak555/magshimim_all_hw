def show_hidden_word(secret_word, old_letters_guessed):
    """this function gets a secret word and a list of guessed letters and returns the word with the guessed letters
    and the rest of the letters as underscores
    :param secret_word: the secret word
    :param old_letters_guessed: the list of guessed letters
    :type secret_word: str
    :type old_letters_guessed: list
    :return: the word with the guessed letters and the rest of the letters as underscores
    :rtype: str
    """
    word = ""
    for letter in secret_word:
        if letter in old_letters_guessed:
            word += letter + " "
        else:
            word += "_ "
    return word[:-1]