# Problem: CF 2002 F1 - Court Blue (Easy Version)
# https://codeforces.com/contest/2002/problem/F1

"""
Algorithm: Dynamic Programming with GCD constraint
Time Complexity: O(n * m * log(min(n, m))) where log factor comes from GCD computation
Space Complexity: O(100 * 100) = O(1) since we only store a fixed-size DP table

This solution uses dynamic programming to find the maximum score achievable
under the constraint that gcd(WL, WF) <= 1 after every round.
We use a sliding window approach by only considering the last 100 values
of WL and WF due to the nature of the GCD constraint, which means we only
need to track a small portion of the full state space.
"""

import math

T = int(input())
for _ in range(T):
    n, m, l, f = map(int, input().split())
    # Use a fixed-size DP table to optimize space, only tracking last 100 wins
    dp = [[0 for _ in range(101)] for _ in range(101)]
    # Start from a point where we are guaranteed to have valid GCDs
    nn = max(0, n - 100)
    mm = max(0, m - 100)
    ans = 0
    for i in range(nn, n + 1):
        for j in range(mm, m + 1):
            # Base case: if we're at the starting point, set it to valid
            if i == nn or j == mm:
                dp[i - nn][j - mm] = 1
            # Check if current state is valid (gcd constraint)
            elif math.gcd(i, j) == 1:
                # Update DP based on previous valid states
                dp[i - nn][j - mm] = dp[i - nn - 1][j - mm] or dp[i - nn][j - mm - 1]
            # Track maximum score if current state is valid
            if dp[i - nn][j - mm]:
                ans = max(ans, i * l + j * f)
    print(ans)


# https://github.com/VaHiX/CodeForces/