# Problem: CF 1814 B - Long Legs
# https://codeforces.com/contest/1814/problem/B

"""
Code purpose:
This program finds the minimum number of moves for a robot to reach a cell (a, b) from (0, 0) 
in an infinite grid, where the robot has adjustable leg lengths. The robot can either jump 
to a cell at distance `m` (leg length) in the x or y direction, or increase its leg length by 1.

Algorithm:
1. Use a heuristic search approach with a starting guess for the leg length `s`.
2. Iterate decreasing values of `s` and compute the minimum moves needed using:
   - `s - 1`: number of times we need to increase leg length (from 1 to s)
   - `ceil(a / s)`: number of jumps in x-direction
   - `ceil(b / s)`: number of jumps in y-direction
3. Track the minimum moves among all valid leg lengths.

Time Complexity: O(1) amortized due to the fixed iteration range (500) and sqrt(a+b) estimation.
Space Complexity: O(1) - only using a few variables.
"""

import sys
from math import ceil, isqrt

input = lambda: sys.stdin.readline().rstrip()


def solution(a, b):
    # Start with an estimate for leg length based on sqrt(a + b)
    s = isqrt(a + b) + 100
    res = 10**12  # Initialize with a large value
    
    # Iterate through possible leg lengths (decreasing)
    for j in range(500):
        s = max(1, s - 1)  # Decrease leg length, ensuring it doesn't go below 1
        # Compute total moves: 
        # (s - 1) steps to increase leg length to s
        # ceil(a / s) jumps in x direction
        # ceil(b / s) jumps in y direction
        res = min(res, s - 1 + ceil(a / s) + ceil(b / s))
    
    return res


for _ in range(int(input())):
    a, b = [int(i) for i in input().split()]
    print(solution(a, b))


# https://github.com/VaHiX/CodeForces/