# Problem: CF 2071 D1 - Infinite Sequence (Easy Version)
# https://codeforces.com/contest/2071/problem/D1

"""
D1. Infinite Sequence (Easy Version)

This problem involves computing the sum of elements in a given range [l, r] of an infinite binary sequence defined recursively.

The sequence is defined as follows:
- For m <= n, a_m = input[m-1]
- For m > n, a_m = a_1 ⊕ a_2 ⊕ ... ⊕ a_{floor(m/2)}

Key algorithms and techniques:
- Prefix XOR for efficient range queries
- Recursive property of the sequence to compute values beyond n
- Optimization via precomputed prefix sums

Time Complexity: O(n) per test case, where n is the size of initial sequence
Space Complexity: O(n) for prefix array storage

Input format:
- First line: number of test cases t
- For each test case:
  - Line 1: n, l, r (l == r in this version)
  - Line 2: n integers representing first n terms of sequence

Output format:
- Sum of a_l + a_{l+1} + ... + a_r for each test case
"""

import sys

input = sys.stdin.readline


def clc(m, n, pre):
    # Base case: if m <= n, return pre[m]
    if m <= n:
        return pre[m]
    # If m is even, recurse with m//2 and XOR with pre[n]
    if m % 2 == 0:
        return clc(m // 2, n, pre) ^ pre[n]
    else:
        # If m is odd, just return pre[n]
        return pre[n]


def solve():
    n, l, r = map(int, input().split())
    ls = list(map(int, input().split()))
    
    # If l <= n, directly output the value at position l-1
    if l <= n:
        print(ls[l - 1])
        return
    
    # Build prefix XOR array
    pre = [0] * (n + 1)
    for i in range(1, n + 1):
        pre[i] = pre[i - 1] ^ ls[i - 1]
    
    # Special handling for even n to extend the sequence
    if n % 2 == 0:
        ls.append(pre[(n + 1) // 2])
        pre.append(pre[n] ^ ls[-1])
        n += 1
    
    # Compute and print result by calling clc on l//2
    print(clc(l // 2, n, pre))


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/codeForces/