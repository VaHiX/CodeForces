# Problem: CF 2026 E - Best Subsequence
# https://codeforces.com/contest/2026/problem/E

"""
E. Best Subsequence

This problem asks to find the maximum possible value of a subsequence of an array,
where the value of a subsequence is defined as the size of the subsequence minus 
the number of set bits in the bitwise OR of all elements in the subsequence.

The approach uses a greedy algorithm with bipartite matching:
- Each element is represented as a set of bits it has set (0 to 59).
- We model this as a bipartite graph where one side is the elements and the other side
  represents bit positions (0 to 59).
- An edge exists from element i to bit j if a[i] has bit j set.
- The goal is to find a maximum matching in this bipartite graph, which corresponds
  to selecting a subset of elements such that each selected element contributes to
  at most one bit position (minimizing overlap in bit coverage).
- The result is the number of elements minus the size of maximum matching.

Time Complexity: O(n * m * sqrt(n)) where n = number of elements, m = max bits (60)
Space Complexity: O(n * m) for storing edges
"""

class BipartiteMatching:
    def __init__(self, n: int, m: int) -> None:
        assert 0 < n
        assert 0 < m
        self._n = n
        self._m = m
        self._edge = [[] for _ in range(n)]

    def add_edge(self, a: int, b: int) -> bool:
        assert 0 <= a < self._n
        assert 0 <= b < self._m
        self._edge[a].append(b)
        return True

    def matching(self):
        n, m, edge = self._n, self._m, self._edge
        backpath = [-1] * n
        root = [-1] * n
        left2right = [-1] * n
        right2left = [-1] * m
        updated = True
        while updated:  # BFS-based augmenting path search
            updated = False
            q = []
            q_front = 0
            for v in range(n):
                if left2right[v] == -1:
                    root[v] = v
                    q.append(v)
            while q_front < len(q):
                v = q[q_front]
                q_front += 1
                if left2right[root[v]] != -1:  # Already matched
                    continue
                for u in edge[v]:  # For each neighbor in right part (bit positions)
                    if right2left[u] == -1:  # Found an unmatched node in right part -> augment
                        while u != -1:
                            right2left[u] = v
                            left2right[v], u = u, left2right[v]
                            v = backpath[v]
                        updated = True
                        break
                    w = right2left[u]  # Find the node on the left that leads to u
                    if backpath[w] != -1:  # Already visited
                        continue
                    backpath[w] = v  # Mark path back
                    root[w] = root[v]  # Update root for BFS layering
                    q.append(w)
            if updated:
                backpath = [-1] * n
                root = [-1] * n
        return [(v, left2right[v]) for v in range(self._n) if left2right[v] != -1]


for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    m = 60
    bm = BipartiteMatching(n, m)
    for i in range(n):
        for j in range(m):
            if a[i] >> j & 1:  # If the j-th bit is set in a[i]
                bm.add_edge(i, j)
    print(n - len(bm.matching()))  # Maximum value = n - max matching size


# https://github.com/VaHiX/codeForces/