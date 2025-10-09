# Contest 2036, Problem G: Library of Magic
# URL: https://codeforces.com/contest/2036/problem/G

#  G. Library of Magic


def solveZero(n):
    y = 2
    while 1:
        print("xor 1", y - 1)
        x = int(input())
        if x == 0:
            y *= 2
        else:
            break
    ab = x
    c = x
    l = y
    h = n
    while 1:
        print("xor", l, (l + h) // 2)
        y = int(input())
        if y == 0:
            l = (l + h) // 2 + 1
        elif y == ab:
            h = (l + h) // 2 - 1
        else:
            break
        if l > h:
            break
    print("ans", y, ab ^ y, c)


for _ in range(int(input())):
    n = int(input())
    if n == 3:
        print("ans 1 2 3")
        continue
    print("xor", 1, n)
    all = int(input())
    if all == 0:
        solveZero(n)
        continue
    l = 1
    h = n
    x = 0
    while 1:
        print("xor", l, (l + h) // 2)
        x = int(input())
        if x == 0:
            l = (l + h) // 2 + 1
        elif x == all:
            h = (l + h) // 2 - 1
        else:
            break
        if l > h:
            break
    ab = x
    c = all ^ x
    l1 = l
    h1 = (l + h) // 2
    l2 = h1 + 1
    h2 = h
    flag = False
    while 1:
        print("xor", l1, (l1 + h1) // 2)
        y = int(input())
        if y == 0:
            l1 = (l1 + h1) // 2 + 1
        elif y == x:
            h1 = (l1 + h1) // 2 - 1
        else:
            flag = True
            break
        if l1 > h1:
            break
    if flag:
        print("ans", y, ab ^ y, c)
    else:
        l1 = l2
        h1 = h2
        while 1:
            print("xor", l1, (l1 + h1) // 2)
            y = int(input())
            if y == 0:
                l1 = (l1 + h1) // 2 + 1
            elif y == c:
                h1 = (l1 + h1) // 2 - 1
            else:
                flag = True
                break
            if l1 > h1:
                break
        print("ans", y, ab, c ^ y)
