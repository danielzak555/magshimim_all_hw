from scapy.all import *
from scapy.all import sniff

TRUE = True
FALSE = False
HTTP = " HTTP"
GET = "GET "
GET_LEN = 4

def filter_the_dns(the_packet):
    """
    the fun filter the DNS packkets from the sniff
    :param packet: packet from the sniff
    :type packet: packet
    :return: FALSE is not dns, TRUE if its dns
    :rtype: bool
    """
    if DNS in the_packet and the_packet[DNS].ancount > 0:
        for record in the_packet[DNS].an:
            if record.type == 1:
                return TRUE
    return FALSE

def print_dns(the_packet):
    """
    the fun prints the ip and domain from the DNS
    :param packet: packet from the sniff
    :type packet: packet
    :return: none
    """
    ip = ''
    for record in the_packet[DNS].an:
        if record.type == 1:
            ip = record.rdata
    dmn = the_packet[DNS].qd.qname.decode()
    print("domain: "+ dmn + "\nip: " + ip)

def filter_the_weather(the_packet):
    """
    the fun filtering the "weather client" packets 
    :param packet: packet from the sniff
    :type packet: packet
    :return: TRUE if the packet is weather client, if not then FALSE
    :rtype: bool
    """
    if IP in the_packet and the_packet[IP].src == '34.218.16.79' and Raw in the_packet and 'Welcome' not in the_packet[Raw].load.decode():
        return TRUE
    return FALSE

def weather_print_answer(packet):
    """
    the fun print the weather client answer
    :param packet: a weather clint packet 
    :type packet: packet
    :return: none
    """
    response = packet[Raw].load.decode()
    print(response)

def http_filter(packet):
    """
    the fun filter the http packets
    :param packet: packet froom the sniff
    :type packet: packet
    :return: FALSE is not http, is http return TRUE
    :rtype: bool
    """
    if TCP in packet and packet[TCP].dport == 80 and Raw in packet and 'GET' in packet[Raw].load.decode():
        return TRUE
    return FALSE

def print_http(packet):
    """
    the fun print the wanted http part
    :param packet: http packet from the sniff
    :type packet: packet
    :return: none
    """
    data = packet[Raw].load.decode()
    first_idx = str(data).index(GET)
    last_idx = str(data).index(HTTP)
    first_idx += len(GET)
    adrs = data[first_idx:last_idx]
    print(adrs)


def choise_and_menu():
    """
    the fun printing the menu
    :return: the choise
    :rtype: str
    """
    choice = 5
    print("Enter what to sniff: ")
    print("1 - DNS\n2 - Forecast\n3 - HTTP\n4 - E-mails\n0 - Exit: ")
    while choice < 0 or choice > 4:
        try:
            choice = int(input("choise:"))
            if choice < 0 or choice > 4:
                print("Invalid choice")
        except Exception as exp:
            print('Error: ' + str(exp))
    return str(choice)


def main():
    FUNCTIONS = {'1': print_dns,'2': weather_print_answer,'3': print_http}
    FILTER = {'1': filter_the_dns,'2': filter_the_weather,'3': http_filter}
    print('welcome to magshishark')
    while TRUE:
        choice = choise_and_menu()
        if choice == '0':
            break
        elif choice >= 1 and choise <= 3:
            try:
                sniff(lfilter=FILTER[choice], prn=FUNCTIONS[choice])
            except KeyboardInterrupt:
                pass
            except Exception as e:
                print('Error: ' + str(e))
        else :
            print('this one not working')

if __name__ == "__main__":
    main()