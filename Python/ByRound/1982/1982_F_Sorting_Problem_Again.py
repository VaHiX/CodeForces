# Problem: CF 1982 F - Sorting Problem Again
# https://codeforces.com/contest/1982/problem/F

"""
Sorting Problem Again
Algorithm: Using coordinate compression, binary indexed tree (Fenwick tree), and heaps to efficiently find the minimum subarray that needs to be sorted.
Time Complexity: O((n + q) * log(n + q)) where n is the size of the array and q is the number of queries.
Space Complexity: O(n + q) for storing the compressed coordinates and the tree.

The approach involves:
1. Coordinate compression to map array values to smaller indices.
2. Using a Fenwick tree to efficiently compute prefix sums for finding subarray boundaries.
3. Maintaining heaps of local minima and maxima to quickly determine the boundaries of the subarray to sort.
4. Updating the heaps and tree after each modification to reflect the current state of the array.
"""

import heapq
import io
import os
import random
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Helper function for coordinate compression using XOR
    return u << 24 ^ v


def get_sum(i):
    # Get prefix sum from Fenwick tree
    s = 0
    while i > 0:
        s += tree[i]
        i -= i & -i
    return s


def add(i, x):
    # Add value to Fenwick tree
    while i < len(tree):
        tree[i] += x
        i += i & -i


t = int(input())
ans = []
inf = pow(10, 9) + 1
rr = random.randint(1, 1 << 60)  # Random number for coordinate compression
for _ in range(t):
    n = int(input())
    a = [-inf] + list(map(int, input().split())) + [inf]
    q = int(input())
    q0 = [0] * (q << 1)  # Store queries as pairs [pos, val]
    x = [0] * (n + q + 2)  # Combined array of coordinates for compression
    for i in range(n + 2):
        x[i] = f(a[i] + inf, i)  # Precompute coordinates for original array
    for i in range(q):
        pos, val = map(int, input().split())
        x[i + n + 2] = f(val + inf, pos)  # Precompute coordinates for updates
        q0[i << 1], q0[i << 1 ^ 1] = pos, val + inf  # Store the actual positions and values

    mi, ma = [], []  # Min and max heaps for local minima and maxima
    tree = [0] * (n + q + 5)  # Fenwick tree for efficient prefix sums
    d = dict()  # Dictionary for coordinate compression
    for i in sorted(x):
        # Compress coordinates using XOR with random number
        if not i ^ rr in d:
            d[i ^ rr] = len(d)
    
    # Assign compressed indices to the original array
    for i in range(n + 2):
        a[i] = d[f(a[i] + inf, i) ^ rr]
        tree[a[i]] += 1  # Initialize Fenwick tree

    # Update Fenwick tree with prefix sums
    for i in range(1, len(tree)):
        j = i + (i & -i)
        if j < len(tree):
            tree[j] += tree[i]

    # Identify initial local minima and maxima
    for i in range(1, n + 1):
        if a[i - 1] > a[i] < a[i + 1]:
            mi.append(f(a[i], i))  # Local minimum
        elif a[i - 1] < a[i] > a[i + 1]:
            ma.append(-f(a[i], i))  # Local maximum

    heapq.heapify(mi)
    heapq.heapify(ma)
    
    ans0 = ["-1 -1" for _ in range(q + 1)]  # Initialize result vector
    
    if mi:
        # Get the current boundaries based on heaps
        l, r = get_sum(mi[0] >> 24), get_sum(-ma[0] >> 24)
        ans0[0] = " ".join(map(str, (l, r)))

    for i in range(q):
        pos, val = q0[i << 1], q0[i << 1 ^ 1]  # Get position and updated value
        add(a[pos], -1)  # Remove old value from the tree
        a[pos] = d[f(val, pos) ^ rr]  # Update the value
        add(a[pos], 1)  # Add new value to tree

        # Check for changes in neighboring elements for potential local extrema
        for j in range(max(pos - 1, 1), min(pos + 2, n + 1)):
            if a[j - 1] > a[j] < a[j + 1]:
                heapq.heappush(mi, f(a[j], j))  # Push new minima
            elif a[j - 1] < a[j] > a[j + 1]:
                heapq.heappush(ma, -f(a[j], j))  # Push new maxima

        # Update heaps by removing outdated entries
        while mi:
            u, j = mi[0] >> 24, mi[0] & 0xFFFFFF
            if a[j - 1] > a[j] == u < a[j + 1]:
                break
            heapq.heappop(mi)
        while ma:
            u, j = -ma[0] >> 24, -ma[0] & 0xFFFFFF
            if a[j - 1] < a[j] == u > a[j + 1]:
                break
            heapq.heappop(ma)

        if mi:
            # Determine and record updated subarray boundaries
            l, r = get_sum(mi[0] >> 24), get_sum(-ma[0] >> 24)
            ans0[i + 1] = " ".join(map(str, (l, r)))
    
    ans.append("\n".join(ans0))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/