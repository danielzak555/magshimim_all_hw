def seven_boom(end_number):
    """Return a list of numbers from 0 to end_number, but with a twist.
    :param end_number: the last number in the list
    :type end_number: int
    :return: a list of numbers from 0 to end_number, but with a twist
    :rtype: list
    """
    seven = []
    for i in range(end_number + 1):
        if '7' in str(i) or i % 7 == 0:
            seven.append('BOOM')
        else:
            seven.append(i)
    return seven