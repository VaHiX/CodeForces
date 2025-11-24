# Problem: CF 2026 C - Action Figures
# https://codeforces.com/contest/2026/problem/C

"""
C. Action Figures

Purpose:
This code solves the problem of minimizing the cost for Monocarp to buy all action figures 
from a set of n figures, where each figure i is available from day i to day n and costs i coins.
Monocarp can visit the shop on certain days (given by a binary string). If he buys at least two
figures in one day, he gets the most expensive one for free.

The approach uses a greedy strategy combined with prefix-like logic, where we track how early 
we can "delay" buying figures to apply discounts optimally. 

Algorithms:
- Greedy approach with backward iteration and count tracking.
- Efficiently computes the best day to buy each set of figures to minimize cost.

Time Complexity: O(N) per test case, where N is the number of days/figures.
Space Complexity: O(1), only using a few variables for computation.

"""

import sys

input = sys.stdin.readline
Q = int(input())
for _ in range(Q):
    N = int(input())
    S = input()[:-1]  # Read string without newline
    result = N * (N + 1) // 2  # Total cost if no discounts are applied
    count = 0  # Tracks how many figures we can delay buying due to discount benefits
    for i in range(N - 1, -1, -1):  # Iterate from last day to first
        if S[i] == "1":  # If Monocarp can visit the shop on this day
            if i + count - 1 < 0:  # If we're trying to delay beyond valid range
                count += 1
            else:
                count -= 1  # Use discount, reduce pending delay
                result -= i + 1  # Deduct cost of the most expensive figure in current batch
        else:
            count += 1  # Increase delay as no visit on this day
            if count > 0:
                count = 0  # Reset when delay is positive (no benefit)
    print(result)


# https://github.com/VaHiX/codeForces/