import random

def check_valid_input(letter_guessed, old_letters_guessed):
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
        return True
    
    else:
        return False
    
def show_hidden_word(secret_word, old_letters_guessed):
    """this function gets a secret word and a list of guessed letters and returns the word with the guessed letters
    and the rest of the letters as underscores
    :param secret_word: the secret word
    :param old_letters_guessed: the list of guessed letters
    :type secret_word: str
    :type old_letters_guessed: lists
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
    
def print_hangman(num_of_tries):
    """the function gets a number of tries and prints the hangman photo accordingly
    :param num_of_tries: the number of tries
    :type num_of_tries: int
    :return: None
    :rtype: None
    """
    HANGMAN_PHOTOS = {0: """
    x-------x""", 1: """
    x-------x
    |
    |
    |
    |
    |""", 2: """
    x-------x
    |       |
    |       0
    |
    |
    |""", 3: """
    x-------x
    |       |
    |       0
    |       |
    |
    |""", 4: """
    x-------x
    |       |
    |       0
    |      /|\\
    |
    |""", 5: """
    x-------x
    |       |
    |       0
    |      /|\\
    |      /
    |""", 6: """
    x-------x
    |       |
    |       0
    |      /|\\
    |      / \\
    |"""}
    print(HANGMAN_PHOTOS[num_of_tries])


def choose_word(file_path, index):
    """the function choses a word from a file
    :param file_path: the path to the file
    :type file_path: str
    :param index: the index of the word
    :type index: int
    :return: a tuple with the length of the file and the word by the index
    :rtype: tuple"""
    with open(file_path, 'r') as f:
        content = f.read()
    words = content.split(" ")
    without_dupes = []
    for word in words:
        if word not in without_dupes:
            without_dupes.append(word)
    while (index > len(words)):
        index -= len(words)
    return (len(without_dupes), words[index - 1])
    

def main():

    print(""" _    _
    | |  | |
    | |__| | __ _ _ __   __ _ _ __ ___   __ _ _ __
    |  __  |/ _' | '_ \ / _' | '_ ' _ \ / _' | '_ \\
    | |  | | (_| | | | | (_| | | | | | | (_| | | | |
    |_|  |_|\__,_|_| |_|\__, |_| |_| |_|\__,_|_| |_|
                                __/ |
                                |___/""")
    print(random.randint(5, 10))

    file_path = input("Enter file path: ")
    index = int(input("Enter index: "))
    word_tuple = choose_word(file_path, index)
    word = word_tuple[1]
    tries = 0
    old_letter_guessed = []
    win = False
    letter = 0
    good_letter = False

    print("\nLet's start!\n")
    print_hangman(tries)
    print(show_hidden_word(word, old_letter_guessed) + "\n")

    while(win == False and tries < 6):
        good_letter = False
        letter = input("Guess a letter: ")
        good_letter = check_valid_input(letter, old_letter_guessed)
        if good_letter == False:
            good_letter = try_update_letter_guessed(letter, old_letter_guessed)
            continue
        old_letter_guessed.append(letter.lower())
        if letter not in word:
            tries += 1
            print(":(\n")
            print_hangman(tries)
            print("\n" + show_hidden_word(word, old_letter_guessed))
            continue
        print(show_hidden_word(word, old_letter_guessed))
        win = check_win(word, old_letter_guessed)
    
    if win:
        print("WIN")
    else:
        print("LOSE")


if __name__ == "__main__":
    main()