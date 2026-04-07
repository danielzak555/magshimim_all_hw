import socket
from datetime import datetime, timedelta

SERVER_IP = "34.218.16.79"
SERVER_PORT = 77
MOVE_INDEX = 5
ZERO_STR = "0"
NINE_STR = "9"
NINE_NUMBER = 9
def check_forecast(name, date):
    """
    Connects to a weather server sends a forecast request for a specific city and date,
    and retrieves the temperature and weather description.

    :param name: The name of the city.
    :type name: str
    :param date: The date for the forecast.
    :type date: str
    :return: A tuple containing the temperature and the weather description.
    :rtype: tuple
    """
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    server_address = (SERVER_IP, SERVER_PORT)
    sock.connect(server_address)

    first_checksum = 0
    sec_checksum = 0

    for letter in name:
        first_checksum += ord(letter) - ord('a') + 1

    for num in date:
        if(num >= ZERO_STR and num <= NINE_STR):
            sec_checksum += ord(num) - ord('0')

    sock.recv(1024)# clean the message that the server sending

    msg = f"100:REQUEST:city={name}&date={date}&checksum={first_checksum}.{sec_checksum}"
    sock.sendall(msg.encode())

    server_msg = sock.recv(1024)
    server_msg = server_msg.decode()

    splited_ans = server_msg.split(":")
    text_index = server_msg.find("text")
    temp_index = server_msg.find("temp")

    if(text_index == -1):
        sock.close()
        return (999.0, splited_ans[2])
    else:
        sock.close()
        temprature = server_msg[temp_index + MOVE_INDEX : text_index - 1]
        text = server_msg[text_index + MOVE_INDEX :]
        return (float(temprature), text)


def create_date(forward):
    """
    Creates a date string in based on the current date and a number of days forward.

    :param forward: The number of days to look into the future (0 for today).
    :type forward: int
    :return: The formatted date string.
    :rtype: str
    """
    time = datetime.now() + timedelta(days=forward)
    list = [time.day, time.month, time.year]
    for i in range(0, 3):
        if list[i] <= NINE_NUMBER:
            list[i] = f"0{list[i]}"
        else:
            list[i] = f"{list[i]}"

    return list[0] + "/" + list[1] + "/" + list[2]

def print_answer(date, answer):
    """
    Prints the formatted forecast information for a given date and forecast answer.

    :param date: The date of the forecast.
    :type date: str
    :param answer: A tuple containing the temperature and weather description.
    :type answer: tuple
    :return: None
    :rtype: None
    """
    str_to_print = f"{date}, Temperature: {answer[0]:.1f}, {answer[1]}"
    print(str_to_print)

def main():
    city = input("Enter your city: ")
    choise = int(input("1 - todays forecast\n2 - today and three days forward forecast\nyour choise: "))
    if choise == 1:
        date = create_date(0)
        answer = check_forecast(city, date)
        print_answer(date, answer)

    elif choise == 2:
        for i in range(0, 4):
            date = create_date(i)
            answer = check_forecast(city, date)
            print_answer(date, answer)

    else:
        print("wrong input next time enter 1 or 2 :(")


if __name__ == "__main__":
    main()