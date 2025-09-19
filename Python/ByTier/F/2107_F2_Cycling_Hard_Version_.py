# Contest 2107, Problem F2: Cycling (Hard Version)
# URL: https://codeforces.com/contest/2107/problem/F2

import bisect


class Line:
    def __init__(self, m, b):
        self.m = m
        self.b = b
        self.x = -float("inf")

    def intersect(self, other):
        if self.m == other.m:
            return float("inf")
        return (other.b - self.b) / (self.m - other.m)

    def __lt__(self, other):
        return self.m < other.m


class chtDynamicMin:
    def __init__(self):
        self.hull = []

    def add_line(self, m, b):
        line = Line(-m, -b)
        idx = bisect.bisect_left(self.hull, line)
        if idx < len(self.hull) and self.hull[idx].m == line.m:
            if line.b <= self.hull[idx].b:
                return
            else:
                del self.hull[idx]
                idx = bisect.bisect_left(self.hull, line)
        if idx > 0 and self.hull[idx - 1].m == line.m:
            if line.b <= self.hull[idx - 1].b:
                return
            else:
                del self.hull[idx - 1]
                idx = bisect.bisect_left(self.hull, line)
        self.hull.insert(idx, line)
        if self.is_bad(idx):
            del self.hull[idx]
            return
        while idx > 0 and self.is_bad(idx - 1):
            del self.hull[idx - 1]
            idx -= 1
        while idx < len(self.hull) - 1 and self.is_bad(idx + 1):
            del self.hull[idx + 1]
        self.update_x(idx)
        if idx > 0:
            self.update_x(idx - 1)
        if idx < len(self.hull) - 1:
            self.update_x(idx + 1)

    def is_bad(self, idx):
        if idx <= 0 or idx >= len(self.hull) - 1:
            return False
        a = self.hull[idx - 1]
        b_line = self.hull[idx]
        c = self.hull[idx + 1]
        return a.intersect(c) <= a.intersect(b_line)

    def update_x(self, idx):
        if idx == 0:
            self.hull[idx].x = -float("inf")
            return
        prev = self.hull[idx - 1]
        curr = self.hull[idx]
        curr.x = prev.intersect(curr)

    def query(self, x):
        if not self.hull:
            return float("inf")
        low, high = 0, len(self.hull)
        while low < high:
            mid = (low + high) // 2
            if self.hull[mid].x <= x:
                low = mid + 1
            else:
                high = mid
        idx = low - 1
        line = self.hull[idx]
        return -(line.m * x + line.b)


import sys

input = sys.stdin.read().split()
ptr = 0
t = int(input[ptr])
ptr += 1
for _ in range(t):
    n = int(input[ptr])
    ptr += 1
    a = list(map(int, input[ptr : ptr + n]))
    ptr += n
    a = [0] + a
    pv = [0] * (n + 1)
    stack = []
    for i in range(n, 0, -1):
        while stack and stack[-1][0] >= a[i]:
            pv[stack.pop()[1]] = i
        stack.append((a[i], i))
    while stack:
        pv[stack.pop()[1]] = 0
    dp = [0] * (n + 1)
    cht = chtDynamicMin()
    output = []
    for i in range(1, n + 1):
        dp[i] = dp[pv[i]] + a[i] * (i - pv[i]) + (i - pv[i] - 1)
        m = 2 + a[i]
        c = dp[i] - m * i
        cht.add_line(m, c)
        ans = cht.query(i)
        output.append(str(ans))
    print(" ".join(output))
