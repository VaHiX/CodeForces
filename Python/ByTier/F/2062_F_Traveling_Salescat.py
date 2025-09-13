# Contest 2062, Problem F: Traveling Salescat
# URL: https://codeforces.com/contest/2062/problem/F


class Q:
    def __init__(this, x, y):
        this.x, this.y = x + y, x - y

    def __lt__(this, rhs):
        return this.y < rhs.y


for _ in range(int(input())):
    n = int(input())
    a = [0] * n
    for i in range(n):
        x, y = map(int, input().split())
        a[i] = Q(x, y)
    a.sort()
    l = [10**18] * (n + 1)
    sl = l.copy()
    slt = l.copy()
    slrt = l.copy()
    s = 10**18
    for m, t in enumerate(a):
        x, y = t.x, t.y
        for i in range(m, 0, -1):
            slrt[i + 1] = min(slrt[i + 1], sl[i] + x + y, slt[i] + x * 2 + y * 2)
            slt[i + 1] = min(slt[i + 1], slt[i] + x * 2, sl[i] + x - y)
            sl[i + 1] = min(sl[i + 1], sl[i] + x * 2, l[i] + x + y)
            l[i + 1] = min(l[i + 1], l[i] + x * 2)
        sl[1] = min(sl[1], x - y)
        l[1] = min(l[1], x * 2 - y * 2)
    print(*[x // 2 for x in slrt[2:]])
