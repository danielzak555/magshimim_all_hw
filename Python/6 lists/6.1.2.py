def shift_left(my_list):
    """
    Given a list, return a new list with the elements shifted left by one index.
    param:my_list: List of somthing
    type: my_list: list
    return: List of somthing
    rtype: list
    """
    return my_list[1:] + my_list[:1]