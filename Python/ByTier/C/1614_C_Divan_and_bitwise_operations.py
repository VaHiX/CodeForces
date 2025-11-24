# Problem: CF 1614 C - Divan and bitwise operations
# https://codeforces.com/contest/1614/problem/C

"""
Code Purpose:
This code computes the "coziness" of a sequence based on the bitwise XOR of all non-empty subsequences.
The key insight is that the coziness can be calculated efficiently using the bitwise OR of all given segments,
multiplied by 2^(n-1) (since each bit contributes to 2^(n-1) subsequences).

Algorithms/Techniques:
- Bitwise operations
- Segment analysis to determine the overall OR
- Modular arithmetic for large results

Time Complexity: O(m), where m is the number of segments
Space Complexity: O(1), constant space used
"""

import sys

input = sys.stdin.readline
mod = 10**9 + 7
for _ in " " * int(input()):
    n, m = map(int, input().split())
    res = 0
    for _ in " " * m:
        l, r, x = map(int, input().split())
        res |= x  # Combine all segment ORs using bitwise OR
    print(res * pow(2, n - 1) % mod)  # Multiply by 2^(n-1) and take mod


# https://github.com/VaHiX/CodeForces/