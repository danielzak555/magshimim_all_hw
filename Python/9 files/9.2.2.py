def copy_file_content(source, destination):
    """this function copies the content of one file to another
    :param source: the path to the source file
    :type source: str
    :param destination: the path to the destination file
    :type destination: str
    :return: None
    :rtype: None
    """
    with open(source, 'r') as f:
        with open(destination, 'w') as d:
            d.write(f.read())