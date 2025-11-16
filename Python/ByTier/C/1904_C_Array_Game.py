# Problem: CF 1904 C - Array Game
# https://codeforces.com/contest/1904/problem/C

"""
Algorithm: Array Game
Purpose: Given an array of positive integers and k operations, each operation appends the absolute difference of two elements to the array. The goal is to minimize the minimum value in the array after k operations.

Approach:
- If k >= 3, we can always reduce the minimum value to 0 by taking differences and adding 0.
- If k == 1, we compute the minimum difference between consecutive elements.
- If k == 2, we iterate through all pairs and calculate how the minimum can be reduced considering the new elements.
- Sorting the array helps in efficient computation of differences.

Time Complexity: O(n log n) due to sorting, where n is the size of the array.
Space Complexity: O(1) ignoring the input storage.
"""

import sys
from math import gcd

input = lambda: sys.stdin.readline().rstrip("\r\n")


from types import GeneratorType


def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to

    return wrappedfunc


def I():
    return input()


def II():
    return int(input())


def MII():
    return map(int, input().split())


def LI():
    return list(input().split())


def LII():
    return list(map(int, input().split()))


def GMI():
    return map(lambda x: int(x) - 1, input().split())


def LGMI():
    return list(map(lambda x: int(x) - 1, input().split()))


def isPrimeMR(n):
    if n <= 1:
        return 0
    if n == 2 or n == 7 or n == 61:
        return 1
    d = n - 1
    d = d // (d & -d)
    L = (
        [2, 7, 61]
        if n < 1 << 32
        else (
            [2, 3, 5, 7, 11, 13, 17]
            if n < 1 << 48
            else [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]
        )
    )
    for a in L:
        t = d
        y = pow(a, t, n)
        if y == 1:
            continue
        while y != n - 1:
            y = y * y % n
            if y == 1 or t == n - 1:
                return 0
            t <<= 1
    return 1


def findFactorRho(n):
    m = 1 << n.bit_length() // 8
    for c in range(1, 99):
        f = lambda x: (x * x + c) % n
        y, r, q, g = 2, 1, 1, 1
        while g == 1:
            x = y
            for i in range(r):
                y = f(y)
            k = 0
            while k < r and g == 1:
                ys = y
                for i in range(min(m, r - k)):
                    y = f(y)
                    q = q * abs(x - y) % n
                g = gcd(q, n)
                k += m
            r <<= 1
        if g == n:
            g = 1
            while g == 1:
                ys = f(ys)
                g = gcd(abs(x - ys), n)
        if g < n:
            if isPrimeMR(g):
                return g
            elif isPrimeMR(n // g):
                return n // g
            return findFactorRho(g)


def primeFactor(n):
    i = 2
    ret = {}
    rhoFlg = 0
    while i * i <= n:
        k = 0
        while n % i == 0:
            n //= i
            k += 1
        if k:
            ret[i] = k
        i += i % 2 + (3 if i % 3 == 1 else 1)
        if i == 101 and n >= 2**20:
            while n > 1:
                if isPrimeMR(n):
                    ret[n], n = 1, 1
                else:
                    rhoFlg = 1
                    j = findFactorRho(n)
                    k = 0
                    while n % j == 0:
                        n //= j
                        k += 1
                    ret[j] = k
    if n > 1:
        ret[n] = 1
    if rhoFlg:
        ret = {x: ret[x] for x in sorted(ret)}
    return ret


def divisors(N):
    pf = primeFactor(N)
    ret = [1]
    for p in pf:
        ret_prev = ret
        ret = []
        for i in range(pf[p] + 1):
            for r in ret_prev:
                ret.append(r * (p**i))
    return sorted(ret)


dx, dy = [0, 1, 0, -1, 1, -1, 1, -1], [1, 0, -1, 0, -1, -1, 1, 1]
inf = float("inf")

mod = int(1e9 + 7)

from itertools import pairwise


def solve():
    n, k = MII()
    a = LII()
    a.sort()
    if k >= 3:
        print(0)
        return
    else:
        res = a[0]
        if k == 1:
            for x, y in pairwise(a):
                res = min(res, y - x)
        else:
            for i in range(n):
                k = 0
                for j in range(i + 1, n):
                    cur = a[j] - a[i]
                    res = min(res, cur)
                    while k < n and a[k] < cur:
                        k += 1
                    if k - 1 >= 0:
                        res = min(res, cur - a[k - 1])
                    if k < n:
                        res = min(res, a[k] - cur)
        print(res)

    return


if __name__ == "__main__":

    t = 1
    if t:
        t = II()
        for _ in range(t):
            solve()
    else:
        solve()


# https://github.com/VaHiX/CodeForces/