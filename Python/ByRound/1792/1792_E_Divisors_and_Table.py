# Problem: CF 1792 E - Divisors and Table
# https://codeforces.com/contest/1792/problem/E

"""
Code Purpose:
This code solves the problem of finding divisors of a number m = m1 * m2 that appear in an n x n multiplication table,
and for each such divisor, finds the minimum row in which it occurs. It then computes the XOR of all such minimum row indices.

Approach:
1. Factorize m1 and m2 into prime factors.
2. Generate all divisors of m that are <= n^2.
3. For each valid divisor d, find the minimum row index where d appears in the multiplication table.
   - A number d appears in row r if r divides d and d/r <= n.
   - The minimum row for d is the smallest r such that r divides d and d/r <= n.
4. XOR all valid minimum row indices.

Time Complexity: O(log(m) * sqrt(n) * log(n))
Space Complexity: O(log(m) * log(n))

Algorithms/Techniques:
- Prime factorization
- Subset generation with backtracking
- Bit manipulation (XOR)
- Mathematical optimization to avoid unnecessary computation
"""

import sys
from collections import Counter
from math import ceil, log, sqrt

input = lambda: sys.stdin.readline().rstrip()
t = int(input())


def factor(n: int) -> list:
    res = []
    for p in range(2, ceil(sqrt(n))):
        if p > n:
            break
        if n % p == 0:
            cur = 0
            while n % p == 0:
                n //= p
                cur += 1
            res.append((p, cur))
            cur = 0
    if n > 1:
        if n % (ceil(sqrt(n))) == 0:
            res.append((ceil(sqrt(n)), 2))
        else:
            res.append((n, 1))
    return res


def solve():
    res, (n, m1, m2) = [1, 1], map(int, input().split())
    d1, d2 = factor(m1), factor(m2)
    cm, maxN = Counter(), n**2
    for p, c in d1 + d2:
        if p > n:
            continue
        cm[p] += c
        cm[p] = min(cm[p], 2 * int(log(n, p)))
    dp, divs = {1: 1}, [[[], [1]]]
    for p, c in cm.items():
        for i in range(len(divs)):
            f, nums = divs[i]
            divs.append([f + [p], []])
            for num in nums:
                cand = num
                for i in range(1, c + 1):
                    cand *= p
                    if cand > maxN:
                        break
                    elif cand <= n:
                        dp[cand] = 1
                    else:
                        dp[cand] = n + 1
                        for q in divs[-1][0]:
                            cq = cand // q
                            dp[cand] = min(
                                dp[cand], dp[cq] * (1 if cand <= dp[cq] * n else q)
                            )
                    if dp[cand] <= n:
                        divs[-1][1].append(cand)
                        res[0] += 1
                        res[1] ^= dp[cand]
                    else:
                        break
    return res


for _ in range(t):
    res = solve()
    print(" ".join(map(str, res)))


# https://github.com/VaHiX/CodeForces/