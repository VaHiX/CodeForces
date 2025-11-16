# Problem: CF 1974 C - Beautiful Triple Pairs
# https://codeforces.com/contest/1974/problem/C

"""
Algorithm: Beautiful Triple Pairs
Techniques: Hashing, Grouping, Inclusion-Exclusion Principle

Time Complexity: O(n)
Space Complexity: O(n)

The solution uses a hashing technique to count occurrences of pairs and triples
in the array. It applies the inclusion-exclusion principle to avoid overcounting:
- First, we count pairs of triples that differ in one position using 2-element hashes.
- Then, we subtract triple counts that differ in all positions using 3-element hashes.

This approach efficiently counts all beautiful pairs in linear time.
"""

import sys
from itertools import groupby

input = lambda: sys.stdin.readline().rstrip()

from random import getrandbits

R = getrandbits(32)


def code2(x, y):
    # Hash function for pairs (x, y) using bit shifting and XOR
    return ((x << 20) | y) ^ R


def code3(x, y, z):
    # Hash function for triples (x, y, z) using bit shifting and XOR
    return ((x << 40) | (y << 20) | z) ^ R


def dups(a):
    # Count duplicate pairs using grouping
    a.sort()
    res = 0
    for _, g in groupby(a):
        k = len(list(g))  # Count group size
        res += k * (k - 1) // 2  # Add combinations of pairs in group
    return res


def solve(n, a):
    res = 0
    # For each pair of indices (0,1), (0,2), (1,2) we count pairs of triples
    # that differ only at those positions
    for i, j in (0, 1), (0, 2), (1, 2):
        b = [code2(a[k + i], a[k + j]) for k in range(n - 2)]
        res += dups(b)
    
    # Count pairs of triples that are identical (i.e., all three positions)
    b = [code3(a[k], a[k + 1], a[k + 2]) for k in range(n - 2)]
    res -= 3 * dups(b)  # Subtract overcounted triple matches
    
    return res


t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    print(solve(n, a))


# https://github.com/VaHiX/CodeForces/