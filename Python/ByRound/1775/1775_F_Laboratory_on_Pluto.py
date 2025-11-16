# Problem: CF 1775 F - Laboratory on Pluto
# https://codeforces.com/contest/1775/problem/F

"""
Code Purpose:
This code solves the problem of constructing a laboratory on Pluto using n square blocks such that the total perimeter (number of outside walls) is minimized. 
For u=1: It outputs one optimal configuration of the lab.
For u=2: It calculates the number of distinct ways to achieve the optimal perimeter, modulo a prime number m.
The approach involves:
1. For u=1: Constructing a rectangular arrangement with dimensions close to sqrt(n) to minimize perimeter.
2. For u=2: Using dynamic programming to count valid configurations.

Algorithms/Techniques:
1. Mathematical optimization to find dimensions minimizing perimeter.
2. Dynamic programming for counting configurations.
3. Fast I/O for handling large inputs.

Time Complexity:
- For u=1: O(sqrt(n)) per test case.
- For u=2: O(n^2) due to nested loops and DP computation.

Space Complexity: 
- O(n) for storing DP states and grid configurations.

Note: The actual implementation has some inconsistencies in handling the cases for u=1 and u=2, but this summary reflects the core idea.
"""

import os
import sys
from io import BytesIO, IOBase

BUFSIZE = 8192  # Buffer size for fast I/O

# Fast input reading using readline instead of input()
input = lambda: sys.stdin.readline().rstrip("\r\n")

def I():
    """Read a single string from input."""
    return input()

def II():
    """Read a single integer from input."""
    return int(input())

def MI():
    """Read multiple integers from a single line."""
    return map(int, input().split())

from math import ceil, sqrt
from types import GeneratorType

# Read input: testcase count and query type (x=1 for construction, x=2 for counting)
testcase, x = MI()

if x == 1:
    # Case x=1: Construct one optimal rectangular lab layout
    # Strategy: Find h and w close to sqrt(n) to minimize perimeter 2*(h+w)
    for _ in range(testcase):
        n = II()
        
        # Start with h = floor(sqrt(n)) and compute w = ceil(n/h)
        # This gives a rectangle close to square shape
        h = int(sqrt(n))
        w = ceil(n / h)
        
        # Create grid with height h and width w
        grid = [["." for _ in range(w)] for _ in range(h)]
        
        # Fill grid with n blocks (marked as '#'), left to right, top to bottom
        for i in range(h):
            for j in range(w):
                if n:
                    grid[i][j] = "#"
                    n -= 1
                else:
                    break

        # Output dimensions and grid
        print(h, w)
        for i in range(h):
            print("".join(grid[i]))
else:
    # Case x=2: Count distinct configurations achieving optimal perimeter
    # For each test case, we count ways to arrange n blocks with minimum perimeter
    
    m = II()  # Prime modulus for answer
    
    # Precompute DP table f[j] = number of ways to fill j blocks using composition
    # f[j] = sum of f[j-i] for all i >= 1 (counts compositions of j)
    # This uses the convolution approach: for each block size i, count compositions
    f = [0 for _ in range(700)]
    f[0] = 1  # Base case: one way to fill 0 blocks (empty)
    
    # DP: f[j] counts number of compositions (ordered partitions) of j
    # For each possible block size i, add contribution from f[j-i]
    for i in range(1, 700):
        for t in range(4):  # Iterate 4 times to accumulate contributions
            for j in range(i, 700):
                f[j] += f[j - i]  # Add ways to fill remaining (j-i) blocks
                f[j] %= m  # Keep result modulo m

    for _ in range(testcase):
        n = II()
        
        # Find initial dimensions close to square for minimum perimeter
        h = int(sqrt(n))
        w = ceil(n / h)
        
        # Optimize dimensions: adjust h and w to minimize difference
        # while keeping w - h <= 1 (closest to square)
        while w - h > 1:
            w -= 1
            h += 1

        # Optimal perimeter = 2 * (h + w)
        length = 2 * (h + w)
        res = 0
        
        # Try all rectangles with same perimeter and count valid configurations
        # We try (h, w), (h-1, w+1), (h-2, w+2), ... while h*w >= n
        while h * w >= n:
            # For this dimension pair, count ways to arrange n blocks
            # f[h*w - n] counts ways to leave (h*w - n) empty positions
            # Multiply by (1 + (h != w)) to account for rectangle symmetry:
            #   If h == w (square): only 1 configuration
            #   If h != w: can flip to get (w, h) as different configuration
            res += f[h * w - n] * (1 + (h != w))
            res %= m
            
            # Try next dimension pair with same perimeter
            h -= 1
            w += 1

        print(length, res)

# https://github.com/VaHiX/CodeForces/