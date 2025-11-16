# Problem: CF 1920 E - Counting Binary Strings
# https://codeforces.com/contest/1920/problem/E

"""
Algorithm: Dynamic Programming with State Transition
Purpose: Count binary strings with exactly n good substrings and max good substring length k.
Time Complexity: O(n^2 * k) per test case
Space Complexity: O(n^2) for the DP array

The problem is solved using dynamic programming where dp[i][j] represents the number of ways to form 
i good substrings ending with a good substring of length j. A good substring is defined as one that 
contains exactly one '1'.

The recurrence builds valid strings by extending existing ones with substrings of length 1 to k,
ensuring that no good substring exceeds length k.

Notes:
- The state dp[i][j] stores the number of valid binary strings with exactly i good substrings,
  ending with a good substring of length j.
- A good substring of length l contributes l positions to the count of good substrings.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Helper function to map 2D state (u, v) to 1D array index
    return u * (n + 1) + v


t = int(input())
ans = []
mod = 998244353
for _ in range(t):
    n, k = map(int, input().split())
    # dp array for dynamic programming
    dp = [0] * ((n + 1) * (n + 1))
    
    # Initialize base case: 1 good substring ending with substring of length 1
    for i in range(1, n + 1):
        dp[i] = 1
    
    # Iterate through all possible counts of good substrings
    for i in range(n):
        # For each possible ending length of good substring
        for j in range(1, n + 1):
            # Skip if this state is unreachable
            if not dp[f(i, j)]:
                continue
            u = dp[f(i, j)] % mod  # Current number of ways to reach this state
            # Try extending with good substrings of length 1 to k-j+1
            for l in range(1, k - j + 2):
                v = i + j * l  # New number of good substrings after extension
                if v > n:
                    break
                # Accumulate the number of ways to reach (v, l) state
                dp[f(v, l)] += u
    
    # Sum all valid final states (ending with good substring of length 1)
    ans0 = 0
    for i in range(f(n, 1), f(n + 1, 0)):
        ans0 += dp[i]
    ans0 %= mod
    ans.append(ans0)

sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/