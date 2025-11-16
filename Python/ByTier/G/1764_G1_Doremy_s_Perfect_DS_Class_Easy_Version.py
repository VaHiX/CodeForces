# Problem: CF 1764 G1 - Doremy's Perfect DS Class (Easy Version)
# https://codeforces.com/contest/1764/problem/G1

"""
Algorithm: Binary search on position of element 1 in the permutation.
Techniques: 
- Use floor division queries to determine the number of distinct values in subarrays.
- Binary search to find the index where p[i] = 1.
- Use properties of how division affects elements to narrow down the position.

Time Complexity: O(log^2 n) due to nested binary searches and at most 30 queries.
Space Complexity: O(1) for variables, O(n) for memoization dictionary D.
"""

n = int(input())
D = dict()
P = list(range(1, n + 1))
import random

random.shuffle(P)


def qu(l, r, k):
    # Query function to get number of distinct values in floor division
    if (l, r, k) not in D:
        print("?", l + 1, r + 1, k)
        q = set()
        for i in range(l, r + 1):
            q.add(P[i] // k)
        D[(l, r, k)] = int(input())
    return D[(l, r, k)]


def ans(x):
    # Output the answer
    print("!", x + 1)


if n % 2 == 0:
    # Handle even case
    lo = 0
    hi = n - 1
    while lo + 1 < hi:
        m = (lo + hi) // 2
        x = qu(0, m, n)
        if x == 1:
            lo = m
        else:
            hi = m
    if hi == 1:
        x = qu(1, n - 1, n)
        if x == 1:
            hi = 0
    biggest = hi
    lo = 0
    hi = n
    while lo + 1 < hi:
        m = (lo + hi) // 2
        l = qu(0, m - 1, 2)
        r = qu(m, n - 1, 2)

        fullb = m - l
        splitb = m - fullb * 2
        if m > biggest:
            splitb -= 1

        rshould = (n - m - splitb - int(biggest >= 1)) // 2 + splitb
        if m <= biggest:
            rshould += 1
        if r > rshould:
            lo = m
        else:
            hi = m
    ans(lo)
    print(P)
else:
    # Handle odd case
    lo = 0
    hi = n
    totalbuckets = n // 2 + 1
    while lo + 1 < hi:
        m = (lo + hi) // 2
        l = qu(0, m - 1, 2)
        r = qu(m, n - 1, 2)

        fullb = m - l
        splitb = m - fullb * 2

        rshould = (n - m - splitb) // 2 + splitb
        if r > rshould:
            lo = m
        else:
            hi = m
    ans(lo)


# https://github.com/VaHiX/CodeForces/