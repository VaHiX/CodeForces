# Contest 1120, Problem A: Diana and Liana
# URL: https://codeforces.com/contest/1120/problem/A

import sys
from array import array

input = lambda: sys.stdin.buffer.readline().decode().strip()
inp = lambda dtype: [dtype(x) for x in input().split()]
inp_2d = lambda dtype, n: [dtype(input()) for _ in range(n)]
inp_2ds = lambda dtype, n: [inp(dtype) for _ in range(n)]
ceil1 = lambda a, b: (a + b - 1) // b
debug = lambda *x: print(*x, file=sys.stderr)
out = []


def get_right():
    dis = set()

    for i in range(s):
        cb[b[i]] += 1
        dis.add(b[i])

    for i in range(m):
        if cb[a[i]]:
            ca[a[i]] += 1
        if ca[a[i]] == cb[a[i]]:
            dis.discard(a[i])

        if not dis:
            return i

    exit(print(-1))


def valid(l, r):
    divl, modl = divmod(l, k)
    divr, modr = divmod(m - r - 1, k)
    le, splits = r - l + 1, divl + divr + 1

    if splits < n:
        return 0

    ret = array("i", list(range(1, modl + 1)) + list(range(m + 1 - modr, m + 1)))
    while splits > n and divl:
        splits -= 1
        divl -= 1
        ret.extend(range(modl + 1, modl + k + 1))
        modl += k

    while splits > n and divr:
        splits -= 1
        divr -= 1
        modr += k
        ret.extend(range(m - modr + 1, m - modr + k + 1))

    for i in range(l, r + 1):
        if cb[a[i]]:
            cb[a[i]] -= 1
        elif le > k:
            le -= 1
            ret.append(i + 1)

    exit(print(f"{m - n * k}\n{' '.join(map(str, ret))}"))


def adjust(l, r):
    while r < m - 1 and r - l + 1 < k:
        r += 1
        ca[a[r]] += 1
    return r


max_ = 5 * 10**5 + 1
m, k, n, s = inp(int)
a, b = array("i", inp(int)), array("i", inp(int))
ca, cb = array("i", [0] * max_), array("i", [0] * max_)
r = adjust(0, get_right())
valid(0, r)

for l in range(1, m - k + 1):
    if cb[a[l - 1]]:
        ca[a[l - 1]] -= 1

        while r < m - 1 and ca[a[l - 1]] < cb[a[l - 1]]:
            r += 1
            ca[a[r]] += 1

        if ca[a[l - 1]] < cb[a[l - 1]]:
            break

    r = adjust(l, r)
    valid(l, r)
print(-1)
