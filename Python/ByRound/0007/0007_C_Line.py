# Contest 7, Problem C: Line
# URL: https://codeforces.com/contest/7/problem/C


def extgcd(a, b):
    global x, y, g
    if b == 0:
        x = 1
        y = 0
        g = a
        return
    extgcd(b, a % b)
    x1 = y
    y1 = x - (a // b) * y
    x = x1
    y = y1


[a, b, c] = [int(x) for x in input().split()]
extgcd(a, b)
c = -c
if c % g:
    print(-1)
else:
    print(x * (c // g), y * (c // g))
