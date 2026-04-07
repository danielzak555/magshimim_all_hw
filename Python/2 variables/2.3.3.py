num = int(input("Enter three digits (each digit for one pig):"))
pig1 = num // 100
pig2 = (num // 10) % 10
pig3 = num % 10
sum = pig1 + pig2 + pig3

flag = sum % 3 == 0

print(sum)
print(sum // 3)
print(sum % 3)
print(flag)
