# Problem: CF 1601 A - Array Elimination
# https://codeforces.com/contest/1601/problem/A

# Flowerbox describing the purpose, algorithms, time and space complexity
"""
Problem: Array Elimination

Purpose:
This code determines all possible values of k for which it is possible to reduce
all elements of an array to zero using a specific operation called "elimination".
Each elimination operation chooses k distinct indices, computes the bitwise AND
of the elements at those indices, and subtracts that value from each chosen element.

Algorithm:
The core idea is based on bit manipulation and properties of bitwise AND.
For each bit position, we count how many numbers in the array have that bit set.
If for any bit, all numbers either have it set or not set (i.e., count is 0 or n),
then it's always possible to do elimination with k=1. Otherwise,
the valid values of k correspond to divisors of the GCD of all bit counts.

Time Complexity: O(n * log(max(a)) + sqrt(gcd))
Space Complexity: O(1) (since we use fixed-size arrays)

Techniques:
- Bit counting
- GCD computation
- Divisor enumeration
"""

import sys

input = sys.stdin.buffer.readline
from math import gcd

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    c = [0] * 30
    # Count how many numbers have each bit set
    for i in a:
        for j in range(30):
            if (i >> j) & 1:
                c[j] += 1
    g = 0
    # Compute GCD of all bit counts
    for i in c:
        g = gcd(g, i)
    if g == 0:
        # If GCD is 0, it means all counts are 0, so any k works
        print(*range(1, n + 1))
    else:
        y = []
        # Find all divisors of g
        for i in range(1, int(g**0.5) + 1):
            if g % i == 0:
                y.append(i)
                if i != g // i:
                    y.append(g // i)
        y.sort()
        print(*y)


# https://github.com/VaHiX/codeForces/