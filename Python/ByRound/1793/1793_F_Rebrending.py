# Problem: CF 1793 F - Rebrending
# https://codeforces.com/contest/1793/problem/F

"""
Algorithm: Offline Processing with Coordinate Compression and Segment Tree
Time Complexity: O(n * log(n) + q * log(n))
Space Complexity: O(n)

This solution uses a combination of coordinate compression, Fenwick tree (Binary Indexed Tree) and 
segment tree to efficiently process range minimum difference queries. The approach is optimized 
for offline processing where all queries are known beforehand. The coordinate compression reduces 
the problem size by mapping heights to indices, and the segment trees are used to maintain 
and query the minimum differences quickly.

The code works by:
1. Preprocessing the array with coordinate compression (mapping heights to indices)
2. Using a segment tree to track positions of each height
3. Using a Fenwick tree to maintain the minimum differences
4. Processing queries offline in sorted order
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Helper function to encode query information
    return u << 20 ^ v


def update1(i, x):
    # Update Fenwick tree for min difference tracking
    while i < len(tree1):
        tree1[i] = min(tree1[i], x)
        i += i & -i
    return


def get_min1(i):
    # Query Fenwick tree for min difference
    ans = inf
    while i > 0:
        ans = min(ans, tree1[i])
        i -= i & -i
    return ans


def update2(i, x):
    # Update segment tree for position tracking
    i ^= l1
    tree2[i] = x
    i >>= 1
    while i:
        tree2[i] = min(tree2[i << 1], tree2[i << 1 ^ 1])
        i >>= 1
    return


def get_min2(s, t):
    # Query segment tree for position range minimum
    s, t = s ^ l1, t ^ l1
    ans = inf
    while s <= t:
        if s & 1:
            ans = min(ans, tree2[s])
            s += 1
        s >>= 1
        if not t & 1:
            ans = min(ans, tree2[t])
            t -= 1
        t >>= 1
    return ans


n, q = map(int, input().split())
a = [0] + list(map(int, input().split()))  # 1-indexed array of heights
q0 = [0] * q  # Store queries with encoded information

# Read all queries and encode them
for i in range(q):
    l, r = map(int, input().split())
    q0[i] = f(f(l, r), i)  # Encode l, r, and query index

# Sort queries by left boundary
q0.sort()
l1 = pow(2, (n + 1).bit_length())  # Size of segment tree (power of 2)
l2 = 2 * l1  # Double size for segment tree
ans = [0] * q  # Store results for each query
inf = pow(10, 9) + 1  # Large value for infinity
tree1, tree2 = [inf] * (n + 1), [inf] * l2  # Initialize Fenwick and segment tree

# Process elements from right to left
for l in range(n, 0, -1):
    u = a[l]  # Current height
    # Find the nearest element in the segment tree using min difference approach
    r = get_min2(u, l1 - 1)
    while r ^ inf:
        # Compute and update differences
        v = a[r]
        update1(r, v - u)
        r = get_min2(u, u + ((v - u) >> 1))
    r = get_min2(0, u)
    while r ^ inf:
        # Update differences in reverse direction (for negative differences)
        v = a[r]
        update1(r, u - v)
        r = get_min2(u - ((u - v) >> 1), u)
    update2(u, l)  # Update segment tree with current position
    # Process all queries that start at position l
    while q0 and q0[-1] >> 40 == l:
        r, i = (q0[-1] >> 20) & 0xFFFFF, q0.pop() & 0xFFFFF  # Extract right boundary and query index
        ans[i] = get_min1(r)  # Get minimum difference for this query
    if not q0:  # If all queries processed, exit early
        break
        
sys.stdout.write("\n".join(map(str, ans)))  # Output all results


# https://github.com/VaHiX/CodeForces/