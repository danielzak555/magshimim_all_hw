def are_files_equal(file1, file2):
    """Return True if the contents of the files are equal.
    :param file1: string, path to file1
    :type file1: str
    :param file2: string, path to file2
    :type file2: str
    :return: bool
    :rtype: bool
    """
    f1 = open(file1, 'r')
    f2 = open(file2, 'r')
    return f1.read() == f2.read()
