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
    print(HANGMAN_PHOTOS[num_of_tries - 1])