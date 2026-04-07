def squared_numbers(start, stop):
    """Return a list of the squares of the numbers from start to stop.
    :param start: the first number in the list
    :type start: int
    :param stop: the last number in the list
    :type stop: int
    :return: a list of the squares of the numbers from start to stop
    :rtype: list
    """
    square = []
    while start <= stop:
        square.append(start ** 2)
        start += 1
    return square