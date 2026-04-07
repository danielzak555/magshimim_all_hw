def is_greater(my_list, n):
    """return list of numbers greater than n
    :param my_list: list of numbers
    :type my_list: list
    :param n: number to compare
    :type n: int
    :return: list of numbers greater than n
    :rtype: list
    """
    greater = []
    for i in my_list:
        if i > n:
            greater.append(i)
    return greater