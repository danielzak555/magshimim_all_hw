def chocolate_maker(small, big, x):
    num = min(x//5, big)
    if num*5 + small >= x:
        return True
    return False
