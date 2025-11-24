# Problem: CF 2111 F - Puzzle
# https://codeforces.com/contest/2111/problem/F

"""
F. Puzzle

Purpose:
This code solves a puzzle arrangement problem where we need to place square puzzle pieces 
on a grid such that the ratio of the perimeter to area of the connected component equals p/s.
The solution generates a valid shape by constructing a rectangle with specific dimensions.

Algorithms/Techniques:
- Mathematical reasoning: The key insight is to construct a rectangle of size i x j, where:
    - Perimeter = 2*(i + j)
    - Area = i * j
    - Ratio = 2*(i + j) / (i * j) = p / s
    - Rearranging gives: i * j * p = 2 * (i + j) * s
- Brute-force search over possible rectangle dimensions up to MAX_RANGE.
- Greedy placement of pieces in a specific order to ensure connectivity.

Time Complexity:
O(MAX_RANGE^2 * MAX_RANGE) = O(201^3) ≈ O(8.2 million) per test case

Space Complexity:
O(MAX_RANGE^2) for the search space and O(50000) for output storage
"""

import sys
from math import gcd

if 1:
    input = lambda: sys.stdin.readline().strip()
    inf = float("inf")

    def I():
        return input()

    def II():
        return int(input())

    def MII():
        return map(int, input().split())

    def LI():
        return list(input().split())

    def LII():
        return list(map(int, input().split()))

    def LFI():
        return list(map(float, input().split()))

    def GMI():
        return map(lambda x: int(x) - 1, input().split())

    def LGMI():
        return list(map(lambda x: int(x) - 1, input().split()))


MAX_RANGE = 201


def __Main__():
    p, s = MII()
    g = gcd(p, s)
    p, s = p // g, s // g
    for i in range(1, MAX_RANGE):  # Try all possible rectangle widths
        for j in range(1, MAX_RANGE):  # Try all possible rectangle heights
            np = (i + j) << 1  # Perimeter of the rectangle: 2 * (i + j)
            if np % p != 0:  # Check if we can get exact ratio
                continue
            MIN_S, MAX_S = i + j - 1, i * j  # Bounds on area for connected component
            S = np // p * s  # Calculate required area from the given ratio
            if S <= 50000 and MIN_S <= S <= MAX_S:  # Check if area is feasible and within limit
                outs = []
                outs.append(str(S))  # First line outputs count of pieces

                # Fill top row (x from 1 to i, y = 1)
                for ni in range(1, i + 1):
                    outs.append("{} {}".format(ni, 1))
                    S -= 1

                # Fill left column (x = 1, y from 2 to j)
                for nj in range(2, j + 1):
                    outs.append("{} {}".format(1, nj))
                    S -= 1

                # Fill internal squares starting from (2,2) up to (i,j)
                for ni in range(2, i + 1):
                    for nj in range(2, j + 1):
                        if S > 0:
                            outs.append("{} {}".format(ni, nj))
                            S -= 1
                        else:
                            break
                    if S <= 0:
                        break
                print("\n".join(map(str, outs)))
                return
    print(-1)


t = II()
for _ in range(t):
    __Main__()


# https://github.com/VaHiX/codeForces/