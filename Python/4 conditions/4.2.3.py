temp = input("Insert the temperature you would like to convert: ")
len = len(temp)

type = temp[-1]
type = type.upper()
num = temp[0:len-1]
converted = 0

celsius = 'C'
farenheit = 'F'

if type == farenheit:
    converted = (5 * float(num) - 160) / 9
    print(str(converted) + celsius)

else:
    converted = (9 * float(num) + (32 * 5)) / 5
    print(str(converted) + farenheit)
