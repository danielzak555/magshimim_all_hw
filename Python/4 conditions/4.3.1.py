guess = input("Guess a letter: ")
len = len(guess)

if len == 1 and ((guess >= "a" and guess <= "z") or (guess >= "A" and guess <= "Z")):
    print(guess.lower())

elif guess.isalpha():
    print("E1")

elif len == 0:
    print("you didn't enter anything")

elif len == 1:
    print("E2")
    
else:
    print("E3") 