def distance(num1, num2, num3):
    if (abs(num1 - num2) <= 1 or abs(num1 - num3) <= 1):
        if ((abs(num1 - num2) >= 2 and abs(num3 - num2) >= 2) or (abs(num1 - num3) >= 2 and abs(num2 - num3) >= 2)):
            return True
    return False
