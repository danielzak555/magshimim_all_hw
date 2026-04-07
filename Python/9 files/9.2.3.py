def who_is_missing(file_name):
    """this function returns the missing number in a sequence
    :param file_name: the path to the file containing the sequence
    :type file_name: str
    :return: int
    :rtype: int
    """
    COMMA = ','
    list_num = []
    missing = 0
    with open(file_name, 'r') as f:
        numbers = f.read().split(COMMA)
        for num in numbers:
            list_num.append(int(num))
        list_num.sort()
        for i in range(1, list_num[-1]+1):
            if i not in list_num:
                missing = i
                break
    
    file = open("found.txt", 'w')
    file.write(str(missing))
    file.close()

    return missing
