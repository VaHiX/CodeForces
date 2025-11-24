# Problem: CF 2116 D - Gellyfish and Camellia Japonica
# https://codeforces.com/contest/2116/problem/D

"""
D. Gellyfish and Camellia Japonica

Algorithm: 
- The problem models a process where an array `a` is modified through a series of operations.
  Each operation sets `c[z_i] = min(c[x_i], c[y_i])`, which represents a min-heap-like update.
- We reverse-engineer the original array `a` based on final values and operations.
- A segment tree with lazy propagation or similar structure is used to track dependencies between elements.

Time Complexity: O(n + q * log n)
Space Complexity: O(n + q)

This code uses a segment tree (seg class) to simulate and reverse-engineer the dependency chain
of how values are assigned during operations. It handles constraints on values via tracking
minima along paths in dependency graphs.
"""

import sys

input = sys.stdin.readline


class seg:
    def __init__(self, n):
        self.n = n
        self.sz = 1
        while self.sz < n:
            self.sz <<= 1
        self.d = [0] * (2 * self.sz)

    def b(self):
        # Initialize the leaves of the segment tree with indices
        for i in range(1, self.n + 1):
            self.d[self.sz + i - 1] = i
        # Set internal nodes to zero initially
        for i in range(self.sz - 1, 0, -1):
            self.d[i] = 0

    def u(self, pos, v):
        # Update value at position `pos` in the segment tree with `v`
        i = self.sz + pos - 1
        self.d[i] = v
        i >>= 1
        while i > 0:
            self.d[i] = 0  # Placeholder logic for propagation
            i >>= 1

    def qr(self, pos):
        # Query the value at position `pos` in the segment tree
        return self.d[self.sz + pos - 1]


def solve():
    n, q = map(int, input().split())
    b = [0] + list(map(int, input().split()))  # b[0] unused, b[i] represents final value
    tot = n + q  # Total number of nodes (original + intermediate)

    # Arrays representing left/right child and low values for each node
    l, r, root, low, ans = (
        [0] * (tot + 1),
        [0] * (tot + 1),
        [0] * (tot + 1),
        [0] * (tot + 1),
        [0] * (tot + 1),
    )
    
    st = seg(n)
    st.b()  # Initialize segment tree

    # Process queries and build mapping from operations to nodes
    for i in range(1, q + 1):
        x, y, z = map(int, input().split())
        u = n + i  # New node id for operation result
        l[u], r[u] = st.qr(x), st.qr(y)  # Set children of this node
        st.u(z, u)  # Update to point to the new node at index z

    # Mark root nodes based on original values
    for i in range(1, n + 1):
        root[st.qr(i)] = 1

    # Initialize low values from original array b
    for i in range(1, n + 1):
        v = st.qr(i)
        if low[v] == 0:
            low[v] = b[i]

    flag = True  # Flag to detect contradiction in assignment

    # Propagate minimums backwards through dependencies
    for u in range(tot, 0, -1):
        if u > n and low[u] > 0:
            # Handle parent-child constraint checking
            if low[l[u]] < low[u]:
                if root[l[u]]:
                    flag = False
                    break
                low[l[u]] = low[u]
            if low[r[u]] < low[u]:
                if root[r[u]]:
                    flag = False
                    break
                low[r[u]] = low[u]

    if not flag:
        print(-1)
        return

    # Final assignment of all values from root to leaves
    for u in range(1, tot + 1):
        if u <= n:
            ans[u] = low[u]
        else:
            c = min(ans[l[u]], ans[r[u]])
            if root[u]:
                if c != low[u]:
                    flag = False
                    break
                ans[u] = c
            else:
                ans[u] = c

    print(-1 if not flag else " ".join(map(str, ans[1 : n + 1])))


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/codeForces/