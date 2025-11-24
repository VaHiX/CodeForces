# Problem: CF 1679 D - Toss a Coin to Your Graph...
# https://codeforces.com/contest/1679/problem/D

"""
Algorithm: Binary Search on Answer + Topological Sort (Kahn's Algorithm)
Time Complexity: O((n + m) * log(max(a))) where n is vertices, m is edges, and max(a) is the maximum value in array a
Space Complexity: O(n + m) for the graph storage and auxiliary arrays

This problem requires finding the minimum possible maximum value in Masha's notebook when performing exactly k-1 operations
on a directed graph. We use binary search on the answer to find the minimum value such that it's possible to perform
k-1 operations while never exceeding this value. For each candidate value, we use Kahn's algorithm to check if it's possible
to traverse the graph for at least k-1 steps while all values in the path are less than or equal to the candidate.
"""

import sys
from array import array
from collections import deque

input = lambda: sys.stdin.buffer.readline().decode().strip()
inp = lambda dtype: [dtype(x) for x in input().split()]
inp_2d = lambda dtype, n: [dtype(input()) for _ in range(n)]
inp_2ds = lambda dtype, n: [inp(dtype) for _ in range(n)]
ceil1 = lambda a, b: (a + b - 1) // b
debug = lambda *x: print(*x, file=sys.stderr)
out = array("i")


class graph:
    def __init__(self, n):
        self.n = n
        self.gdict = [array("i") for _ in range(n + 1)]
        self.deg = array("i", [0] * (n + 1))

    def add_uniedge(self, node1, node2):
        self.gdict[node1].append(node2)
        self.deg[node2] += 1

    def kahn(self):
        # Initialize queue with nodes having in-degree 0
        que, cnt = deque([(i, 0) for i in range(1, self.n + 1) if not self.deg[i]]), 0
        ret = 0

        while que:
            s, lev = que.popleft()
            ret = max(ret, lev)

            for i in self.gdict[s]:
                self.deg[i] -= 1
                # Only continue traversal if the value at node i is <= md
                if a[i] <= md and not self.deg[i]:
                    que.append((i, lev + 1))

            cnt += 1
        # Check if all valid nodes were processed and we reached at least k-1 steps
        return cnt != valids or ret >= k - 1


n, m, k = inp(int)
a = array("i", [0] + inp(int))
g = graph(n)

for i in range(m):
    u, v = inp(int)
    g.add_uniedge(u, v)

# Binary search bounds
be, en, ans = min(a[1:]), 10**9, -1
orgdeg = g.deg[:]

while be <= en:
    md, valids = (be + en) >> 1, n
    # Mark nodes whose values exceed the current mid value
    for i in range(1, n + 1):
        if a[i] > md:
            valids -= 1
            g.deg[i] = 10**6
            for j in g.gdict[i]:
                g.deg[j] -= 1

    if g.kahn():
        # If valid path exists for k-1 steps, try smaller value
        en, ans = md - 1, md
    else:
        # If not valid, try larger value
        be = md + 1

    # Reset degrees for next iteration
    g.deg = orgdeg[:]

print(ans)


# https://github.com/VaHiX/CodeForces/