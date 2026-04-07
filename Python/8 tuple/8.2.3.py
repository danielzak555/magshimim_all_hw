def mult_tuple(tuple1, tuple2):
    """this function gets two tuples and returns a new tuple with all tuple pair combinations that you can make from the
    two tuples
    :param tuple1: a tuple
    :type tuple1: tuple
    :param tuple2: a tuple
    :type tuple2: tuple
    :return: a new tuple with all tuple pair combinations that you can make from the two tuples
    :rtype: tuple
    """
    combinations = []
    for i in tuple1:
        for j in tuple2:
            combinations.append((i, j))
    for j in tuple1:
        for i in tuple2:
            combinations.append((i, j))
    return tuple(combinations)