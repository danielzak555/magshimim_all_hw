def data_base():
    
    pink_floid = []
    album_name = ""
    album_year = ""
    album = {}
    song = {}
    song_name = ""
    writers = []
    time = ""
    lyrics = []

    file_path = "Pink_Floyd_DB.txt"

    with open(file_path, 'r') as file:
        for line in file:
            if line[0] == '#':
                parts = line[1:].split("::")
                
                album_name = parts[0]
                album_year = parts[1].strip('\n')
                
                album = {"album_name": album_name,"year": album_year,"songs": []}
                
                pink_floid.append(album)

            elif line[0] == '*':
                parts = line[1:].split("::")

                song_name = parts[0]
                writers = parts[1].split(",")
                time = parts[2]
                lyrics = parts[3].split(' ')
                
                song = {"song_name": song_name,"writers": writers,"time": time,"lyrics": lyrics}

                album["songs"].append(song)
            else:
                new_word = line[:].split(' ')
                
                song["lyrics"] += new_word

    return pink_floid

def get_albums(pinkfloid):
    
    albums = []
    for album in pinkfloid:
        albums.append(album["album_name"])
    return ', '.join(albums) + '\n'

def get_songs(pinkfloid, name_of_album):
    
    list_of_songs = []
    for album in pinkfloid:
        if album["album_name"] == name_of_album:
            for song in album["songs"]:
                list_of_songs.append(song["song_name"])
    return ', '.join(list_of_songs) + '\n'

def song_len(pinkfloid, name_of_song):

    len = ""
    for album in pinkfloid:
        for song in album["songs"]:
            if song["song_name"] == name_of_song:
                len = song["time"]
    return len + '\n'

def song_lyr(pinkfloid, name_of_song):

    lyr = ""
    for album in pinkfloid:
        for song in album["songs"]:
            if song["song_name"] == name_of_song:
                for word in song["lyrics"]:        
                    if '\n' in word:
                        lyr += word
                    else:
                        lyr += word + " "

    return lyr

def album_by_song(pinkfloid, name_of_song):

    name_of_album = ""
    for album in pinkfloid:
        for song in album["songs"]:
            if song["song_name"] == name_of_song:
                name_of_album = album["album_name"]
    return name_of_album + '\n'

def song_by_name(pinkfloid, name):
    
    list_of_songs = []
    big_name = name.capitalize()
    for album in pinkfloid:
        for song in album["songs"]:
            if name in song["song_name"] or big_name in song["song_name"]:
                list_of_songs.append(song["song_name"])
    return ', '.join(list_of_songs) + '\n'

def song_by_word(pinkfloid, word):

    list_of_songs = []
    for album in pinkfloid:
        for song in album["songs"]:
            found = False
            for element in song["lyrics"]:
                if word in element and found == False:
                    list_of_songs.append(song["song_name"])
                    found = True
    return ', '.join(list_of_songs) + '\n'