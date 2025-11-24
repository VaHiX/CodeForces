# Problem: CF 2119 D - Token Removing
# https://codeforces.com/contest/2119/problem/D

"""
Problem: Token Removing
Algorithm: Dynamic Programming with Combinatorial Mathematics
Time Complexity: O(N^2)
Space Complexity: O(N)

This solution computes the sum of weights over all valid sequences of length N.
A valid sequence a of length N satisfies 0 <= a[i] <= i for all i.
The weight f(a) represents the number of ways to remove tokens based on the sequence.

We use dynamic programming where dp[r] represents the number of ways to place r tokens
at positions such that the cumulative removal process respects the sequence constraints.

The recurrence relation is derived from considering how each element in the sequence
affects the number of possible token removal orders.
"""

for T in range(int(input())):
    N, M = map(int, input().split())
    dp = [1] + [0] * N  # Initialize dp[0] = 1, rest = 0
    for v in range(1, N + 1):  # Iterate through each position v in the sequence
        for r in range(v, 0, -1):  # For each token placement count r from v down to 1
            # Update dp[r] by adding contributions from previous states
            dp[r] += dp[r - 1] * (N + 1 - v) * (v - (r - 1)) % M
    print(sum(dp) % M)  # Output total sum modulo M


# https://github.com/VaHiX/codeForces/