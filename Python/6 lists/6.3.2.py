def longest(my_list):
    """will return the longest string in a list
    :param my_list: list of strings
    :type my_list: list
    :return: the longest string in the list
    :rtype: string
    """
    my_list.sort(key=len)
    return my_list[-1]