def arrow(my_char, max_length):
    """Return an arrow of a given length.
    :param my_char: a character
    :type my_char: char
    :param max_length: the length of the arrow
    :type max_length: int
    :return: an arrow of a given length
    :rtype: str
    """
    str = ""
    for i in range(1, max_length + 1):
        str += my_char * i
        str += "\n"
    for i in range(max_length - 1, 0, -1):
        str += my_char * i
        str += "\n"
    str = str[:-1]
    return str
