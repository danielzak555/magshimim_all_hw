def extend_list_x(list_x, list_y):
    """will add the elements of list_y to the start of list_x without using the + operator or extend method
    param: list_x: List of somthing
    type: list_x: list
    param: list_y: List of somthing
    type: list_y: list
    return: list_x with list_y added to the start
    rtype: list
    """
    list_x[:0] = list_y
    return list_x