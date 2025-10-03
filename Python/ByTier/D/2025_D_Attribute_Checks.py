# Contest 2025, Problem D: Attribute Checks
# URL: https://codeforces.com/contest/2025/problem/D

n, m = map(int, input().split())
rs = map(int, input().split())

d = [-int(1e9)] * (m + 1)
d[0] = 0
add = [0] * (m + 2)


def addSegment(l, r):
    if l <= r:
        add[l] += 1
        add[r + 1] -= 1


def pushAll():
    sum = 0
    for i in range(m + 1):
        sum += add[i]
        d[i] += sum
    for i in range(m + 2):
        add[i] = 0


cntPoints = 0
for r in rs:
    if r == 0:
        pushAll()
        for i in range(m, 0, -1):
            d[i] = max(d[i], d[i - 1])
        cntPoints += 1
    else:
        lf, rg = 0, 0
        if r > 0:
            lf = min(r, m + 1)
            rg = m
        else:
            lf = 0
            rg = max(-1, cntPoints + r)
        addSegment(lf, rg)
pushAll()
print(max(d))
