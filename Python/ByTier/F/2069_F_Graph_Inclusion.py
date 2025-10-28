# Problem: CF 2069 F - Graph Inclusion
# https://codeforces.com/contest/2069/problem/F

"""
F. Graph Inclusion

Purpose:
This code solves the problem of maintaining two graphs A and B, each initially with n vertices and no edges,
and processing queries to add/remove edges in either graph. After each query, it computes the minimum number
of additional edges needed in graph A such that all connected components of B are subsets of connected components of A.

Algorithms:
- Union-Find (Disjoint Set Union) data structure for tracking connected components.
- Segment tree with lazy propagation to efficiently track edge operations over time.
- Offline processing using a segment tree and temporal union-find to compute component size differences.

Time Complexity: 
O(q * α(n)) where α(n) is the inverse Ackermann function, which is effectively constant for practical inputs. 
This assumes amortized constant time for union-find operations.

Space Complexity:
O(n + q) for storing segment tree structure and auxiliary data.

Note: The actual complexity is more nuanced due to complex operations involving segment trees and temporal tracking.
"""

import io
import os
import random
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Hashing function to map pair (u,v) into a unique integer
    return u << 20 ^ v


def g(u, v, w):
    # Combines three values using bit shifts for unique signature
    return u << 40 ^ v << 20 ^ w


def get_segment(s, t):
    # Returns segments of the range [s, t] to traverse the segment tree
    s, t = s ^ l1, t ^ l1
    while s <= t:
        if s & 1:
            yield s
            s += 1
        s >>= 1
        if not t & 1:
            yield t
            t -= 1
        t >>= 1


def get_root(s):
    # Find root of the set containing s with path compression
    while s ^ root[s]:
        s = root[s]
    return s


def unite(s, t):
    # Unite sets containing s and t using union by rank
    s, t = get_root(s), get_root(t)
    if s == t:
        return 0
    if rank[s] < rank[t]:
        s, t = t, s
    root[t], rs = s, rank[s]
    if rank[s] == rank[t]:
        rank[s] += 1
    return g(s, t, rs)


n, q = map(int, input().split())
rr = random.randint(1, 1 << 40)
da, db = dict(), dict()  # Tracks intervals for additions of edges in graphs A and B
qa, qb = [0] * (q << 2), [0] * (q << 1)  # Segment tree queries for graph A & B
j = k = 0  # Pointers to store query data
z = f(n, n)  # Mask for hashing purposes
for i in range(q):
    t, x, y = input().rstrip().split()
    x, y = int(x), int(y)
    if x > y:
        x, y = y, x
    u = f(x, y) ^ rr  # Create unique key for edge (x,y)
    if ord(t) & 1:  # If query is for graph A
        if not u in da:
            da[u] = i  # Record start of interval
        else:
            qa[j], qa[j ^ 1], j = f(da.pop(u), i - 1), u ^ rr, j + 2  # End interval and store start+end
            qa[j], qa[j ^ 1], j = qa[j - 2], qa[j - 1] + z, j + 2
    else:  # If query is for graph B
        if not u in db:
            db[u] = i  # Record start of interval
        else:
            qb[k], qb[k ^ 1], k = f(db.pop(u), i - 1), u ^ rr, k + 2  # End interval and store start+end

l1 = pow(2, (q + 1).bit_length())  # Length of segment tree base
l2 = 2 * l1  # Actual size of segment tree needed

for i in da.keys():  # Process remaining additions in graph A
    qa[j], qa[j ^ 1], j = f(da[i], l1 - 1), i ^ rr, j + 2
    qa[j], qa[j ^ 1], j = qa[j - 2], qa[j - 1] + z, j + 2
for i in db.keys():  # Process remaining additions in graph B
    qb[k], qb[k ^ 1], k = f(db[i], l1 - 1), i ^ rr, k + 2

s0 = [0] * (l2 + 3)  # Segment tree size tracker
for i in range(0, j, 2):
    l, r = qa[i] >> 20, qa[i] & 0xFFFFF  # Extract left and right boundaries
    for v in get_segment(l, r):  # Add to segment tree count
        s0[v + 2] += 1
for i in range(0, k, 2):
    l, r = qb[i] >> 20, qb[i] & 0xFFFFF  # Extract left and right boundaries
    for v in get_segment(l, r):  # Add to segment tree count
        s0[v + 2] += 1

for i in range(2, l2 + 3):  # Prefix sum for segment tree
    s0[i] += s0[i - 1]

tree = [0] * s0[-1]  # Segment tree storage to hold edge operations
for i in range(0, j, 2):
    l, r = qa[i] >> 20, qa[i] & 0xFFFFF
    for v in get_segment(l, r):
        tree[s0[v + 1]] = qa[i ^ 1]  # Assign edge operation values
        s0[v + 1] += 1
for i in range(0, k, 2):
    l, r = qb[i] >> 20, qb[i] & 0xFFFFF
    for v in get_segment(l, r):
        tree[s0[v + 1]] = qb[i ^ 1]
        s0[v + 1] += 1

root = [i for i in range((n + 1) << 1)]  # DSU root array
rank = [1 for _ in range((n + 1) << 1)]  # DSU rank array
ans = [-1] * q  # Final answer array
visit, i = [0] * l2, 1  # Visited tracker and current node pointer
c1 = c2 = 0  # Count of nodes in active components for A and B

for j in range(s0[1], s0[2]):  # Process initial operations
    s, t = tree[j] >> 20, tree[j] & 0xFFFFF
    tree[j] = unite(s, t)  # Perform union
    if not tree[j]:
        continue
    if s <= n:
        c1 += 1  # Count node in A's component
    else:
        c2 += 1  # Count node in B's component

while ans[-1] == -1:  # Traverse the segment tree backwards
    visit[i] = 1
    if i & l1 or visit[i << 1 ^ 1]:  # If this is a leaf or right child not visited
        for j in range(s0[i + 1] - 1, s0[i] - 1, -1):  # Revert operations
            if not tree[j]:
                continue
            s, t, rs = tree[j] >> 40, (tree[j] >> 20) & 0xFFFFF, tree[j] & 0xFFFFF
            rank[s], root[t] = rs, t  # Restore original state of DSU
            if s <= n:  # Adjust component sizes
                c1 -= 1
            else:
                c2 -= 1
        i >>= 1
        continue
    i = i << 1 if not visit[i << 1] else i << 1 ^ 1  # Move to left or right path
    for j in range(s0[i], s0[i + 1]):
        s, t = tree[j] >> 20, tree[j] & 0xFFFFF
        tree[j] = unite(s, t)
        if not tree[j]:
            continue
        if s <= n:
            c1 += 1
        else:
            c2 += 1
    if i & l1:  # Save final result if it's a leaf
        ans[i ^ l1] = c1 - c2

sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/codeForces/