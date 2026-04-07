import socket
import re


def shift_even_indices_back(text: str, shift: int) -> str:
    result = ""
    for i, char in enumerate(text):
        if i % 2 == 0 and char.isalpha():
            shifted = chr(
                ((ord(char.lower()) - ord('a') - shift) % 26) + ord('a'))
            result += shifted.upper() if char.isupper() else shifted
        else:
            result += char
    return result


def process_shifted_chunks(big_text: str) -> str:
    # Match tags like ERR008, DAT003 etc.
    pattern = r'([A-Z]{3})(\d{3})'
    matches = list(re.finditer(pattern, big_text))

    result = ""
    for i in range(len(matches)):
        start = matches[i].end()
        end = matches[i+1].start() if i+1 < len(matches) else len(big_text)
        # tag = matches[i].group(0)
        shift = int(matches[i].group(2))
        chunk = big_text[start:end]
        shifted_chunk = shift_even_indices_back(chunk, shift)
        result += shifted_chunk + '\n'  # preserve the original tag

    return result


def shift_even_indices_back(text: str, shift: int) -> str:
    result = ""
    for i, char in enumerate(text):
        if i % 2 == 0 and char.isalpha():
            shifted = chr(
                ((ord(char.lower()) - ord('a') - shift) % 26) + ord('a'))
            result += shifted.upper() if char.isupper() else shifted
        else:
            result += char
    return result


# Socket
SERVER = ("54.71.128.194", 99)

MESSAGES = {
    "ENT": {"prefix": "ENT003", "data": "jupiter"},
    "FLY": {"prefix": "FLY008", "data": "location_md5=REPLACE_THIS_MD5,airport=nevada25.84,time=15:52,lane=earth.jup,vehicle=2554,fly"}
}

ENCRYPTED_MESSAGES = {
}

for message_name, message in MESSAGES.items():
    prefix, data = message.values()
    shift = int(prefix[3:])
    ENCRYPTED_MESSAGES[message_name] = f"{prefix}{shift_even_indices_back(data, -1 * shift)}"


def send_and_recv(sock: socket.socket, message: str):
    print(f"> SEND: {message}")
    sock.sendall(message.encode())
    response = sock.recv(10000).decode()
    print(process_shifted_chunks(response))
    return response


def main():
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
            s.connect(SERVER)

            send_and_recv(s, ENCRYPTED_MESSAGES["ENT"])

    except Exception as e:
        print(f"Error: {e}")


if __name__ == "__main__":
    main()
