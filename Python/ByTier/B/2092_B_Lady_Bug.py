# Problem: CF 2092 B - Lady Bug
# https://codeforces.com/contest/2092/problem/B

"""
B. Lady Bug

Problem Description:
Given two binary strings 'a' and 'b' of equal length n, determine if it's possible to make string 'a' consist only of zeros using specific swap operations. The allowed swaps are between a[i] and b[i-1] or b[i] and a[i-1] for i in range [2, n].

Approach:
We simulate the process by constructing two candidate strings:
    - c: formed by taking even-indexed characters from 'a' and odd-indexed from 'b'
    - d: formed by taking odd-indexed characters from 'a' and even-indexed from 'b'

The key idea is that we can only move bits from b to a if they are in positions where swapping is allowed. So, we check if in these constructed strings we have enough zeros to fill up the required number of positions.

Time Complexity: O(n) per test case
Space Complexity: O(n) due to string construction
"""

from sys import stdin

input = lambda: stdin.buffer.readline().decode().strip()
for _ in range(int(input())):
    n = int(input())
    a = input()
    b = input()
    # Construct c by taking even indices from 'a' and odd indices from 'b'
    c = a[::2] + b[1::2]
    # Construct d by taking odd indices from 'a' and even indices from 'b'
    d = a[1::2] + b[::2]
    # Check if either of the constructed strings has enough zeros
    print("YES" if c.count("0") >= (n + 1) // 2 and d.count("0") >= n // 2 else "NO")


# https://github.com/VaHiX/codeForces/