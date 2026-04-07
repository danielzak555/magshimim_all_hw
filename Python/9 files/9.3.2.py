def my_mp4_playlist(file_path, new_song):
    """This function reads a file and adds the new song to the third row,
    then prints the file content after the modification
    :param file_path: the path to the file
    :type file_path: str
    :param new_song: the name of the new song to add
    :type new_song: str
    :return: None
    :rtype: None
    """
    parts = []

    with open(file_path, 'r') as f:
        content = f.read()
    lines = content.splitlines()
    for line in lines:
        parts.append(line.split(';'))
    
    if len(lines) >= 3:
        parts[2][0] = new_song
        with open(file_path, 'w') as f:
            for part in parts:
                line = part[0] + ';' + part[1] + ';' + part[2] + ';'
                f.write(line)
                if part != parts[-1]:
                    f.write('\n')
    else:
        if len(lines) == 2:
            line = parts[0][0] + ';' + parts[0][1] + ';' + parts[0][2] + ';\n' + parts[1][0] + ';' + parts[1][1] + ';' + parts[1][2] + ';\n' + new_song + ';'
        elif len(lines) == 1:
            line = parts[0][0] + ';' + parts[0][1] + ';' + parts[0][2] + ';\n' + '\n' + new_song + ';'
        else:
            line = ',,,' + new_song + ';'
        with open(file_path, 'w') as f:
            f.write(line)

    with open(file_path, 'r') as f:
        print(f.read())
