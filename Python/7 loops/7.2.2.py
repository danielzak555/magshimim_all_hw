def numbers_letters_count(my_str):
    """Return the number of letters and numbers in a string.
    :param my_str: a string
    :type my_str: str
    :return: the number of letters and numbers in a string
    :rtype: list
    """
    count = [0, 0]
    for i in my_str:
        if i.isdigit():
            count[0] += 1
        else:   
            count[1] += 1
    return count