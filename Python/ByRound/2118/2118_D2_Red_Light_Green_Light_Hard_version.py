# Problem: CF 2118 D2 - Red Light, Green Light (Hard version)
# https://codeforces.com/contest/2118/problem/D2

"""
D2. Red Light, Green Light (Hard version)

Problem Description:
This problem involves determining whether a person starting at given positions on a strip of length 10^15 can escape the strip within 10^100 seconds, based on traffic lights that switch between red and green at periodic intervals.

Each traffic light at position p_i has a delay d_i. It shows red at second l*k + d_i for integer l. The person moves one cell per second and turns around if they encounter a red light.

Algorithm:
- Use Disjoint Set Union (DSU) to group nodes that are connected by the movement rules.
- For each group, check using DSU cycle detection if there's a cycle that would prevent escape.
- Use binary search to find relevant lights when checking validity of a position.
- Time Complexity: O(n log n + q log n)
- Space Complexity: O(n)

Techniques:
- Disjoint Set Union (DSU) with cycle detection.
- Binary search for efficient lookup.
- Modular arithmetic.
"""

import sys
from collections import defaultdict

input = lambda: sys.stdin.readline().rstrip()


class DSU:
    def __init__(self, n):
        self._parent = list(range(n))
        self._cycle = [False] * n

    def find(self, x):
        parent = self._parent
        y = x
        while x != parent[x]:
            x = parent[x]
        while y != x:
            parent[y], y = x, parent[y]
        return x

    def unite(self, x, y):
        x = self.find(x)
        y = self.find(y)
        if x == y:
            self._cycle[x] = True
            return False
        else:
            self._parent[y] = x
            return True

    def is_cycle(self, x):
        return self._cycle[self.find(x)]


def solve_case():
    n, k = map(int, input().split())
    p = list(map(int, input().split()))
    d = list(map(int, input().split()))
    q = int(input())
    a = list(map(int, input().split()))
    move_right = defaultdict(list)
    move_left = defaultdict(list)
    for i in range(n):
        # Group elements by (p[i] - d[i]) % k to determine movement direction
        move_right[(p[i] - d[i]) % k].append(i)
        move_left[(p[i] + d[i]) % k].append(i)
    dsu = DSU(2 * n)
    # Connect elements in move_right groups with corresponding elements in move_left (with offset of n)
    for b in move_right.values():
        for i in range(len(b) - 1):
            dsu.unite(b[i], b[i + 1] + n)
    for b in move_left.values():
        for i in range(len(b) - 1, 0, -1):
            dsu.unite(b[i] + n, b[i - 1])

    def check(pos):
        # Get the category of current position based on (pos % k)
        cat = pos % k
        if not move_right[cat] or pos > p[move_right[cat][-1]]:
            return "YES"
        if pos <= p[move_right[cat][0]]:
            i = move_right[cat][0]
        else:
            lo, hi = 0, len(move_right[cat]) - 1
            while lo + 1 < hi:
                mid = (lo + hi) // 2
                if pos <= p[move_right[cat][mid]]:
                    hi = mid
                else:
                    lo = mid
            i = move_right[cat][hi]
        # If the node is part of a cycle, then we cannot escape.
        if dsu.is_cycle(i + n):
            return "NO"
        return "YES"

    ans = [""] * q
    for i in range(q):
        ans[i] = check(a[i])
    return "\n".join(ans)


ans = []
for _ in range(int(input())):
    ans.append(str(solve_case()))
print("\n".join(ans))


# https://github.com/VaHiX/CodeForces/