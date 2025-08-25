# Contest 2118, Problem D2: Red Light, Green Light (Hard version)
# URL: https://codeforces.com/contest/2118/problem/D2

# https://codeforces.com/contest/2118

import sys
from collections import defaultdict

input = lambda: sys.stdin.readline().rstrip()  # faster!


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
    n, k = map(int, input().split())  # 1 <= n <= 2 * 10**5, 1 <= k <= 10**15
    p = list(map(int, input().split()))  # 1 <= p[0] < p[1] < ... < p[n-1] <= 10**15
    d = list(map(int, input().split()))  # 0 <= d[i] < k
    q = int(input())  # 1 <= q <= 2 * 10**5
    a = list(map(int, input().split()))  # 1 <= a[i] <= 10**15

    move_right = defaultdict(list)
    move_left = defaultdict(list)
    for i in range(n):
        move_right[(p[i] - d[i]) % k].append(i)
        move_left[(p[i] + d[i]) % k].append(i)

    dsu = DSU(2 * n)
    for b in move_right.values():
        for i in range(len(b) - 1):
            dsu.unite(b[i], b[i + 1] + n)
    for b in move_left.values():
        for i in range(len(b) - 1, 0, -1):
            dsu.unite(b[i] + n, b[i - 1])

    def check(pos):
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
