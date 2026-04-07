import socket
from datetime import date

LIS_PORT = 9090
FILM_IP = "54.71.128.194"
FILM_PORT = 92
SUB_THE_WORD_YEAR = 5
SUB_THE_WORD_GENRE = 6
MAX_GENRE = 20

def main():
    prx_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)#make a sosket for the proxy
    prx_socket.bind(('0.0.0.0', LIS_PORT)) 
    prx_socket.listen(1)#listen for a massage

    while(True):
        print("Proxy is running on port 9090... Waiting for a connection...\n")

        client_socket, client_address = prx_socket.accept()#creat socket with client and getting his details
        print(f"Connected with: {client_address}\n")# for us to know the connection is succsesful

        request = client_socket.recv(1024)
        request_text = request.decode()
        print("Received request:")
        print(request_text)
        print("\n")
        
        country_index =request_text.find("country")
        year_index = request_text.find("year")
        the_years = request_text[year_index +  SUB_THE_WORD_YEAR: country_index - 1]
        first_year = int(the_years[:the_years.find("-")])
        second_year = int(the_years[the_years.find("-") + 1:])
        current_date = date.today()
        current_year = current_date.year
        
        genre_index = request_text.find("genre")
        the_genre = request_text[genre_index + SUB_THE_WORD_GENRE : year_index - 1]
        
        if(first_year > current_year or second_year > current_year):
            answer = "ERROR#\"one or more of the years is in future!\""
            client_socket.sendall(answer.encode())
 
        elif(len(the_genre) > MAX_GENRE):
            answer = "ERROR#\"the genre is to long!\""
            client_socket.sendall(answer.encode())

        else:
            server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

            server_address = (FILM_IP, FILM_PORT)
            server_socket.connect(server_address)#connecting to the socket
            
            server_socket.sendall(request)

            server_msg = server_socket.recv(1024)
            server_msg = server_msg.decode()

            print("Received request from film:")
            print(server_msg)
            print("\n")


            modified_request = server_msg.replace('name:\"', 'name:\"proxy ')#adding before the name the word "proxy"
            modified_request = modified_request.replace('jpg\"', '.jpg\"')
            print("Modified request:")
            print(modified_request)
            print("\n")


            is_serv_err = server_msg.find("SERVERERROR")
            if(is_serv_err + 1):#because if there is it will be 1 and if not then will be 0 = -1 + 1  :)
                serv_error = server_msg[:server_msg.find('#')]
                modified_request = server_msg.replace(serv_error, "ERROR")


            countries_index = modified_request.find("countries")
            actors_index = modified_request.find("actors")
            countries = modified_request[countries_index : actors_index - 1] #cut the part of the countries
            if(countries.find("France") + 1):
                modified_request = 'ERROR#\"France is banned!\"'
                print(modified_request)

            

            client_socket.sendall(modified_request.encode())#sending back to the client the answer from the server

        client_socket.close()
        server_socket.close()

if __name__ == "__main__":
    main()