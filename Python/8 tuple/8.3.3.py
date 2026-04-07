def count_chars(my_str):
    """returns a dictionary with the count of each character in my_str
    :param my_str: string
    :type my_str: str
    :return: dictionary
    :rtype: dict
    """
    the_dict = {}
    was_here = []
    for char in my_str:
        if char in was_here or char == ' ':
            continue
        was_here.append(char)
        the_dict[char] = my_str.count(char)
    return the_dict