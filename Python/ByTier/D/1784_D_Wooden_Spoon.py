# Problem: CF 1784 D - Wooden Spoon
# https://codeforces.com/contest/1784/problem/D

"""
Code Purpose:
This code solves the "Wooden Spoon" problem for a single-elimination tournament.
The task is to compute, for each player, how many of the (2^n)! possible bracket arrangements
will result in that player winning the "Wooden Spoon" award.
The Wooden Spoon winner is defined by a specific losing sequence in the tournament tree.

Algorithm:
- Dynamic Programming with bitmask and combinatorics
- The DP state tracks the number of ways to arrange players such that a specific
  player ends up in a specific position in the losing sequence
- Combinatorics are used to compute binomial coefficients efficiently using precomputed factorials

Time Complexity: O(2^(2n)) due to the nested iterations over the DP states
Space Complexity: O(2^n) for the DP arrays and auxiliary arrays
"""

from sys import stdin, stdout

N = 998244353

# Precompute powers of 2
po2 = [1]
for i in range(20):
    po2.append(po2[-1] * 2)

# Precompute factorials and inverse factorials
fact = [1]
for i in range(1, 1048581):
    fact.append((fact[-1] * i) % N)

fact_inv = [0] * (1048581)
fact_inv[1048580] = pow(fact[1048580], N - 2, N)

for i in range(1048579, -1, -1):
    fact_inv[i] = (fact_inv[i + 1] * (i + 1)) % N

n = int(stdin.readline())

# Initialize DP with all arrangements where the last match (leaf) is computed
dp = [0] * (po2[n])
dp[-1] = fact[po2[n]]

# Iterate through each round of the tournament
for d in range(n):
    # Create new DP array for next round
    dp2 = [0] * (po2[n])

    # Precompute g: cumulative sum for combinations
    g = [0] * (po2[n - d - 1])
    for s in range(po2[n - d - 1], po2[n]):
        g.append(
            (
                g[-1]
                + (fact[s - 1] * fact_inv[po2[n - d - 1] - 1])
                % N
                * fact_inv[s - po2[n - d - 1]]
            )
            % N
        )

    # Compute dp2 values using the recurrence relation
    temp_sum = 0
    for x in range(po2[n] - 2 - d, po2[n - d - 1] - 2, -1):
        temp_sum = (
            temp_sum
            + ((dp[x + 1] * fact_inv[x + 1]) % N * fact[po2[n - d - 1]])
            % N
            * fact[x + 1 - po2[n - d - 1]]
        ) % N
        temp_factor = (
            (fact[x] * fact_inv[po2[n - d - 1] - 1])
            % N
            * fact_inv[x - po2[n - d - 1] + 1]
        ) % N
        dp2[x] = (temp_sum * temp_factor) % N

    # Update dp for next iteration
    dp = dp2

# Output the results for each player in reversed order of indexing  
for x in range(po2[n] - 1, -1, -1):
    stdout.write(str(dp[x]) + "\n")


# https://github.com/VaHiX/CodeForces/