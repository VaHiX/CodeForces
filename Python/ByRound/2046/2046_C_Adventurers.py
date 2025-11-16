# Problem: CF 2046 C - Adventurers
# https://codeforces.com/contest/2046/problem/C

"""
Algorithm: 2D Coordinate Compression + Fenwick Tree + Binary Search
Time Complexity: O(n * log^2(n))
Space Complexity: O(n)

This solution uses coordinate compression for y-coordinates and Fenwick trees
to efficiently calculate the number of cities in each quadrant for a given
dividing point (x0, y0). It employs binary search over possible dividing points
to find the one that maximizes the minimum number of cities for any merchant.
"""

from sys import stdin

input = lambda: stdin.readline().strip()
from bisect import bisect_left

II = lambda: int(input())
MII = lambda: map(int, input().split())
LII = lambda: list(MII())


class Fenwick:
    def __init__(self, n):
        self.n = n
        self.a = [0] * n

    def add(self, i, cnt):
        i += 1
        while i <= self.n:
            self.a[i - 1] += cnt
            i += i & -i

    def sum(self, i):
        res = 0
        while i > 0:
            res += self.a[i - 1]
            i -= i & -i
        return res

    def __getitem__(self, k):
        x = 0
        cur = 0

        i = 1 << (self.n.bit_length() - 1)
        while i > 0:
            if x + i <= self.n and cur + self.a[x + i - 1] <= k:
                x += i
                cur += self.a[x - 1]
            i >>= 1
        return x


t = II()
for _ in range(t):
    n = II()
    p = []
    ys = []
    for _ in range(n):
        x, y = MII()
        p.append((x, y))
        ys.append(y)

    ys.sort()
    ys = list(set(ys))  # Unique y-coordinates for compression

    tr_l = Fenwick(n)  # Fenwick tree for left half
    tr_r = Fenwick(n)  # Fenwick tree for right half
    p.sort()  # Sort points by x-coordinate
    for i, (x, y) in enumerate(p):
        y = bisect_left(ys, y)  # Compress y-coordinate
        p[i] = (x, y)
        tr_r.add(y, 1)

    ans = 0
    pos = (0, 0)
    for i in range(n):
        x, y = p[i]
        tr_l.add(y, 1)  # Add point to left tree
        tr_r.add(y, -1)  # Remove point from right tree

        # Skip if next point has same x-coordinate (avoid duplicates)
        if i < n - 1 and x == p[i + 1][0]:
            continue

        while True:
            cnt = i + 1  # Total points considered so far
            mi = max(tr_l[ans], tr_r[ans])  # Find minimum count in current quadrants
            mx = min(tr_l[cnt - ans - 1], tr_r[(n - cnt) - ans - 1])

            if mi >= mx:
                break
            ans += 1
            pos = (x + 1, ys[mx])

    print(ans)
    print(*pos)


# https://github.com/VaHiX/CodeForces/