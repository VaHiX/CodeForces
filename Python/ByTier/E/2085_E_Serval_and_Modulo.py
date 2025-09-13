# Contest 2085, Problem E: Serval and Modulo
# URL: https://codeforces.com/contest/2085/problem/E

import sys


def input():
    return sys.stdin.readline().strip()


def getints():
    return map(int, sys.stdin.readline().strip().split())


from math import isqrt

for _ in range(int(input())):
    n = int(input())
    a = list(getints())
    bb = list(getints())

    b = {}
    for x in bb:
        if x in b:
            b[x] += 1
        else:
            b[x] = 1

    t = sum(a) - sum(bb)
    mb = max(bb)
    top = 10**6 + 10

    if t < 0:
        print(-1)
        continue

    f = [10**6 + 5]
    for i in range(1, isqrt(t) + 1):
        if t % i == 0:
            f.append(i)
            if i != t // i:
                f.append(t // i)

    for x in f:
        if x <= mb or x > top:
            continue

        c = {}
        for p in a:
            p = p % x
            if p in c:
                c[p] += 1
            else:
                c[p] = 1

        for p in c:
            if p in b:
                if c[p] != b[p]:
                    break
            else:
                break
        else:
            print(x)
            break
    else:
        print(-1)
