# Problem: CF 1672 F2 - Checker for Array Shuffling
# https://codeforces.com/contest/1672/problem/F2

"""
Algorithm: Cycle Detection and Topological Sorting
Purpose: Determine if permutation b has maximum sadness (minimum swaps to sort) over all permutations of array a.
Time Complexity: O(n)
Space Complexity: O(n)

The sadness of a permutation b is the minimum number of swaps needed to transform b into a.
This is equivalent to finding the number of cycles in the permutation graph minus 1.
Maximum sadness occurs when the number of cycles is minimized, which happens when:
- The permutation consists of the maximum frequency element in a forming a single large cycle
- All other elements form smaller cycles that can be grouped together in a way that maximizes the number of operations

Approach:
1. Count frequency of each element in a
2. Identify the element with maximum frequency (call it m)
3. Build a directed graph where an edge from x to y means a[i] = x and b[i] = y
4. Use topological sort to count nodes that are not part of cycles and not the maximum frequency element
5. If the count of such nodes equals total unique elements minus 1, then it's the maximum sadness case, else it is not.
"""
import sys

try:
    pass
except:
    pass
try:
    from icecream import ic
except:
    ic = lambda *a: None if not a else (a[0] if len(a) == 1 else a)
from bisect import *
from collections import *
from functools import *
from heapq import *
from itertools import *
from random import *

input = lambda: sys.stdin.readline().strip()


def read(fn=int):
    return map(fn, input().split())


def dbg(*args, **kwargs):
    print(*args, **kwargs, file=sys.stderr)


class ostream:
    def __lshift__(self, s):
        sys.stdout.write(str(s))
        return self


cout = ostream()
endl = "\n"

yes = "YES"
no = "NO"


def mul(a, b, mod=0):
    if sum(map(sum, a)) == 0 or sum(map(sum, b)) == 0:
        return [[0] * len(b[0]) for _ in range(len(a))]
    c = [[0 for j in range(len(b[0]))] for i in range(len(a))]
    for i in range(len(a)):
        for j in range(len(b[0])):
            for k in range(len(b)):
                c[i][j] += a[i][k] * b[k][j]
                if mod:
                    c[i][j] %= mod
    return c


def power(x, y, mod=0):
    n = len(x)
    res = [[+(i == j) for j in range(n)] for i in range(n)]
    while y:
        if y % 2:
            res = mul(res, x, mod)
        x = mul(x, x, mod)
        y //= 2
    return res


def power2(x, y, mod=0):
    res = [[+(i == j) for j in range(20)] for i in range(20)]
    for i in range(len(pows)):
        if (y >> i) & 1:
            res = mul(res, pows[i], mod)
            if sum(map(sum, res)) == 0:
                break
    return res


mod = 998244353


def sieve(n, primes):
    n = int(n)
    isp = [True] * (n + 1)
    isp[0] = isp[1] = False
    for i in range(2, n + 1):
        if isp[i]:
            primes += [i]
            for j in range(i * i, n + 1, i):
                isp[j] = False
    return isp


for _ in range(int(input())):
    (n,) = read()
    a = [*read()]
    b = [*read()]
    f = [0] * (n + 1)
    for x in a:
        f[x] += 1
    m = (0, 0)
    for i in range(1, n + 1):
        m = max(m, (f[i], i))
    m = m[1]
    deg = [0] * (n + 1)
    adj = [[] for _ in range(n + 1)]
    for i in range(n):
        if a[i] == m or b[i] == m:
            continue
        adj[a[i]].append(b[i])
        deg[b[i]] += 1

    l = [i for i in range(1, n + 1) if f[i] and deg[i] == 0 and i != m]
    vis = 0
    while l:
        x = l.pop()
        vis += 1
        for y in adj[x]:
            deg[y] -= 1
            if not deg[y]:
                l += [y]
    print("AC" if vis == sum(x > 0 for x in f) - 1 else "WA")


# https://github.com/VaHiX/CodeForces/