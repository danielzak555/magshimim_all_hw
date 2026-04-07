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
    