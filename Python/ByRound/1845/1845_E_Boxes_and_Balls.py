# Problem: CF 1845 E - Boxes and Balls
# https://codeforces.com/contest/1845/problem/E

"""
Algorithm: Dynamic Programming with Optimization
Time Complexity: O(n * k * log(n)) 
Space Complexity: O(n * k)

This solution uses dynamic programming to count the number of different arrangements 
of balls after exactly k moves. The key idea is to track how many ways we can reach 
each position (ball location) after a certain number of moves. 

We optimize by noting that only a few positions (within a window) need to be considered 
at each step, avoiding full iteration through all positions each time.

The approach:
- Identify which boxes have balls (a[i] == 1) and which are empty (a[i] == 0).
- Use a compressed representation of ball positions to reduce state space.
- For each move, update the DP table by considering valid transitions from adjacent 
  positions (ball to empty box).
- Since we're counting arrangements based on ball positions, we calculate the number 
  of valid final configurations after k moves.
"""

import os
import sys

if os.path.exists("in.txt"):
    file = open("in.txt")
    input = file.readline
else:
    input = sys.stdin.readline
from bisect import bisect_left

readi = lambda: int(input())
readis = lambda: list(map(int, input().split()))
reads = lambda: input().rstrip()
readss = lambda: input().split()


def solution():
    n, k = readis()
    a = readis()
    less = sum(a) <= n // 2  # Determine if we use 0s or 1s for compression
    I = [i for i, x in enumerate(a) if x == less]  # List of indices for selected type (0s or 1s)
    dp = [[0] * (k + 1) for _ in range(len(I) + 1)]  # DP table: dp[j][t] = ways to reach pos j after t moves
    dp[0][0] = 1  # Base case
    
    # Process each box
    for i in range(n):
        j0 = bisect_left(I, i)  # Find index in I for position i
        # Iterate around relevant indices, with some bounds
        for j in range(min(i + 1, len(I), j0 + 40), max(0, j0 - 40), -1):
            d = abs(I[j - 1] - i)  # Distance between current and previous ball position
            # Update DP values backward to prevent overwriting
            for t in range(k, d - 1, -1):
                dp[j][t] += dp[j - 1][t - d]  # Accumulate number of paths
                dp[j][t] %= 1000000007  # Modulo operation
    
    # Sum up results where number of moves is even (since we only consider valid final states)
    print(sum(dp[-1][i] for i in range(k, -1, -2)) % 1000000007)


for i in range(1):
    solution()


# https://github.com/VaHiX/CodeForces/