# Problem: CF 2123 E - MEX Count
# https://codeforces.com/contest/2123/problem/E

"""
E. MEX Count

Purpose:
This code computes for each k (0 <= k <= n), the number of possible MEX values 
that can be obtained by removing exactly k elements from the given array.

Approach:
1. For a given array, we count occurrences of each value (0 to n).
2. We then compute prefix sums on segment updates to determine how many times
   each MEX value is achievable after removing k elements.
3. The key idea is that MEX can be at most n+1 (since there are at most n elements),
   and we simulate what MEX values are possible by checking removals.

Algorithms/Techniques:
- Frequency counting
- Difference array technique for range updates
- Prefix sum computation

Time Complexity: O(n) per test case
Space Complexity: O(n)
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    f = [0] * (n + 1)
    for j in range(n):
        f[a[j]] += 1
    b = []
    # Find the first index where frequency is zero
    for j in range(f.index(0) + 1):
        b.append((f[j], n - j))
    out = [0] * (n + 1)
    for l, r in b:
        out[l] += 1
        if r < n:
            out[r + 1] -= 1
    for j in range(1, n + 1):
        out[j] += out[j - 1]
    print(*out)


# https://github.com/VaHiX/codeForces/