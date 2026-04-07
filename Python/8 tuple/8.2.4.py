def sort_anagrams(list_of_strings):
    """this function gets a list of strings and returns a list of lists that contains all the anagrams in the input list
    :param list_of_strings: a list of strings
    :type list_of_strings: list
    :return: a list of lists that contains all the anagrams in the input list
    :rtype: list
    """
    the_list = list_of_strings
    anagrams = []
    group = []
    i = 0   
    for word in the_list:
        group.append(word)
        for other_word in the_list[i + 1:]:
            if sorted(word) == sorted(other_word):
                group.append(other_word)
                the_list.remove(other_word)
        anagrams.append(group)
        group = []
        i += 1
    return anagrams
