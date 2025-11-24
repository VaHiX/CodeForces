# Problem: CF 2092 E - She knows...
# https://codeforces.com/contest/2092/problem/E

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
mod = 1000000007


def pw(a, b):
    ret = 1
    while b:
        if b & 1:  # If exponent is odd, multiply result by base
            ret = ret * a % mod
        a = a * a % mod  # Square the base
        b >>= 1  # Halve the exponent
    return ret


T = int(input())
for _ in range(T):
    n, m, k = map(int, input().split())
    edge = 2 * n + 2 * m - 8  # Total edges of the board's grid minus corner edges
    cnt = 0
    for _ in range(k):
        i, j, c = map(int, input().split())
        if (i in [1, n]) ^ (j in [1, m]):  # If cell is on boundary but not corner
            edge -= 1  # Remove this edge from consideration
            cnt += c  # Count the color value for parity check
    
    if edge:  # If there are edges left to consider
        print(pw(2, n * m - k - 1))  # Answer is 2^(remaining_cells - 1)
    else:  # If no edges remain
        if cnt & 1:  # If the sum of colors on boundary is odd
            print(0)  # Impossible to satisfy parity condition
        else:
            print(pw(2, n * m - k))  # Answer is 2^(remaining_cells)

"""
Purpose: Calculate number of valid ways to repaint a board such that number of adjacent cells with different colors is even.
Algorithms/Techniques: 
    - Binary exponentiation (fast power)
    - Graph edge counting and parity
    - Modular arithmetic

Time Complexity: O(T * k + T * log(mod)) where T is number of test cases, k is total input size
Space Complexity: O(1) constant space usage
"""


# https://github.com/VaHiX/codeForces/