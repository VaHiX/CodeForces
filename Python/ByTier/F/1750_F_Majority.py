# Problem: CF 1750 F - Majority
# https://codeforces.com/contest/1750/problem/F

"""
Algorithm: Dynamic Programming with Memoization
Time Complexity: O(n^2)
Space Complexity: O(n^2)

The problem involves counting "rated" binary strings of length n, where a string is rated if all servers 
can be turned on using a specific operation called "electricity spread". The operation allows turning on 
offline servers in a range [i, j] if the number of online servers in that range is at least half the range size.

This solution uses dynamic programming. It defines f[L] as the number of rated strings of length L, and 
maintains a dictionary w[L][y] which represents how many ways we can form a string of length L with a 
specific "diagonal" parameter y. The diagonal parameter y reflects the number of non-zero elements in a 
specific structure used during transitions.

The recurrence builds upon previous results considering two types of transitions:
1. Direct recursive structure (from previous f values)
2. Through overlapping subproblems (using diagonal array)

Finally, it computes f[n] and outputs the result modulo m.
"""

n, MOD = [int(t) for t in input().split()]
f = [0, 1, 1, 2, 4]  # Base cases for small lengths
w = [{}, {}, {}, {}, {}]  # Memoization for transition counts
diagonal = [0] * (2 * n)  # Tracks diagonal contributions for transitions

# Iterate from length 5 to n to calculate f values
for L in range(5, n + 1):
    # Copy previous transition counts
    ways = {x: w[-1][x] for x in w[-1]}

    # Handle odd-length case
    if L & 1:
        for y in range(1, L // 2):
            if not y in ways:
                ways[y] = 0
            # Update ways by combining with previous f values
            ways[y] += f[y] * f[L // 2 - y]

    # Update ways with diagonal contribution
    for y in ways:
        # Add contribution from previous diagonal
        ways[y] += f[y] * diagonal[L - 2 * y - 1]
        ways[y] %= MOD  # Ensure modular arithmetic

    # Update diagonal array
    for y in ways:
        diagonal[L + y] += ways[y]
        diagonal[L + y] %= MOD

    # Calculate f[L] using derived formula
    f.append((pow(2, L - 2, MOD) - sum(ways.values())) % MOD)
    w.append(ways)  # Store for next iteration

# Output final result
print(f[n])


# https://github.com/VaHiX/CodeForces/