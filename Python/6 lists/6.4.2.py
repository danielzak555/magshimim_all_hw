def try_update_letter_guessed(letter_guessed, old_letters_guessed):
    """will check if the letter guessed is valid and not was guessed before
    :param letter_guessed: the letter that the user guessed
    :type letter_guessed: string
    :param old_letters_guessed: list of the letters that the user guessed before
    :type old_letters_guessed: list
    :return: if the letter is valid and not was guessed before
    :rtype: bool
    """
    
    guess = letter_guessed.lower()

    if len(guess) == 1 and guess >= "a" and guess <= "z" and guess not in old_letters_guessed:
        old_letters_guessed.append(guess)
        old_letters_guessed.sort()
        return True
    
    else:
        old_letters_guessed.sort()
        print("X")
        print(" -> ".join(old_letters_guessed))
        return False