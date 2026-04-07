def inverse_dict(my_dict):
    """returns a dictionary with the keys and values of my_dict swapped
    :param my_dict: dictionary
    :type my_dict: dict
    :return: dictionary
    :rtype: dict
    """
    reversed_dict = {}
    for key, value in my_dict.items():
        if value not in reversed_dict:
            reversed_dict[value] = [key]
        else:
            reversed_dict[value].append(key)
        reversed_dict[value] = sorted(reversed_dict[value], key=lambda x: (x[0].isalnum(), x))
    return reversed_dict
def main():
    print(inverse_dict({'ab': 'cd', 'bb': 'cd', 'cc': 'dd', 'dd': '5', '!': '5', '%': '4', '$': '5'}))
if __name__ == '__main__':
    main()
