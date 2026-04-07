def main():
    file1 = input('Enter the path to the first file: ')
    func = input('Enter the function name: ')
    list = []
    f = open(file1, 'r')   

    if func == "sort":
        for line in f:
            words = line.split()
            for word in words:
                if word not in list:
                    list.append(word)
        list.sort()
        print(list)
    elif func == "rev":
        for line in f:
            print(line[::-1])
            
        print(list)
    else:
        n = int(input('Enter the number of last lines you want to print: '))
        #print the last n line of the file
        lines = f.readlines()
        for line in lines[-n:]:
            print(line)


if __name__ == '__main__':
    main()