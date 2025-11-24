# Problem: CF 1842 H - Tenzing and Random Real Numbers
# https://codeforces.com/contest/1842/problem/H

"""
Algorithm: Dynamic Programming with Bitmasking
Purpose: Calculate the probability that all given constraints on random variables are satisfied.
Time Complexity: O(2^n * n), where n is the number of variables.
Space Complexity: O(2^n), for storing the DP states.

The solution uses a bitmask DP approach where:
- Each bit in the mask represents whether a variable is assigned a value.
- For each subset of variables assigned, we check if satisfying the constraints leads to a valid configuration.
- Finally, we compute the ratio of valid configurations to the total possible configurations.

Constraints:
- Variables are uniformly distributed between 0 and 1.
- Conditions can be of two types: x_i + x_j <= 1 or x_i + x_j >= 1.
"""

MOD = 998244353


def main():
    import sys

    n, m = map(int, sys.stdin.readline().split())
    # G[i][0] stores bits of variables that must be <= 1 when x_i is added
    # G[i][1] stores bits of variables that must be >= 1 when x_i is added
    G = [[0, 0] for _ in range(n)]
    for _ in range(m):
        t, i, j = map(int, sys.stdin.readline().split())
        i -= 1
        j -= 1
        # Set the bit corresponding to variable j to indicate constraint
        G[i][t] |= 1 << j
        G[j][t] |= 1 << i

    size = 1 << n
    dp = [0] * size
    dp[0] = 1  # Base case: no variables assigned

    # Iterate through all possible states (subsets of variables)
    for S in range(size):
        for i in range(n):
            if not (S & (1 << i)):
                # Check if condition x_i + x_j <= 1 is satisfied for all j in G[i][0]
                if (G[i][0] | S) == S:
                    new_mask = S | (1 << i)
                    dp[new_mask] = (dp[new_mask] + dp[S]) % MOD
                # Check if condition x_i + x_j >= 1 is satisfied for all j in G[i][1]
                if (G[i][1] | S) == S:
                    new_mask = S | (1 << i)
                    dp[new_mask] = (dp[new_mask] + dp[S]) % MOD

    # Compute the denominator: total number of possibilities for n variables
    # Each variable has 2*n possibilities (since it's real in [0,1], but for combinatorics we use n!)
    denominator = 1
    for i in range(1, n + 1):
        denominator = denominator * i % MOD  # factorial of n
        denominator = denominator * 2 % MOD  # each variable has range [0,1], thus multiply by 2

    # Invert denominator using modular multiplicative inverse
    inv_denominator = pow(denominator, MOD - 2, MOD)
    # Result = valid configurations / total configurations
    ans = dp[(1 << n) - 1] * inv_denominator % MOD
    print(ans)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/