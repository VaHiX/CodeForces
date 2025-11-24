# Problem: CF 2071 D2 - Infinite Sequence (Hard Version)
# https://codeforces.com/contest/2071/problem/D2

"""
D2. Infinite Sequence (Hard Version)

Purpose:
    This code computes the sum of elements in a given range [l, r] for an infinite binary sequence.
    The first n terms are provided; for m > n, each term is defined as the XOR of all previous terms up to floor(m/2).

Algorithms/Techniques Used:
    - Prefix XOR for efficient range queries
    - Bit manipulation and properties of XOR
    - Recursive calculation with memoization-like behavior
    - Optimization using bit-length analysis

Time Complexity:
    O(n * log(max(r))) where n is the size of input sequence, due to recursive and bitwise operations.
    
Space Complexity:
    O(n) for storing prefix XOR array and auxiliary arrays.

"""

import sys
from functools import reduce
from operator import xor

input = sys.stdin.readline
rn = lambda: int(input())
rs = lambda: input().strip()
rl = lambda: list(map(int, input().split()))


def solve():
    (_n, l, r), _a = rl(), [0] + rl()  # Read n, l, r and first n terms; pad with 0
    n, a = _n | 1, _a if _n & 1 else list(_a) + [reduce(xor, _a[: (_n + 1) // 2 + 1])]  # Ensure odd length, add last element if needed
    pre_xor = [0] * (n + 1)  # Precompute prefix XORs for fast range XOR queries
    for i in range(1, n + 1):
        pre_xor[i] = pre_xor[i - 1] ^ a[i]
    rev = pre_xor[n]  # Total XOR value of all elements

    def _calc(m):
        # Helper function to compute the value at position m recursively based on definition
        k = m // 2
        return (
            a[m]
            if m <= n
            else (
                reduce(xor, a[: k + 1])
                if k <= n
                else reduce(xor, a)
                ^ (_calc(n + 1) if not n & 1 else 0)
                ^ (0 if k & 1 else _calc(k))
            )
        )

    def calc(m):
        # Main function to calculate how many 1s are there in position m (up to some limit), optimized using bit analysis
        if not (m & 1):  # Even case - recursively solve odd case with offset
            return calc(m + 1) - _calc(m + 1)
        f = [  # Bitmask manipulation based on powers of 2
            max(0, ((m // 2 - (1 << i)) // (1 << (i + 1)) - n // 2)) << 1
            for i in range(0, 61, 2)
        ]
        z = [(i, (m // i).bit_length() - 1) for i in range(n // 2 + 1, n + 1)]  # Precompute useful values
        res = (
            a[: m + 1].count(1)  # If within known sequence
            if m <= n
            else (
                sum([v << 1 for (i, v) in z if pre_xor[i]]) + a.count(1)
                if not rev
                else a.count(1) + sum(f) + sum([(v + pre_xor[i]) & -2 for (i, v) in z])
            )
        )
        return res

    print(calc(r) - calc(l - 1))  # Output result of range query


[solve() for _ in range(rn())]


# https://github.com/VaHiX/codeForces/