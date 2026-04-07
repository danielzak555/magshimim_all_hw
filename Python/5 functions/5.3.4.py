def last_early(my_str):
    last = my_str[-1]
    rest = my_str[:-1]
    last = last.lower()
    rest = rest.lower()
    
    flag = rest.find(last)

    if flag == -1:
        return False
    else:
        return True
    
