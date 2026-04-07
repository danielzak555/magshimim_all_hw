def groceries(str):
    """Return what the user wants
    :param str: a string
    :type str: str
    :return: None
    :rtype: None
    """
    last = 0
    grocery_list = []
    flag = True
    i = 0

    for item in str:
        if item == ',':
            grocery_list.append(str[last:i])
            last = i + 1
        i += 1
    grocery_list.append(str[last:])

    while(flag):
        choise = int(input("enter number between 1 and 9:"))
        if(choise == 1):
            print(grocery_list)
        elif(choise == 2):
            print(len(grocery_list))
        elif(choise == 3):
            item = input("enter item to check:")
            if item in grocery_list:
                print("True")
            else:
                print("False")
        elif(choise == 4):
            item = input("enter item to check how much:")
            print(grocery_list.count(item))
        elif(choise == 5):
            item = input("enter item to remove his first appiriance:")
            grocery_list.remove(item)
        elif(choise == 6):
            item = input("item to add: ")
            grocery_list.append(item)
        elif(choise == 7): #check if item shorter than 3 or have somthing else then letters
            for i in grocery_list:
                if len(i) < 3 or not i.isalpha():
                    print(i)
        elif(choise == 8):# remove all repeated groceries in the list
            new_list = [grocery_list[0]]
            for i in grocery_list:
                if i not in new_list:
                    new_list.append(i)
            grocery_list = new_list
        elif(choise == 9):
            flag = False
                
def main():
    str = input("enter your list:")
    groceries(str)

if __name__ == "__main__":
    main()
