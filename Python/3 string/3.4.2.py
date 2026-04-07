original = input("Please enter a string: ")
if original == "":
    print("You didn't enter anything.")
else:
    first = original[0]
    rest = original[1:]
    new_rest = rest.replace(first, 'e')

    print(first + new_rest)

