import calendar

date_str = input("Enter a date: ")

day = int(date_str[0:2])
month = int(date_str[3:5])
year = int(date_str[6:10])

day_number = calendar.weekday(year, month, day)

if day_number == 0:
    name_of_day = "Monday"
elif day_number == 1:
    name_of_day = "Tuesday"
elif day_number == 2:
    name_of_day = "Wednesday"
elif day_number == 3:
    name_of_day = "Thursday"
elif day_number == 4:
    name_of_day = "Friday"
elif day_number == 5:
    name_of_day = "Saturday"
else:
    name_of_day = "Sunday"

print(name_of_day)