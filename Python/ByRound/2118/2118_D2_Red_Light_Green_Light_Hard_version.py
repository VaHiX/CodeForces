# Problem: CF 2118 D2 - Red Light, Green Light (Hard version)
# https://codeforces.com/contest/2118/problem/D2

"""
Problem: D2. Red Light, Green Light (Hard version)

Purpose:
This code determines whether a person starting at a given position on a strip will eventually leave the strip within 10^100 seconds when moving according to traffic light rules.
The strip has n traffic lights; each light changes at time l*k + d_i where l is an integer and d_i is the delay.
If at any second that position has a red light, the person turns around. Then moves one step forward or backward.

Algorithms:
- Disjoint Set Union (DSU) to track connected components of movement constraints.
- Binary search on sorted positions for efficient lookup.

Time Complexity: O(n log n + q log n)
Space Complexity: O(n)

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
        # Group indices of positions based on (pos - delay) % k
        move_right[(p[i] - d[i]) % k].append(i)
        # Group indices of positions based on (pos + delay) % k
        move_left[(p[i] + d[i]) % k].append(i)
    dsu = DSU(2 * n)
    # Connect elements in move_right groups with their next neighbor in DSU
    for b in move_right.values():
        for i in range(len(b) - 1):
            dsu.unite(b[i], b[i + 1] + n)
    # Connect elements in move_left groups in reverse order
    for b in move_left.values():
        for i in range(len(b) - 1, 0, -1):
            dsu.unite(b[i] + n, b[i - 1])

    def check(pos):
        cat = pos % k
        # If no elements in current group or position is beyond largest one
        if not move_right[cat] or pos > p[move_right[cat][-1]]:
            return "YES"
        if pos <= p[move_right[cat][0]]:
            i = move_right[cat][0]
        else:
            # Binary search to find the smallest index satisfying constraint
            lo, hi = 0, len(move_right[cat]) - 1
            while lo + 1 < hi:
                mid = (lo + hi) // 2
                if pos <= p[move_right[cat][mid]]:
                    hi = mid
                else:
                    lo = mid
            i = move_right[cat][hi]
        # If the component has a cycle, we can't escape from this group
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


# https://github.com/VaHiX/codeForces/