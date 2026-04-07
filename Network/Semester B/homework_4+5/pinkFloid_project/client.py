import socket
import hashlib

SERVER_PORT = 64999
SERVER_IP = "127.0.0.1"
MOVE_7_FRW = 7
MOVE_2_BCK = 2
QUIT = 8
OP1 = 1

def main():
    ask_dic = {2: "Enter album name: ", 3: "Enter song name: ", 4: "Enter song name: ", 5: "Enter song: ", 6: "Enter text: ", 7: "Enter text: "}
    ans_dic = {1: "The albums list:", 2: "The songs in the album:", 3: "The song length:", 4: "The song lyrics:", 5: "The album with this song is:", 6: "The list of songs:", 7: "The list of songs:"}
    ser_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    server_address = (SERVER_IP, SERVER_PORT)
    ser_sock.connect(server_address)
    over = 0
    print((ser_sock.recv(1024)).decode() + "\n")
    password_ok = False

    while(over != QUIT):
        if password_ok == False:
            try:
                password = input("Please enter password: ")
                hashed_pass = hashlib.sha256(password.encode()).hexdigest()
                ser_sock.sendall(hashed_pass.encode())
                pass_ans = ser_sock.recv(1024).decode()
                if "wrong" not in pass_ans:
                    password_ok = True
            except Exception as e:
                print("server disconected")
                break
        if password_ok:
            try:
                print("""1 Get Albums\n2 Get Album Songs\n3 Get Song Length\n4 Get Song Lyrics\n5 Get Song Album\n6 Search Song by Name\n7 Search Song by Lyrics\n8 Quit\n""")
                choise = int(input("Enter_number: "))
                if(choise > QUIT or choise < OP1):
                    while(choise > QUIT or choise < OP1):
                        choise = int(input("Enter_number: "))
            except Exception as e:
                print(f"The Error: {e}")
                continue

            if(choise == OP1 or choise == QUIT):
                get_msg = f"GT{choise}@"
            else:
                what_to_ask = ask_dic[choise]
                additional = input(what_to_ask)
                get_msg = f"GT{choise}@{additional}"

            try:
                ser_sock.sendall(get_msg.encode())
                server_ans = ser_sock.recv(1024)

            except Exception as e:
                print("server disconnected :(")
                break
            
            server_ans = server_ans.decode()
            server_ans_list = server_ans.split('@')
            if choise != QUIT:    
                print(ans_dic[choise])
            print(server_ans_list[1])
            
            if(choise == QUIT):
                over = QUIT 

    ser_sock.close()

if __name__ == "__main__":
    main()