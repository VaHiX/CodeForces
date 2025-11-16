# Problem: CF 2167 G - Mukhammadali and the Smooth Array
# https://codeforces.com/contest/2167/problem/G

"""
Algorithm: Dynamic Programming with Coordinate Compression and Binary Indexed Tree (Fenwick Tree)
Purpose: Given an array and costs to modify elements, find the minimum cost to make the array non-decreasing (no drops).
Techniques:
- Coordinate compression to reduce the range of values.
- Binary Indexed Tree (Fenwick Tree) for efficient range maximum queries and updates.
- Dynamic Programming where for each element, we compute the maximum cost benefit of not changing it.

Time Complexity: O(n log n) per test case due to coordinate compression, sorting, and BIT operations.
Space Complexity: O(n) for storing values, costs, BIT, and auxiliary structures.

The problem is transformed into finding a maximum weight path in a DAG where:
- Each node represents a compressed value in the array.
- The edge weights are the costs of modifying elements.
- We maximize the sum of weights for a non-decreasing sequence.

We use a Fenwick Tree to maintain the maximum accumulated cost for each compressed value.
"""

import sys

r = sys.stdin.buffer.read
w = sys.stdout.write
d = list(map(int, r().split()))
p = 0
t = d[p]
p += 1
o = []
for _ in range(t):
    n = d[p]
    p += 1
    a = d[p : p + n]
    p += n
    c = d[p : p + n]
    p += n
    s = sum(c)  # Total cost of all elements if we change all
    v = sorted(set(a))  # Unique sorted values for coordinate compression
    m = len(v)
    x = {v[i]: i + 1 for i in range(m)}  # Map original value to compressed index
    b = [0] * (m + 1)  # Binary Indexed Tree for maximum cost tracking

    def u(i, y):
        # Update BIT: at index i, store maximum of current value and y
        while i <= m:
            if y > b[i]:
                b[i] = y
            i += i & -i  # Move to next index

    def q(i):
        # Query BIT: get maximum value in range [1, i]
        z = 0
        while i > 0:
            if b[i] > z:
                z = b[i]
            i -= i & -i  # Move to parent index
        return z

    y = 0  # Maximum accumulated cost found so far
    for i in range(n):
        j = x[a[i]]  # Compressed index of current element
        z = q(j) + c[i]  # Cost to modify current element + best previous score
        if z > y:
            y = z
        u(j, z)  # Update BIT with new maximum score at index j

    o.append(str(s - y))  # Minimum cost is total - maximum benefit
w("\n".join(o))


# https://github.com/VaHiX/CodeForces/