# Problem: CF 2130 E2 - Interactive RBS (Medium Version)
# https://codeforces.com/contest/2130/problem/E2

"""
Interactive RBS (Medium Version)

Purpose:
This code solves an interactive problem where the goal is to reconstruct a hidden bracket sequence of length n, consisting of '(' and ')', using at most 200 queries.

Algorithms/Techniques:
- Binary search on the structure of the bracket sequence.
- Using a specific set of queries to determine which positions belong to the prefix or suffix.
- Determining individual bracket types based on query results using precomputed lookup tables (w, w1).

Time Complexity: O(n * log n) - Each position is checked multiple times in a binary search fashion and for each group of 10 elements we perform a few queries, leading to linearithmic behavior.

Space Complexity: O(n) - Storage for result array 'rs' and temporary lists during processing.
"""

def INT():
    return int(input())


def MAP():
    return map(int, (input().split()))


def MAT(n):
    return [list(map(int, (input().split()))) for _ in range(n)]


def qu(a):
    print(f"? {len(a)}", end=" ")
    print(*a)
    return INT()


def op(n):
    a = 1
    o = list(range(2, n + 1))
    while len(o) > 1:
        m = len(o) >> 1
        he = o[:m]
        ii = [a] + [x for h in he for x in (h, a)]
        o = he if qu(ii) > 0 else o[m:]
    b = o[0]
    return (a, b) if qu([a, b]) == 1 else (b, a)


# Precomputed lookup tables for binary search
w = [1, 3, 6, 15, 28, 55, 120, 231, 465, 5050]
w1 = [1, 2, 3, 5, 7, 10, 15, 21, 30, 100]

for _ in range(INT()):
    n = INT()
    l, r = op(n)
    rs = [-1] * (n + 1)
    rs[l] = 0
    rs[r] = 1
    uwu = [i for i in range(1, n + 1) if i not in (l, r)]
    i = 0
    while i < len(uwu):
        ww = uwu[i : min(i + 10, len(uwu))]  # Process up to 10 elements at a time to maintain query limits
        ii = []
        for k, u in enumerate(ww):
            ii += [u, r] * w1[k]  # Prepare multiple queries per element based on lookup table
            ii += [r]
        t = qu(ii)  # Perform single query for current batch
        for k in range(len(ww), 0, -1):
            u = ww[k - 1]
            if t >= w[k - 1]:  # Determine type of bracket based on prefix sum
                rs[u] = 0
                t -= w[k - 1]
            else:
                rs[u] = 1
        i += len(ww)
    print("!", "".join("(" if rs[i] == 0 else ")" for i in range(1, n + 1)))


# https://github.com/VaHiX/codeForces/