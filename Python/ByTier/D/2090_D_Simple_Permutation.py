# Contest 2090, Problem D: Simple Permutation
# URL: https://codeforces.com/contest/2090/problem/D

import math

limit = 100000


def soe(limit):
    prime = [True] * (limit + 1)
    prime[0] = prime[1] = False
    for i in range(2, int(math.sqrt(limit)) + 1):
        if prime[i]:
            for j in range(i * i, limit + 1, i):
                prime[j] = False
    return prime


def solve(n, prime):
    res = []
    p = 1
    for i in range(1, 2 * n // 3 + 1):
        if prime[i]:
            p = i
    l, r = p - 1, p + 1
    res.append(p)
    while True:
        if r > n:
            break
        res.append(r)
        r += 1
        if l < 1:
            break
        res.append(l)
        l -= 1
    res.extend(range(1, l + 1))
    res.extend(range(r, n + 1))
    print(" ".join(map(str, res)))


t = int(input())
prime = soe(limit)
for _ in range(t):
    n = int(input())
    solve(n, prime)
