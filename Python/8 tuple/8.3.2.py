def main():
    choise = int(input("Enter a number: "))
    person = {"first_name": "Mariah", "last_name": "Carey", "birth_date": "27.03.1970", "hobbies": ["Sing", "Compose", "Act"]}

    if choise == 1:
        print(person["last_name"])
    elif choise == 2:
        print(person["birth_date"][3:5])
    elif choise == 3:
        print(len(person["hobbies"]))
    elif choise == 4:
        print(person["hobbies"][-1])
    elif choise == 5:
        person["hobbies"].append("Cooking")
    elif choise == 6:#birth date into 3 numbers day, month , year
        day, month, year = person["birth_date"].split(".")
        print((day, month, year))
    else:
        print(person["50"])

if __name__ == "__main__":
    main()