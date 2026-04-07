def format_list(my_list):
    """"return a string representation of all of the second elements in the list and the last one in the list and between each word a , and before the last one the word and
    param:my_list: List of words
    type: my_list: list
    return: string
    rtype: str
    """
    even_list = my_list[::2]
    print(even_list)

    if len(my_list) == 1:
        return str(my_list[0]) + "and "

    return ", ".join(even_list[:]) + ", and " + my_list[-1]

def main():
    print(format_list([", "]))

if __name__ == '__main__':
    main()