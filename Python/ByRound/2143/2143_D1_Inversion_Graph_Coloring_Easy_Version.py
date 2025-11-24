# Problem: CF 2143 D1 - Inversion Graph Coloring (Easy Version)
# https://codeforces.com/contest/2143/problem/D1

"""
D1. Inversion Graph Coloring (Easy Version)
Algorithms/Techniques: Dynamic Programming on Subsequences with State Compression

Time Complexity: O(n^3) per test case
Space Complexity: O(n^2) for the DP table

This problem asks us to count the number of "good" subsequences, where a good subsequence
can be colored red or blue such that for every pair in the subsequence with b_i > b_j,
the indices i and j have different colors. This is equivalent to checking if the subsequence
is "invertible" — no two elements form an inversion that would require same color.

We use dynamic programming:
- dp[i][j] represents the number of ways to form a good subsequence ending at position i
  with the last element having value j.
- For each new element in the input sequence, we extend all valid subsequences by including it,
  accounting for valid colorings using transitions between states.

The solution tracks how many valid colorings exist at each step as we build up subsequences.
"""

from sys import stdin

input = lambda: stdin.readline().rstrip()
mod = 1000000007


def solve():
    n = int(input())
    a = list(map(int, input().split()))
    # dp[l][r] stores number of good subsequences ending at index l with last value r
    dp = [[0] * (n + 1) for _ in range(n + 1)]
    dp[0][0] = 1  # base case: empty subsequence
    
    for x in a:
        # Compute transitions for current element x
        # Iterate over all possible previous rightmost values (from 0 to x)
        for r in range(x + 1):
            # For each such value r, iterate backwards from x
            # to update contributions where index j < i and value a[j] > a[i]
            for l in range(x, r - 1, -1):
                dp[x][r] = (dp[x][r] + dp[l][r]) % mod
        
        # Update dp values for larger indices with smaller last values
        for l in range(x + 1, n + 1):
            for r in range(x, -1, -1):
                dp[l][x] = (dp[l][x] + dp[l][r]) % mod
    
    # Return total number of good subsequences
    return sum(sum(x) % mod for x in dp) % mod


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/codeForces/