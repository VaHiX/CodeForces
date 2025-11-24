# Problem: CF 1746 F - Kazaee
# https://codeforces.com/contest/1746/problem/F

"""
Algorithm: Coordinate Compression + Binary Indexed Tree (Fenwick Tree) + Hashing
Purpose: Efficiently process range queries and updates on an array to check if all element frequencies in a subarray are divisible by a given number k.

Time Complexity: O((n + q) * log n * log(max_val))
Space Complexity: O(n * log(max_val))

The code uses a combination of coordinate compression, hash functions, and binary indexed trees to handle 
both point updates and range queries efficiently. The hash function 'f(u, v)' creates a unique signature for each element-position pair.
"""

import io
import os
import random
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Hash function combining element value and position
    return u << 20 ^ v


def add(i, u, v):
    # Update the binary indexed tree for element u and v
    for p in range(0, 10 * (1 << 19), 1 << 19):
        # Calculate difference in hash values
        c = z[u & 7] - z[v & 7]
        u, v, j = u >> 3, v >> 3, i
        if not c:
            continue
        # Update BIT
        while j <= n:
            tree[j ^ p] += c
            j += j & -j
    return


def ok(l, r, k):
    # Check if all frequencies in range [l, r] are divisible by k
    for p in range(0, 10 * (1 << 19), 1 << 19):
        i, j, s = l - 1, r, 0
        # Compute prefix sum for left boundary
        while i > 0:
            s -= tree[i ^ p]
            i -= i & -i
        # Compute prefix sum for right boundary
        while j > 0:
            s += tree[j ^ p]
            j -= j & -j
        # Check divisibility for each of 3 hash components
        for _ in range(3):
            if (s & 0xFFFFF) % k:
                return False
            s >>= 20
    return True


# Read input
n, q = map(int, input().split())
a = [0] + list(map(int, input().split()))
q0 = [0] * (q << 2)  # Store all queries
u = [f(a[i], i) for i in range(1, n + 1)]  # Hash all initial elements

# Process all queries
for i in range(q):
    t = list(map(int, input().split()))
    for j in range(len(t)):
        q0[i << 2 ^ j] = t[j]  # Pack queries in q0 array
    if t[0] == 1:
        # Update operation: add new element to u for processing
        u.append(f(t[2], n + i + 1))

la = 0  # Last hash value processed
# Coordinate compression mapping hash values to random values
for i in sorted(u):
    x, j = i >> 20, i & 0xFFFFF  # Extract hash and position
    if la ^ x:  # New hash value
        la, r = x, random.randint(1, (1 << 30) - 1)  # Generate random mapping
    if j <= n:
        a[j] = r  # Update original array
    else:
        q0[(j - n - 1) << 2 ^ 2] = r  # Update query result

# Initialize hash mapping table z
z, c, p = [0] * 8, 1, 1
for _ in range(3):
    for i in range(8):
        if i & p:
            z[i] ^= c
    p, c = p << 1, c << 20  # Shift for next component

# Initialize binary indexed tree
tree = [0] * (1 << 23)
for i in range(1, n + 1):
    add(i, a[i], 0)  # Initialize BIT with original array

ans = []
# Process all queries
for j in range(0, q << 2, 4):
    if q0[j] == 1:  # Update query
        i, x = q0[j ^ 1], q0[j ^ 2]
        add(i, x, a[i])  # Update BIT
        a[i] = x  # Update array
    else:  # Range query
        l, r, k = q0[j ^ 1], q0[j ^ 2], q0[j ^ 3]
        ans0 = "YES" if ok(l, r, k) else "NO"
        ans.append(ans0)

# Output results
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/