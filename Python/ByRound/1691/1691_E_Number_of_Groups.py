# Problem: CF 1691 E - Number of Groups
# https://codeforces.com/contest/1691/problem/E

"""
Algorithm: Union-Find (DSU) with sorting
Time Complexity: O(n log n + n α(n)) where α(n) is inverse Ackermann function
Space Complexity: O(n)

This solution uses a Disjoint Set Union (DSU) data structure to group segments.
It sorts segments by their left endpoint and processes them sequentially.
For each segment, it checks for overlap with previously seen segments of the opposite color.
If an overlap exists, the segments are merged into the same group.
The DSU tracks connected components and reports the final number of groups.
"""

import sys

input = sys.stdin.buffer.readline


class dsu:
    def __init__(self, n):
        self.n = n
        self.p = list(range(n))  # Parent array for DSU
        self.sz = [1] * n        # Size of each component
        self.comps = n           # Number of connected components

    def rep(self, x):
        # Find the root of x with path compression
        if self.p[x] == x:
            return x
        self.p[x] = self.rep(self.p[x])
        return self.p[x]

    def merge(self, a, b):
        # Merge two sets
        a = self.rep(a)
        b = self.rep(b)

        if a != b:
            # Union by size
            if self.sz[a] < self.sz[b]:
                a, b = b, a

            self.p[b] = a
            self.sz[a] += self.sz[b]
            self.comps -= 1


for _ in range(int(input())):
    n = int(input())
    # Add index to each segment for tracking
    a = [list(map(int, input().split())) + [i] for i in range(n)]

    # Sort segments by their left endpoint
    a.sort(key=lambda s: s[1])
    segs = dsu(n)
    # prev[c] stores (right_endpoint, index) for segments of color c
    prev = [[], []]
    
    for c, l, r, i in a:
        furthest = (-1, 0)
        # Check for overlap with opposite color segments
        for r2, j in prev[c ^ 1]:  # c ^ 1 gives opposite color (0 -> 1, 1 -> 0)
            if r2 >= l:  # If there's overlap
                segs.merge(i, j)
                furthest = max(furthest, (r2, j))

        # Clear list for opposite color and add current segment's right endpoint
        prev[c ^ 1] = []
        if ~furthest[0]:  # If furthest was updated
            prev[c ^ 1].append(furthest)

        prev[c].append((r, i))

    print(segs.comps)


# https://github.com/VaHiX/CodeForces/