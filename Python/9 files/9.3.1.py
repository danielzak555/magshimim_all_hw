def my_mp3_playlist(file_path):
    """this function reads a file and returns a tuple with the longest song and the amount of song and the most pupular artist on the list
    :param file_path: the path to the file containing the playlist
    :type file_path: str
    :return: tuple
    :rtype: tuple
    """
    f = open(file_path, 'r')
    content = f.read()
    list = content.replace('\n', ',').split(';')
    most_popular= ""
    max_appeared= 0
    max_time = 0
    count_songs = len(list) // 3
    longest_song = ""
    
    artists = []
    for i in range(1, len(list), 3):
        if i < len(list):
            artists.append(list[i])
    
    for artist in artists:
            count = artists.count(artist)
            if count > max_appeared:
                max_appeared = count
                most_popular = artist

    for i in range(0, len(list), 3):
        if i+2 < len(list):
            time_parts = list[i+2].split(':')
            if len(time_parts) == 2:
                minutes = int(time_parts[0])
                seconds = int(time_parts[1])
                total_seconds = minutes * 60 + seconds
                
                if total_seconds > max_time:
                    max_time = total_seconds
                    longest_song = list[i]
    f.close()
    return (longest_song, count_songs, most_popular)
