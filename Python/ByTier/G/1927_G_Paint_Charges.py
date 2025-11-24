# Problem: CF 1927 G - Paint Charges
# https://codeforces.com/contest/1927/problem/G

"""
Algorithm: Dynamic Programming with Greedy Optimization
Time Complexity: O(n^2) where n is the length of the strip
Space Complexity: O(n) for the dp array

This problem is solved using dynamic programming where we determine the minimum number of charges to be used to paint all cells.

The key idea:
1. For each cell, we decide whether to use its charge to the left or right.
2. We use a DP state dp[i] representing the minimum number of charges needed to paint all cells from 1 to i.
3. For each position, we update our DP table considering using the current charge to the left or right.
4. The DP transition handles both directions efficiently by maintaining and updating minimum values across ranges.

Approach:
- We iterate through each position in the grid.
- At each position i, we can use the charge a[i] to paint left or right.
- Use DP to track minimum charges required to cover up to each position.
- Apply optimization to efficiently update ranges with minimal operations.
"""

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    dp = [10**18] * (n + 1)
    dp[0] = 0
    for i in range(n):
        # Propagate minimum values backwards to maintain consistency
        for j in range(i - 1, -1, -1):
            dp[j] = min(dp[j], dp[j + 1])
        # Use charge at i to the right: covers from i to min(i+a[i]-1, n-1)
        dp[i + 1] = min(dp[i + 1], dp[max(0, i + 1 - a[i])] + 1)
        x = dp[i]
        # Iterate over the range that can be painted from position i to the right
        for j in range(i + 1, min(n, i + a[i])):
            # Update x with minimum charge needed to cover cell j
            x = min(x, dp[min(i, max(0, j - a[j] + 1))] + 1)
            # Update dp[j + 1] considering possible coverage from charge at j
            dp[j + 1] = min(dp[j + 1], x + 1)
    print(dp[-1])


# https://github.com/VaHiX/CodeForces/