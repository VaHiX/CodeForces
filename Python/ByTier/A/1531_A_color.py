# Contest 1531, Problem A: Зингер | color
# URL: https://codeforces.com/contest/1531/problem/A

a = int(input())
locker = False
color = "blue"
for i in range(a):
    s = input()
    if s == "lock":
        locker = True
    elif s == "unlock":
        locker = False
    else:
        if locker == False:
            color = s
print(color)
