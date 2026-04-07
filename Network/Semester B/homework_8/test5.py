import socket
import re
import hashlib


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
    
    return decoded_text


def get_md5(input_text):
    hasher = hashlib.md5()
    hasher.update(input_text.encode('utf-8'))
    return hasher.hexdigest()


def receive_data(sock):
    raw_data = sock.recv(4096).decode()
    decoded = parse_tagged_data(raw_data)
    print(decoded)
    return decoded


def communicate(sock, data):
    print(f"> SENDING: {data}")
    sock.sendall(data.encode())
    result = receive_data(sock)
    return result


HOST_ADDR = ("54.71.128.194", 99)

COMMANDS = {
    "LOGIN": {"header": "ENT003", "content": "jupiter"},
    "FLIGHT": {"header": "FLY008", "content": "location_md5=00000000000000000000000000000000,airport=nevada25.84,time=15:52,lane=earth.jup,vehicle=2554,fly"}
}

# Prepare encoded commands
READY_COMMANDS = {}
for cmd_type, cmd_info in COMMANDS.items():
    header, content = cmd_info.values()
    rotation = int(header[3:])
    READY_COMMANDS[cmd_type] = f"{header}{decode_even_positions(content, -1 * rotation)}"


def main():
    location_parts = []
    
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as client:
            client.connect(HOST_ADDR)
            
            # Send login
            communicate(client, READY_COMMANDS["LOGIN"])
            
            # Collect location data
            for iteration in range(30):
                response = receive_data(client)
                if "location data" in response:
                    location_parts.append(response.split(":")[1].strip())
            
            # Process collected data
            all_locations = "".join(location_parts)
            print("Collected: ", all_locations)
            
            checksum = get_md5(all_locations)
            print("MD5: " + checksum)
            
            # Build flight command
            flight_params = f"location_md5={checksum},airport=nevada25.84,time=15:52,lane=earth.jup,vehicle=2554,fly"
            encoded_flight = f"FLY008{decode_even_positions(flight_params, -8)}"
            print(encoded_flight)
            
            # Send flight command
            communicate(client, encoded_flight)
            
    except Exception as err:
        print(f"Error occurred: {err}")


if __name__ == "__main__":
    main()