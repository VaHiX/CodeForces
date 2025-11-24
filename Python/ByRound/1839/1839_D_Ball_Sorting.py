# Problem: CF 1839 D - Ball Sorting
# https://codeforces.com/contest/1839/problem/D

"""
Algorithm: Dynamic Programming with optimization for ball sorting problem
Techniques: 
- Dynamic Programming with state transitions
- Sliding window / optimization techniques for finding longest increasing subsequences

Time Complexity: O(n^3) where n is the number of balls
Space Complexity: O(n^2) for the DP table

The problem involves reordering balls to get sequence [1,2,3,...,n] using:
1. Inserting color 0 balls (at most k times)
2. Moving non-zero balls adjacent to 0 balls (costs 1 coin each)

This solution uses DP where dp[j][i] represents the longest increasing subsequence ending at position i with at most j operations of type 1 (inserting 0).
"""

import sys

input = sys.stdin.readline

t = int(input())
for _ in range(t):
    n = int(input())
    a = [*map(int, input().split())]
    dp = [[0] * n for _ in range(n + 1)]
    dp[0][0] = 1
    for j in range(n + 1):
        if j == 0:
            # Initialize for case when no color 0 balls are inserted
            for i in range(n):
                if i > 0:
                    if a[i] > a[i - 1]:
                        dp[j][i] = dp[j][i - 1] + 1
                    else:
                        break
        else:
            # For cases with j color 0 balls inserted
            for i in range(1, n):
                maxi = 0
                # If current ball can extend previous sequence
                if a[i - 1] < a[i]:
                    maxi = dp[j][i - 1]
                # Check all previous positions for possible extensions
                for k in range(i - 1):
                    if a[k] < a[i]:
                        maxi = max(maxi, dp[j - 1][k])
                dp[j][i] = maxi + 1
            # Update last element with maximum from previous state
            dp[j][i] = max(dp[j - 1][i], dp[j][i])

    ans = [0] * (n + 1)
    for j in range(n + 1):
        maxi = max(dp[j])
        if dp[j][-1] == maxi:
            # If longest sequence ends at last element
            ans[j] = max(ans[j], maxi)
            if j > 0:
                ans[j] = max(ans[j - 1], ans[j])
        else:
            # Otherwise take the value at last element 
            ans[j] = max(ans[j], dp[j][-1])
            if j > 0:
                ans[j] = max(ans[j - 1], ans[j])
            if j < n:
                # Propagate maximum to next state
                ans[j + 1] = max(ans[j], ans[j + 1], maxi)

    print(*[n - i for i in ans[1:]])


# https://github.com/VaHiX/CodeForces/