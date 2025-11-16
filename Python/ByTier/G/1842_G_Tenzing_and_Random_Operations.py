# Problem: CF 1842 G - Tenzing and Random Operations
# https://codeforces.com/contest/1842/problem/G

"""
Algorithm: Dynamic Programming with Probability
Time Complexity: O(n^2)
Space Complexity: O(n^2)

This code computes the expected value of the product of elements in array 'a'
after performing 'm' random operations. Each operation selects an index 'i'
uniformly at random and adds 'v' to all elements from index 'i' to 'n'.

The approach uses dynamic programming where dp[i][j] represents the probability
of having exactly 'j' operations that start at or before index 'i'. The transitions
account for how the product changes and how probabilities propagate.

The final result is computed as the sum of all possible products weighted by their
probabilities.
"""

MOD = 10**9 + 7

n, m, v = map(int, input().split())
a = list(map(int, input().split()))

# Precompute modular inverse of n
inv_n = pow(n, -1, MOD)

# dp[i][j] represents the probability of having exactly j operations starting at or before index i
dp = [[0] * (n + 1) for _ in range(n + 1)]

# Base case: 0 operations have been done, so probability = 1
dp[0][0] = 1

# Iterate through each index in the array
for i in range(n):
    # Iterate over all possible numbers of operations that start at or before index i
    for j in range(n):
        # Case 1: No new operation starts at index i
        # Increment the probability of keeping j operations from previous state
        dp[i + 1][j] = (dp[i + 1][j] + dp[i][j] * a[i]) % MOD

        # Case 2: An operation starts at index i and modifies elements from i to n
        # We contribute to the current position's value by adding j * v to the current product
        dp[i + 1][j] = (dp[i + 1][j] + dp[i][j] * j * v) % MOD

        # Case 3: A new operation starts at or after index i, which increases the number of operations
        # This contributes to dp[i+1][j+1] with probability (m - j) * (1/n) * v
        dp[i + 1][j + 1] = (
            dp[i][j] * (m - j) % MOD * ((i + 1) * inv_n % MOD) % MOD * v % MOD
        )

# Sum up all final probabilities to get expected value
print(sum(dp[-1]) % MOD)


# https://github.com/VaHiX/CodeForces/