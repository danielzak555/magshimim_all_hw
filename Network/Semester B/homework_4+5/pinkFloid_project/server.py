import socket
import data

LIS_PORT = 64999
HELLO = "Welcome to the Pink-Floyd Server!"
QUIT = '8'
GET_ALBUMS = '1'
BYE = "\nThank you for using the Pink-Floyd Server! Bye Bye!\n"
HASHED_PASSWORD = "57431ecd7699fc01db4739a427c6f6350d4ae626b9c93d5df56ec1f95e0c012b"
GOOD_PASS = "PSW@correct password"
BAD_PASS = "PSW@wrong password"

def get_ans_from_data(request_data, request_type):

    pinkfloid = data.data_base()

    def option_1():
        return data.get_albums(pinkfloid)

    def option_2():
        return data.get_songs(pinkfloid, request_data)

    def option_3():
        return data.song_len(pinkfloid, request_data)

    def option_4():
        return data.song_lyr(pinkfloid, request_data)

    def option_5():
        return data.album_by_song(pinkfloid, request_data)

    def option_6():
        return data.song_by_name(pinkfloid, request_data)

    def option_7():
        return data.song_by_word(pinkfloid, request_data)

    functions = {
        '1': option_1,
        '2': option_2,
        '3': option_3,
        '4': option_4,
        '5': option_5,
        '6': option_6,
        '7': option_7
    }

    return functions[request_type]()

def login(client_pass):

    if client_pass == HASHED_PASSWORD:
        return True
    else:
        return False


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(('0.0.0.0', LIS_PORT)) 
    sock.listen(1)#listen for a massage

    password_ok = False
    over = False
    client_req_list = []

    print("running on port 64999... Waiting for a connection...\n")
    client_socket, client_address = sock.accept()#creat socket with client and getting his details
    print(f"Connected with: {client_address}\n")# for us to know the connection is succsesful

    client_socket.sendall(HELLO.encode())

    while(over == False):
        
        if password_ok == False:
            try:
                password = client_socket.recv(1024)
            except Exception as e:
                print("client unexpectadly disconnected")
                break
            client_pass = password.decode()
            password_ok = login(client_pass)
            if password_ok == True:
                client_socket.sendall(GOOD_PASS.encode())
            else:
                client_socket.sendall(BAD_PASS.encode())

        if password_ok == True:
            try:
                request = client_socket.recv(1024)
            except Exception as e:
                print("client unexpectadly disconnected")
                break
        
            request_text = request.decode()
            print("Received request:")
            print(request_text)
            client_req_list = request_text.split('@')
            msg_type = client_req_list[0][2]

            if msg_type != GET_ALBUMS and msg_type != QUIT:
                data_answer = get_ans_from_data(client_req_list[1], msg_type)
            
            elif msg_type == GET_ALBUMS:
                data_answer = get_ans_from_data("", msg_type)

            try:
                if msg_type != QUIT:
                    ser_ans = f"OK{msg_type}@{data_answer}"
                else:
                    ser_ans = f"OK{msg_type}@{BYE}"
                
                client_socket.sendall(ser_ans.encode())#sending back to the client the answer from the server
                if(msg_type == QUIT):   
                    print("client asked to quit")
                    over = True

            except Exception as e:
                print("client unexpectadly disconnected")
                sock.listen(1)
                print("running on port 64999... Waiting for a connection...\n")
                client_socket, client_address = sock.accept()
                print(f"Connected with: {client_address}\n")
                client_socket.sendall(HELLO.encode())


    client_socket.close()
    sock.close()

if __name__ == "__main__":
    main()