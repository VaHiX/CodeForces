# Problem: CF 2036 F - XORificator 3000
# https://codeforces.com/contest/2036/problem/F

"""
F. XORificator 3000

This problem involves computing the XOR of all integers in a given range [l, r] that satisfy the condition:
x  k (mod 2^i), which means x % 2^i != k.

The algorithm uses bitwise manipulation and a recursive approach to efficiently compute the result by:
- Breaking the problem into subproblems based on bit positions.
- Using precomputed masks and recurrence relations to avoid iterating over all numbers.

Time Complexity: O(1) per query — since i is bounded by 30, the number of operations is constant.
Space Complexity: O(1) — only a few variables are used regardless of input size.

Algorithms/Techniques:
- Bit manipulation
- Recursive bit-level processing
- Modular arithmetic with powers of two
"""

import sys

input = sys.stdin.readline


def fn(l, r, i, k):
    # Lambda function to compute a mask-based transformation for XOR operations
    rg = lambda a, b: [a - 1, 1, a, 0][(a - 1) & 3] ^ [b, 1, b + 1, 0][b & 3]
    
    # Compute high part of the range using the transformation
    hi = rg((l - 1 - k + (1 << i)) >> i, (r - k) >> i) << i
    
    # Compute low part based on parity of intervals
    lo = k * (((r - k) >> i) - ((l - k - 1) >> i) & 1)
    
    # Output final result by combining transformations
    print(rg(l, r) ^ hi ^ lo)


for _ in range(int(input())):
    l, r, i, k = list(map(int, input().split()))
    fn(l, r, i, k)


# https://github.com/VaHiX/codeForces/