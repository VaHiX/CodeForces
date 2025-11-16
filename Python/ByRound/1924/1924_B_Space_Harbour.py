# Problem: CF 1924 B - Space Harbour
# https://codeforces.com/contest/1924/problem/B

"""
Space Harbour Problem
Algorithm: Segment Tree with Lazy Propagation, Coordinate Compression
Time Complexity: O((n + m + q) * log n)
Space Complexity: O(n)

This problem involves managing harbours on a line and calculating movement costs for ships.
Key components:
1. Coordinate compression using bit manipulation to store harbour positions and values
2. Segment tree to efficiently query and update ranges of harbour costs
3. Dynamic updates when new harbours are added
4. Efficient range sum queries for cost calculation

The segment tree maintains:
- Minimum/maximum harbour positions in ranges (for nearest harbour lookup)
- Sum of cost contributions in each segment
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Helper function to combine position and value using bit manipulation
    return u << 28 ^ v


def update(i, x):
    # Update the segment tree with new cost value at position i
    i += l1
    mi[i] = ma[i] = i - l1  # Update min/max arrays
    s[i] = x  # Update sum array
    i >>= 1
    while i:
        # Propagate updates to parent nodes
        mi[i] = min(mi[2 * i], mi[2 * i + 1])
        ma[i] = max(ma[2 * i], ma[2 * i + 1])
        s[i] = s[2 * i] + s[2 * i + 1]
        i >>= 1
    return


def get_min(s, t):
    # Get minimum harbour position in range [s, t]
    s, t = s + l1, t + l1
    ans = inf
    while s <= t:
        if s & 1:  # If s is odd
            ans = min(ans, mi[s])
            s += 1
        s >>= 1
        if not t & 1:  # If t is even
            ans = min(ans, mi[t])
            t -= 1
        t >>= 1
    return ans


def get_max(s, t):
    # Get maximum harbour position in range [s, t]
    s, t = s + l1, t + l1
    ans = -inf
    while s <= t:
        if s & 1:  # If s is odd
            ans = max(ans, ma[s])
            s += 1
        s >>= 1
        if not t & 1:  # If t is even
            ans = max(ans, ma[t])
            t -= 1
        t >>= 1
    return ans


def get_sum(l, r):
    # Get sum of costs in range [l, r]
    l, r = l + l1, r + l1
    ans = 0
    while l <= r:
        if l & 1:  # If l is odd
            ans += s[l]
            l += 1
        l >>= 1
        if not r & 1:  # If r is even
            ans += s[r]
            r -= 1
        r >>= 1
    return ans


n, m, q = map(int, input().split())
x = list(map(int, input().split()))
v = list(map(int, input().split()))
# Coordinate compression using bit manipulation
y = [f(i, j) for i, j in zip(x, v)]
y.sort()
for i in range(m):
    # Unpack compressed coordinates
    x[i], v[i] = y[i] >> 28, y[i] & 0xFFFFFff
u = [0] * (n + 1)
u[1] = 1
# Initialize lookup table for harbour values
for i in range(m - 1):
    u[x[i + 1]] = v[i]
l1 = pow(2, (n + 1).bit_length())  # Size of segment tree
l2 = 2 * l1
inf = pow(10, 9) + 1
# Initialize segment tree arrays
mi, ma = [inf] * l2, [-inf] * l2
for i in x:  # Set initial min/max values
    mi[i ^ l1] = ma[i ^ l1] = i
for i in range(l1 - 1, 0, -1):  # Propagate min/max values
    mi[i] = min(mi[2 * i], mi[2 * i + 1])
    ma[i] = max(ma[2 * i], ma[2 * i + 1])
s = [0] * l2
# Initialize costs in segment tree
for i in range(1, m):
    c = (x[i] - x[i - 1]) * (x[i] - x[i - 1] - 1) // 2
    s[x[i] ^ l1] = c * v[i - 1]
for i in range(l1 - 1, 0, -1):  # Propagate sum values
    s[i] = s[2 * i] + s[2 * i + 1]
ans = []
for _ in range(q):
    t, l, r = map(int, input().split())
    if t == 1:
        # Add new harbour
        x0, v0 = l, r
        l0, r0 = get_max(0, x0 - 1), get_min(x0 + 1, l1 - 1)
        u[x0] = u[r0]
        u[r0] = v0
        c = (x0 - l0) * (x0 - l0 - 1) // 2
        update(x0, c * u[x0])
        c = (r0 - x0) * (r0 - x0 - 1) // 2
        i = r0 + l1
        s[i] = c * v0
        i >>= 1
        while i:  # Update parent nodes
            s[i] = s[2 * i] + s[2 * i + 1]
            i >>= 1
    else:
        # Calculate sum of costs for ships in range [l, r]
        if l == r and u[l]:
            ans0 = 0
            ans.append(ans0)
            continue
        ans0 = 0
        if not u[l - 1]:
            l0 = get_min(l, l1 - 1)
            c = (l0 - l) * (l0 - l + 1) // 2
            ans0 += c * u[l0]
            l = l0 + 1
        if not u[r]:
            r0 = get_min(r, l1 - 1)
            c = (r0 - r) * (r0 - r - 1) // 2
            ans0 -= c * u[r0]
            r = r0
        ans0 += get_sum(l, r)
        ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/