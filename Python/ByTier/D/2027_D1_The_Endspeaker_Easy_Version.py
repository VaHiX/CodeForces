# Problem: CF 2027 D1 - The Endspeaker (Easy Version)
# https://codeforces.com/contest/2027/problem/D1

"""
Problem: D1. The Endspeaker (Easy Version)

Algorithms/Techniques:
- Dynamic Programming with Sliding Window Optimization
- Prefix sums for efficient range sum queries

Time Complexity: O(n * m) per test case, where n is the length of array 'a' and m is the length of array 'b'.
Space Complexity: O(n + m), for prefix sum array and DP array.

This problem involves making an array empty by performing two types of operations:
1. Increase k (no cost)
2. Remove a prefix of array a whose sum is <= b[k], with cost = m - k

We use dynamic programming with a sliding window to optimize the process.
"""

import sys

inp = lambda func=int: list(map(func, sys.stdin.readline().split()))
t = inp()[0]
for _ in range(t):
    n, m = inp()
    a = inp()
    b = inp()
    pre = [0] * (n + 1)
    for i in range(n):
        pre[i + 1] = pre[i] + a[i]  # Compute prefix sums for fast range sum calculation
    dp = [float("inf")] * (n + 1)
    dp[0] = 0  # Base case: 0 cost to make empty array
    for k in range(1, m + 1):
        j = 0
        for i in range(1, n + 1):
            # Shrink the window from left while prefix sum exceeds b[k]
            while j < i and pre[i] - pre[j] > b[k - 1]:
                j += 1
            if j < i:
                # Update dp[i] with minimum cost to reach here using current k
                dp[i] = min(dp[i], dp[j] + m - k)
    print(dp[n] if dp[n] != float("inf") else -1)  # Output result or -1 if impossible


# https://github.com/VaHiX/codeForces/