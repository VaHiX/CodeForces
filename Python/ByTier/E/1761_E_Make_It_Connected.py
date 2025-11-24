# Problem: CF 1761 E - Make It Connected
# https://codeforces.com/contest/1761/problem/E

"""
Algorithm: Make It Connected
Purpose: Given a simple undirected graph, determine the minimum number of operations to make it connected.
Each operation chooses a vertex u and flips all edges connected to u (remove existing edges, add missing edges).

Techniques:
- Union-Find (Disjoint Set Union) to track connected components
- Degree counting to identify vertices with no edges
- Greedy strategy to minimize operations based on component sizes and degrees

Time Complexity: O(N^2) per test case due to graph traversal and Union-Find operations
Space Complexity: O(N) for Union-Find structure and auxiliary arrays

Approach:
1. Identify connected components using Union-Find
2. Count degrees of each vertex
3. If already connected (only one component), return 0
4. Otherwise, use greedy logic:
   - If there's a vertex with degree 0, one operation is sufficient to connect it
   - Else, find a vertex with minimal degree within its component to minimize operations
   - If the graph has exactly 2 components, connect them by choosing one vertex from each
   - Otherwise, use two operations to connect all components

Note: The implementation uses Union-Find with path compression for efficiency.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
from collections import defaultdict


class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))

    def find(self, a):
        acopy = a
        while a != self.parent[a]:
            a = self.parent[a]
        while acopy != a:
            self.parent[acopy], acopy = a, self.parent[acopy]
        return a

    def merge(self, a, b):
        self.parent[self.find(b)] = self.find(a)


for _ in range(int(input())):
    N = int(input())
    A = []
    for _ in range(N):
        A.append(input())

    union = UnionFind(N)

    deg = [0] * N
    for i in range(N):
        for j in range(i + 1, N):
            if A[i][j] == "1":
                union.merge(i, j)
                deg[i] += 1
                deg[j] += 1

    cnt = defaultdict(int)
    for i in range(N):
        cnt[union.find(i)] += 1
    if len(cnt.keys()) == 1:
        print(0)
    else:
        ans = None
        for i in range(N):
            if deg[i] == 0:
                ans = [1, [i + 1]]
                break

        if ans == None:
            pre = [float("inf"), -1]
            for i in range(N):
                if deg[i] < pre[0] and deg[i] < cnt[union.find(i)] - 1:
                    pre[0] = deg[i]
                    pre[1] = i

            if pre[1] > -1:
                ans = [1, [pre[1] + 1]]
            else:
                if len(cnt.keys()) == 2:
                    B = [(v, k) for k, v in cnt.items()]
                    B.sort()
                    ans = [B[0][0], []]
                    for i in range(N):
                        if union.find(i) == B[0][1]:
                            ans[1].append(i + 1)
                else:
                    ans = [2, []]
                    for i in range(N - 1):
                        if union.find(i) != union.find(i + 1):
                            ans[1].append(i + 1)
                            ans[1].append(i + 2)
                            break

        print(ans[0])
        print(*ans[1])


# https://github.com/VaHiX/CodeForces/