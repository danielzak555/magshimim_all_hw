word = input("Enter a word: ")
word = word.lower()
word = word.replace(" ", "")
opposite = word[::-1]

if word == opposite:
    print("OK")
else:
    print("NOT")