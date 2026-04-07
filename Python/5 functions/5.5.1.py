def is_valid_input(letter_guessed):
    """the function checks if the input is valid
    param letter_guessed: the letter the user guessed
    type letter_guessed: string
    return: True if the input is valid, False otherwise
    rtype: bool"""

    guess = letter_guessed

    if len(guess) == 1 and ((guess >= "a" and guess <= "z") or (guess >= "A" and guess <= "Z")):
        return True
    
    else:
        return False 