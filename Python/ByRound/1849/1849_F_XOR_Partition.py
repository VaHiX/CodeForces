# Problem: CF 1849 F - XOR Partition
# https://codeforces.com/contest/1849/problem/F

"""
Algorithm: XOR Partition using Trie-based approach with Union-Find
Time Complexity: O(30 * n * log(n)) 
Space Complexity: O(n)

This solution uses a trie data structure to efficiently find the minimum XOR
between elements in different partitions. It employs a binary search-like
approach on the bits, using Union-Find to maintain connectivity of elements
and determine the optimal partition.

The algorithm works by:
1. Sorting input elements
2. Using a trie to store elements for efficient XOR queries
3. Applying a divide-and-conquer strategy on bit levels
4. Using Union-Find to track which elements belong to the same partition
5. Determining the final assignment based on connected components
"""

import io
import os
import random
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(l, u, v):
    return l << 40 ^ u << 20 ^ v


def g(u, v):
    return u << 20 ^ v


def insert(x, c, la):
    j = 0
    for i in p:
        if x & i:
            if not G[j] >> 28:  # If right child doesn't exist
                la += 1
                G[j] ^= la << 28  # Set right child to la
                j = la
            else:
                j = G[j] >> 28  # Move to right child
        else:
            if not G[j] & 0xFFFFFFF:  # If left child doesn't exist
                la += 1
                G[j] ^= la  # Set left child to la
                j = la
            else:
                j = G[j] & 0xFFFFFFF  # Move to left child
        color[j] = c  # Mark node with color c
    return la


def xor_min(x, c):
    j, ans = 0, 0
    for i in p:
        if x & i:
            if color[G[j] >> 28] == c:  # If right child has same color
                j = G[j] >> 28  # Go right
            else:
                ans ^= i  # XOR with current bit
                j = G[j] & 0xFFFFFFF  # Go left
        else:
            if color[G[j] & 0xFFFFFFF] == c:  # If left child has same color
                j = G[j] & 0xFFFFFFF  # Go left
            else:
                ans ^= i  # XOR with current bit
                j = G[j] >> 28  # Go right
        if not j:  # If reached leaf
            return ans
    return ans


def get_root(s):
    v = []
    while not s == root[s]:
        v.append(s)
        s = root[s]
    for i in v:
        root[i] = s
    return s


def unite(s, t):
    s, t = get_root(s), get_root(t)
    if s == t:
        return
    if rank[s] < rank[t]:
        s, t = t, s
    if rank[s] == rank[t]:
        rank[s] += 1
    root[t] = s
    return


def same(s, t):
    return True if get_root(s) == get_root(t) else False


n = int(input())
a = list(map(int, input().split()))
d = dict()
r = random.randint(1, 1 << 30)
for i in range(n):
    d[a[i] ^ r] = i
a.sort()
pow2 = [1]
l = 30
for _ in range(l):
    pow2.append(2 * pow2[-1])
p = pow2[::-1]
st = [f(30, 0, n)]
inf = pow2[30]
G, color, c, la = [0] * 6000000, [0] * 6000000, 0, 0
root = [i for i in range(2 * n)]
rank = [1 for _ in range(2 * n)]
while st:
    x = st.pop()
    l0, u, v = x >> 40, (x >> 20) & 0xFFFFF, x & 0xFFFFF
    c += 1
    if u == v or l0 < 0:  # Base case
        continue
    p2 = pow2[l0]
    if p2 & a[u] == p2 & a[v - 1]:  # If all numbers have same bit
        st.append(f(l0 - 1, u, v))
        continue
    m = u
    while not a[m] & p2:  # Find mid point
        m += 1
    mi = inf
    if m - u <= v - m:
        for i in range(u, m):
            la = insert(a[i], c, la)
        for i in range(m, v):
            mi0 = xor_min(a[i], c)
            if mi > mi0:
                e, mi = a[i], mi0
    else:
        for i in range(m, v):
            la = insert(a[i], c, la)
        for i in range(u, m):
            mi0 = xor_min(a[i], c)
            if mi > mi0:
                e, mi = a[i], mi0
    i, j = d[e ^ r], d[e ^ mi ^ r]  # Get indices of elements
    unite(i, j + n)
    unite(i + n, j)
    st.append(f(l0 - 1, u, m))
    st.append(f(l0 - 1, m, v))
ans = ["1" if same(i, 0) else "0" for i in range(n)]
sys.stdout.write("".join(ans))


# https://github.com/VaHiX/CodeForces/