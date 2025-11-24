# Problem: CF 1746 E2 - Joking (Hard Version)
# https://codeforces.com/contest/1746/problem/E2

"""
Interactive problem to find a hidden integer x in range [1, n] using at most 53 queries and 2 guesses.
The key idea is to use a strategy that adapts to potentially false answers, leveraging the constraint 
that at least one of two consecutive answers is correct. This allows us to determine x by halving 
the search space in a way that respects the joke constraint.

Algorithms:
- Binary search with adaptive strategy considering potential false answers
- Uses memoized recursive functions to compute optimal split points for queries

Time Complexity: O(n^3 log n) in worst case due to caching and recursive computation
Space Complexity: O(n^2) for memoization tables and storage of candidate numbers
"""

import sys

input = sys.stdin.readline

n = int(input())

good = list(range(1, n + 1))
mid = []


def query(l):
    # Query if the hidden number x is in set l
    print("?", len(l), " ".join(map(str, l)))
    sys.stdout.flush()

    s = input().strip()
    return s == "YES"


from functools import cache


@cache
def solveu(p, q):
    # Recursive function to compute minimal queries needed for a given p,q
    if p + q <= 2:
        return 0

    if p == 2 and q == 1:
        return 2

    if p + q < 10:
        uu, vv = solved(p, q, 0)

        pl = uu
        ql = vv

        pr = p - pl
        qr = q - ql
    else:
        pl = p // 2
        pr = p - pl

        qr = q // 2
        ql = q - qr

    return 1 + max(solveu(pl + ql, pr), solveu(pr + qr, pl))


@cache
def solve(p, q):
    # Another recursive function to compute min queries needed
    if p + q <= 2:
        return 0

    if p == 2 and q == 1:
        return 2

    pl = p // 2
    pr = p - pl

    qr = q // 2
    ql = q - qr

    return 1 + max(solve(pl + ql, pr), solve(pr + qr, pl))


@cache
def solved(p, q, d):
    # Function to decide best split for a query considering d (depth)
    if d > 100:
        return d

    if p + q <= 2:
        return d

    if p == 2 and q == 1:
        return 2 + d

    poss = []

    for i in range(p + 1):
        for j in range(q + 1):
            # Try all splits
            poss.append(
                (
                    max(solved(i + j, p - i, d + 1), solved(p - i + q - j, i, d + 1)),
                    i,
                    j,
                )
            )

    if d == 0:
        # Return indices for best split
        return min(poss)[1:]

    return min(poss)[0]


# Compute max needed queries
mz = solveu(n, 0)
assert mz <= 53


ct = 0
while len(good) + len(mid) > 2:
    # Estimate remaining queries needed
    curr = ct + solveu(len(good), len(mid))
    assert curr <= mz
    mz = min(curr, mz)

    ct += 1
    assert ct <= 53

    p = len(good)
    q = len(mid)

    # Special case: small sets
    if p == 2 and q == 1:
        if query(good):
            mid = []
            continue
        else:
            mid, good = good, mid
            continue

    # Decide how to split sets based on computed values or simple binary split
    if p + q < 10:
        uu, vv = solved(p, q, 0)

        pl = good[:uu]
        pr = good[uu:]

        ql = mid[:vv]
        qr = mid[vv:]
    else:
        pl = good[: p // 2]
        pr = good[p // 2 :]

        ql = mid[q // 2 :]
        qr = mid[: q // 2]

    # Make query on combined left half
    if query(pl + ql):
        good = pl + ql
        mid = pr
    else:
        good = pr + qr
        mid = pl

# Final guesses
poss = good + mid

for v in poss:
    # Try all remaining candidates as guesses
    print("!", v)
    sys.stdout.flush()
    s = input().strip()
    if s == ":)":
        exit()


# https://github.com/VaHiX/CodeForces/