def sequence_del(my_str):
    """Remove all repeated characters in a string.
    :param my_str: a string
    :type my_str: str
    :return: a string with all repeated characters removed
    :rtype: str
    """
    if len(my_str) == 0:
        return my_str
    else:
        new_str = my_str[0]
        for i in range(1, len(my_str)):
            if my_str[i] != my_str[i - 1]:
                new_str += my_str[i]
        return new_str
