original = input("Please enter a string: ")
len = len(original) // 2
part_one = original[0:len]
part_two = original[len:]
print(part_one.lower() + part_two.upper())


