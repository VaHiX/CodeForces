# Problem: CF 1890 E1 - Doremy's Drying Plan (Easy Version)
# https://codeforces.com/contest/1890/problem/E1

"""
Algorithm: Union-Find with interval processing and greedy optimization
Time Complexity: O(m * α(n) + m) where α is the inverse Ackermann function
Space Complexity: O(n + m)

This solution processes intervals of rain across days and uses Union-Find to efficiently
manage overlapping intervals. It then calculates the maximum number of cities that can
be kept dry by preventing rain on exactly 2 days.
"""

import random
import sys
from collections import defaultdict

input = sys.stdin.readline
rd = random.randint(10**9, 2 * 10**9)


def fun1(x):
    # Find root of x with path compression
    t = x
    while fa[x] != x:
        x = fa[x]
    while t != x:
        fa[t], t = x, fa[t]
    return x


def fun2(s, f):
    # Union operation in Union-Find
    x = fun1(s)
    y = fun1(f)
    fa[x] = y


def fun3():
    # Read number of test cases
    t = int(input())
    i = 0
    while i < t:
        fun4()
        i += 1


def fun4():
    # Read input for current test case
    n, m, k = map(int, input().split())
    li = [[] for _ in range(n)]
    global fa
    fa = [i for i in range(n + 1)]
    i = 0
    while i < m:
        l, r = map(int, input().split())
        l -= 1
        r -= 1
        cur = fun1(l)
        while cur <= r:
            li[cur].append(i)
            if len(li[cur]) >= 3:
                # Merge interval if it has 3 or more overlapping days
                fun2(cur, cur + 1)
                cur = fun1(cur)
            else:
                cur += 1
        i += 1
    fun5(n, m, li)


def fun5(n, m, li):
    # Count how many times each day contributes to a city being wet
    cnt = [0] * m
    d = defaultdict(int)
    z = 0
    i = 0
    while i < n:
        if len(li[i]) == 1:
            # City is wet only on one day
            cnt[li[i][0]] += 1
        elif len(li[i]) == 2:
            # City is wet on exactly two days - count pair
            d[(li[i][0], li[i][1])] += 1
        elif len(li[i]) == 0:
            # City is never wet
            z += 1
        i += 1
    fun6(m, cnt, d, z)


def fun6(m, cnt, d, z):
    # Calculate maximum number of dry cities
    ans = 0
    mx = 0
    i = 0
    while i < m:
        # Greedily choose one day to block to minimize wet cities
        ans = max(ans, cnt[i] + mx)
        mx = max(mx, cnt[i])
        i += 1
    # Consider combinations of two days where both can prevent two cities
    for x, y in list(d.keys()):
        ans = max(ans, d[(x, y)] + d[(y, x)] + cnt[x] + cnt[y])
    print(ans + z)


fun3()


# https://github.com/VaHiX/CodeForces/