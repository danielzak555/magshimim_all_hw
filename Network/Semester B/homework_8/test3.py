import socket

target_ip = "54.71.128.194"
target_port = 99
base_msg = "FLY008"
start_base = "ENT003"
message = "location_md5=68cdaeac7bb51cd583415ba2fa552d5c,airport=nevada25.84,time=15:52,lane=earth.jup,vehicle=2554,fly"
sec_msg = "location_md5=68cdaeac7bb51cd583415ba2fa552d5c,airport=unselected,time=15:52,lane=earth.jup,vehicle=2554,fly"
start_message = "jupiter"

def shift_odd_indices_back(text, shift):
    result = ""
    for i, char in enumerate(text):
        if i % 2 == 0 and char.isalpha():
            shifted = chr(((ord(char.lower()) - ord('a') - shift) % 26) + ord('a'))
            result += shifted.upper() if char.isupper() else shifted
        else:
            result += char
    return result

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

try:
    sock.connect((target_ip, target_port))
    start_enc = shift_odd_indices_back(start_message, -3)
    full_start = start_base + start_enc
    sock.sendall(full_start.encode())

    data = sock.recv(4096)
    print(f"{data.decode()}")
    
    output_text = shift_odd_indices_back(message, 8)
    full_msg = f"{base_msg}{output_text}"
    sock.sendall(full_msg.encode())
    data = sock.recv(4096)
    print(f"{data.decode()}")
    
    output_sec = shift_odd_indices_back(sec_msg, 8)
    full_msg_sec = f"{base_msg}{output_sec}"
    for i in range(6):
        sock.sendall(full_msg_sec.encode())

        data = sock.recv(4096)
        print(f"{data.decode()}")

except Exception as e:
    print(f"An error occurred: {e}")

sock.close()
