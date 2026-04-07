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
        tag = matches[i].group(0)
        shift = int(matches[i].group(2))
        chunk = big_text[start:end]
        shifted_chunk = shift_even_indices_back(chunk, shift)
        result += shifted_chunk + '\n'  # preserve the original tag
 
    return result
 
 
BIG = """ERR008***ezrwr wqtp nlg ueasigm***;lwcitqov ud5 qs wzovg! xezfwru ud5 paah ov bhm 100 khir bcfnez!;""".strip()
 
 
print(process_shifted_chunks(BIG))
 