def check_win(secret_word, old_letters_guessed):
    """this function gets a secret word and a list of guessed letters and returns True if all the letters in the secret
    word are in the guessed letters list and False otherwise
    :param secret_word: the secret word
    :param old_letters_guessed: the list of guessed letters
    :type secret_word: str
    :type old_letters_guessed: list
    :return: True if all the letters in the secret word are in the guessed letters list and False otherwise
    :rtype: bool
    """
    for letter in secret_word:
        if letter not in old_letters_guessed:
            return False
    return True