# Problem: CF 1872 D - Plus Minus Permutation
# https://codeforces.com/contest/1872/problem/D

"""
Problem: Find the maximum possible score of a permutation of length n,
         where the score is defined as:
         sum(p_i for i divisible by x) - sum(p_i for i divisible by y)

Algorithms/Techniques: 
- Mathematical optimization using inclusion-exclusion principle
- Arithmetic series summation
- GCD computation for least common multiple

Time Complexity: O(1) per test case
Space Complexity: O(1)

The approach:
1. Count numbers divisible by x (cx) and y (cy)
2. Subtract those divisible by both x and y (using LCM) to avoid double counting
3. Assign largest values to positions divisible by x (to maximize positive contribution)
4. Assign smallest values to positions divisible by y (to minimize negative contribution)
5. Use arithmetic series formulas to compute sums efficiently
"""

import math
import sys

sys.setrecursionlimit(100000)


def my_input():
    return sys.stdin.readline().strip()


def solve():
    n, x, y = map(int, my_input().split())
    # Count multiples of x (excluding those also multiples of y)
    cx = n // x
    # Count multiples of y (excluding those also multiples of x)
    cy = n // y
    # Count multiples of LCM(x, y) to exclude from both cx and cy
    c = n // (x * y // math.gcd(x, y))
    cx -= c
    cy -= c
    # The maximum score is achieved by taking:
    # - The largest cx numbers for positions divisible by x
    # - The smallest cy numbers for positions divisible by y
    # Sum using arithmetic series formula
    return cx * (n - cx) + cx * (cx + 1) // 2 - cy * (cy + 1) // 2


def main():
    print("\n".join([str(solve()) for _ in range(int(my_input()))]))


main()


# https://github.com/VaHiX/CodeForces/