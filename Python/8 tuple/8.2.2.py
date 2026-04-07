def sort_prices(list_of_tuples):
    """this function gets a list of tuples and returns a list of tuples sorted by the second element in each tuple
    :param list_of_tuples: a list of tuples
    :type list_of_tuples: list
    :return: a list of tuples sorted by the second element in each tuple
    :rtype: list
    """
    while True:
        swapped = False
        for i in range(len(list_of_tuples) - 1):
            if list_of_tuples[i][1] < list_of_tuples[i + 1][1]:
                list_of_tuples[i], list_of_tuples[i + 1] = list_of_tuples[i + 1], list_of_tuples[i]
                swapped = True
        if not swapped:
            break
    return list_of_tuples


#[('item', 'price'), ('item', 'price'), ('item', 'price')]