# Contest 2093, Problem G: Shorten the Array
# URL: https://codeforces.com/contest/2093/problem/G

import sys


def input():
    return sys.stdin.readline().strip()


def getints():
    return map(int, sys.stdin.readline().strip().split())


out = []
for _ in range(int(input())):
    n, k = getints()
    a = list(getints())

    if k == 0:
        out.append("1")
        continue

    inf = 10**9
    ans = inf
    x = [-1, -1, inf] * (30 * n + 2)
    nex = 3

    for i in range(n - 2, -1, -1):
        u = 0
        p = 1 << 29
        for j in range(30):
            t = 1 if (a[i + 1] & p) else 0
            if x[u + t] == -1:
                x[u + t] = nex
                nex += 3
            u = x[u + t]
            x[u + 2] = i + 1
            p >>= 1

        u = 0
        t = 1 << 29
        for j in range(30):
            if u == -1:
                break

            if k & t:
                u = x[u + int(a[i] & t == 0)]
            else:
                p = 0 if a[i] & t else 1
                if x[u + p] != -1:
                    temp = 1 + x[x[u + p] + 2] - i
                    if temp < ans:
                        ans = temp
                u = x[u + (1 - p)]
            t >>= 1
        if u != -1:
            temp = 1 + x[u + 2] - i
            if temp < ans:
                ans = temp
        if ans == 2:
            break

    out.append(str(ans if ans != inf else -1))
print("\n".join(out))
