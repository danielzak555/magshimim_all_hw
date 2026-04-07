def are_lists_equal(list1, list2):
    """will check if equals
    param list1: list of something
    type list1: list
    param list2: list of something
    type list2: list
    return: True if equal, False if not
    rtype: bool
    """
    list1.sort()
    list2.sort()
    if list1 == list2:
        return True
    else:
        return False
