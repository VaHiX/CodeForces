# Problem: CF 2124 F1 - Appending Permutations (Easy Version)
# https://codeforces.com/contest/2124/problem/F1

"""
F1. Appending Permutations (Easy Version)
Algorithm: Dynamic Programming with Difference Array Optimization
Time Complexity: O(n^3)
Space Complexity: O(n^2)

This problem involves counting valid permutations of length n that can be formed 
by appending cyclic shifts of arrays [1,2,...,s] while respecting m restrictions on positions.

The solution uses dynamic programming where we track how many valid sequences end at each position,
and use a difference array technique to efficiently update ranges. The key insight is that
each operation allows us to append a cyclic shift of [1..s], which affects a range in the final array.
Restrictions are enforced by tracking forbidden values and using modular arithmetic.

The approach processes the problem from left to right, keeping track of valid ways to fill each prefix,
and applying constraints through difference arrays for efficient range updates.
"""

from sys import stdin

input = lambda: stdin.readline().rstrip()
MOD = 998244353


def min2(x, y):
    return x if x < y else y


def solve():
    n, m = map(int, input().split())
    b = [[n] * (n + 1) for _ in range(n + 1)]
    # Initialize forbidden positions with value n (default)
    for _ in range(m):
        i, x = (num - 1 for num in map(int, input().split()))  # Convert to 0-indexed
        b[i][x] = i  # Mark position i cannot have value x

    # Propagate forbidden positions backwards to find minimum constraint
    for p in range(n - 1, -1, -1):
        for i in range(n):
            b[p][i] = min2(b[p][i], b[p + 1][i + 1])

    # Difference array to efficiently update ranges of dp values
    hav = [[0] * (n + 1) for _ in range(n + 2)]
    dp = [1] + [0] * n  # dp[i] represents number of ways to form prefix of length i

    # Process prefixes from left to right
    for l in range(n + 1):
        l1 = l + 1
        # For all possible shifts starting at position l
        for i in range(1, n - l + 1):
            x = dp[l]
            # Apply backward constraint if valid
            if l - i >= 0 and b[l - i][0] >= l:
                x -= dp[l - i]
            # Compute range to update using difference array
            r1 = b[l][i] + 1
            hav[l1][i] = (hav[l1][i] + x) % MOD
            hav[r1][i] = (hav[r1][i] - x) % MOD

        # Propagate updates from previous layer to current
        for i in range(n + 1):
            hav[l1][i] = (hav[l1][i] + hav[l][i]) % MOD

        # Update dp values using cumulative values in hav and b
        for i in range(1, b[l][0] - l + 1):
            dp[l + i] = (dp[l + i] + dp[l] + hav[l][i]) % MOD

    return dp[-1]


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/CodeForces/