# Problem: CF 1780 E - Josuke and Complete Graph
# https://codeforces.com/contest/1780/problem/E

"""
Algorithm: Count Unique GCD Values in a Range of Vertices
Techniques: Mathematical analysis with optimization for large ranges

Time Complexity: O(sqrt(r)) per test case
Space Complexity: O(1)

The problem asks to count how many unique GCD values exist between pairs of integers in the range [l, r].
In a complete graph where edge weights are gcd(u, v), we compute all unique values of gcd(i, j) for i, j in [l, r].

Key insights:
- For each divisor d of numbers in [l, r], we count how many pairs (i, j) have gcd(i, j) = d.
- This is equivalent to counting pairs (i, j) where i = d*i', j = d*j' and gcd(i', j') = 1.
- We use inclusion-exclusion and mathematical optimizations to avoid checking all pairs directly.

Optimization:
- When the range d = r - l is small, we iterate over divisors directly.
- When d is large, we use a more advanced inclusion-exclusion approach with block-wise calculations.

The code uses a two-phase approach:
1. For small ranges, direct iteration over divisors.
2. For large ranges, optimized block-wise calculations with inclusion-exclusion principle.
"""

import sys

readline = sys.stdin.readline

T = int(readline())
for t in range(T):
    l, r = map(int, readline().split())
    r += 1  # Make r inclusive
    d = r - l
    ans = d // 2  # Base case: we know that gcd(i, i) = i, but since no self-loops, we consider unique pairs
    l -= 1
    r -= 1
    if d <= 10**6:
        # Direct computation for small ranges
        for i in range(d // 2 + 1, d + 1):
            ans += r // i - l // i - 1
    else:
        # Optimized computation for large ranges using inclusion-exclusion or block-wise approach
        for j in range(r // d, r // (d // 2 + 1) + 1):
            ans += (min(r // j + 1, d + 1) - max(r // (j + 1) + 1, d // 2 + 1)) * j
        for j in range(max(1, l // d), l // (d // 2 + 1) + 1):
            ans -= (min(l // j + 1, d + 1) - max(l // (j + 1) + 1, d // 2 + 1)) * j
        ans -= d - (d // 2)
    print(ans)


# https://github.com/VaHiX/CodeForces/