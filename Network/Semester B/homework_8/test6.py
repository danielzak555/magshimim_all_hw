from scapy.all import sniff, UDP, IP, sr1
import re
import hashlib

INTERFACE = r"\Device\NPF_{8DF02B1E-8F7D-4290-84F0-EBB3BD657DA9}"
pkt_count = 50
location_parts = []
client_port = 0
client_ip = 0
was_ten_of_ten = 0

def decode_even_positions(data, rotation):
    output = ""
    for pos, ch in enumerate(data):
        if pos % 2 == 0 and ch.isalpha():
            rotated = chr(((ord(ch.lower()) - ord('a') - rotation) % 26) + ord('a'))
            output += rotated.upper() if ch.isupper() else rotated
        else:
            output += ch
    return output


def parse_tagged_data(raw_text):
    global was_ten_of_ten
    tag_regex = r'([A-Z]{3})(\d{3})'
    found_tags = list(re.finditer(tag_regex, raw_text))
    
    decoded_text = ""
    for i in range(len(found_tags)):
        begin = found_tags[i].end()
        finish = found_tags[i+1].start() if i+1 < len(found_tags) else len(raw_text)
        rotation_num = int(found_tags[i].group(2))
        segment = raw_text[begin:finish]
        decoded_segment = decode_even_positions(segment, rotation_num)
        decoded_text += decoded_segment + '\n'
        if "location data" in decoded_text:
            if was_ten_of_ten == 0:
                    if "10/10" in decoded_text:
                        was_ten_of_ten = 1
                    location_parts.append(decoded_text.split(":")[1].strip())
    
    return decoded_text


def get_md5(input_text):
    return hashlib.md5(input_text.encode('utf-8')).hexdigest()


def packet_callback(packet):
    global client_port
    global client_ip
    if UDP in packet and (packet[UDP].sport == 99 or packet[UDP].dport == 99):
        try:
            payload = bytes(packet[UDP].payload).decode()
            decoded = parse_tagged_data(payload)
            print(decoded)
            
            if client_port == 0 and packet[UDP].dport == 99 and packet[IP].dst == "54.71.128.194":
                client_port = packet[UDP].sport
                client_ip = packet[IP].src
                print(f"Captured client info - IP: {client_ip}, Port: {client_port}")
                
        except Exception as e:
            print(f"Failed to decode packet: {e}")

def sniff_packets():
    print("Sniffing UDP packets on port 99...")
    sniff(filter="udp port 99", prn=packet_callback, count=pkt_count, iface=INTERFACE)

    
def main():
    sniff_packets()

    all_locations = ''.join(location_parts)
    print("Collected text:\n", all_locations)

    checksum = get_md5(all_locations)
    print("MD5 checksum:", checksum)

    flight_params = f"location_md5={checksum},airport=nevada25.84,time=15:52,lane=earth.jup,vehicle=2554,fly"
    encoded_flight = f"FLY008{decode_even_positions(flight_params, -8)}"
    print("Prepared flight command:\n", encoded_flight)

    print(f"> SENDING: {encoded_flight}")
    
    packet = IP(src=client_ip, dst="54.71.128.194") / UDP(sport=client_port, dport=99) / encoded_flight
    response = sr1(packet, verbose=0)
    
    if response:
        if response.haslayer(UDP):
            print("Response:", bytes(response[UDP].payload).decode())
    else:
        print("No response received")


if __name__ == "__main__":
    main()