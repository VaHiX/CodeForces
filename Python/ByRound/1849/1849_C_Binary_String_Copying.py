# Problem: CF 1849 C - Binary String Copying
# https://codeforces.com/contest/1849/problem/C

"""
Algorithm: Binary String Copying
Purpose: Given a binary string and m operations, each operation sorts a substring of a copy of the string, 
         determine how many distinct strings are produced among all copies.

Time Complexity: O(n + m * log(m)) where n is the length of the string and m is the number of operations.
Space Complexity: O(n + m) for storing the string, auxiliary arrays, and results.

Techniques:
- Efficient sorting of substrings by preprocessing
- Coordinate compression to reduce complexity
- Binary search for duplicate checking
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Helper function to map coordinates to a unique identifier
    return u * (n + 1) + v


t = int(input())
ans = []
inf = pow(10, 9) + 1
for _ in range(t):
    n, m = map(int, input().split())
    # Convert string to list with 1-based indexing
    t = [0] + list(input().rstrip())
    # Preprocessing arrays
    l0 = [0] * (n + 1)
    l0[1] = 1
    u = inf
    # Forward pass for l0
    for i in range(1, n):
        u = min(u, i) if not t[i] & 1 else inf
        l0[i + 1] = min(u, i + 1)
    r0 = [0] * (n + 1)
    r0[n] = n
    u = -inf
    # Backward pass for r0
    for i in range(n, 1, -1):
        u = max(u, i) if t[i] & 1 else -inf
        r0[i - 1] = max(u, i - 1)
    v = [0] * (n + 1)
    # Compute differences for segments of the string
    for i in range(2, n + 1):
        v[i] = v[i - 1] + (t[i] ^ t[i - 1])
    s = [-1] * m
    # Process each operation and assign a key for sorting
    for i in range(m):
        l, r = map(int, input().split())
        # If the prefix sums are the same or a specific condition is met, skip sorting
        if v[l] == v[r] or (v[l] + 1 == v[r] and not t[l] & 1):
            continue
        s[i] = f(l0[l], r0[r])
    # Sort the keys
    s.sort()
    ans0 = m
    # Count unique keys
    for i in range(m - 1):
        if s[i] == s[i + 1]:
            ans0 -= 1
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/