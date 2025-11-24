# Problem: CF 2156 F2 - Strange Operation (Hard Version)
# https://codeforces.com/contest/2156/problem/F2

"""
This code solves the "Strange Operation (Hard Version)" problem using a combination of data structures:
- Fenwick Tree (Binary Indexed Tree) for tracking counts
- Segment Tree (Minimum Query) for efficient range minimum queries
- Greedy strategy based on parity of counts

Key Algorithm:
1. Transform input to 0-indexed
2. For each position, determine if we can apply operation greedily using parity checks
3. If we can't apply operation, assign current minimum value
4. If we can apply operation, find valid j and perform two-step operation
5. Use Fenwick Tree to maintain count of elements and Segment Tree for efficient minimum queries

Time Complexity: O(n log n) per test case due to Fenwick and Segment Tree operations
Space Complexity: O(n) for storing Fenwick Tree, Segment Tree, and auxiliary arrays
"""

import sys

INF = 10**9

input = sys.stdin.readline


class Fenwick:
    def __init__(self, n):
        self.n = n
        self.bit = [0] * n

    def add(self, idx, delta):
        # Add delta to position idx in Fenwick Tree
        n = self.n
        while idx < n:
            self.bit[idx] += delta
            idx |= idx + 1

    def sum(self, idx):
        # Calculate prefix sum up to idx
        res = 0
        while idx >= 0:
            res += self.bit[idx]
            idx = (idx & (idx + 1)) - 1
        return res


class SegTreeMin:
    def __init__(self, init):
        # Initialize Segment Tree with minimum values
        n0 = len(init)
        size = 1
        while size < n0:
            size <<= 1
        self.size = size
        self.N = n0
        self.arr = [INF] * (2 * size)

        for i in range(n0):
            self.arr[size + i] = init[i]

        for i in range(size - 1, 0, -1):
            self.arr[i] = (
                self.arr[2 * i]
                if self.arr[2 * i] < self.arr[2 * i + 1]
                else self.arr[2 * i + 1]
            )

    def update(self, idx, val):
        # Update value at index idx to val
        pos = self.size + idx
        self.arr[pos] = val
        pos >>= 1
        while pos:
            left = self.arr[2 * pos]
            right = self.arr[2 * pos + 1]
            self.arr[pos] = left if left < right else right
            pos >>= 1

    def query(self, l, r):
        # Query minimum in range [l, r]
        if l > r:
            return INF
        l += self.size
        r += self.size
        res = INF
        while l <= r:
            if (l & 1) == 1:
                v = self.arr[l]
                if v < res:
                    res = v
                l += 1
            if (r & 1) == 0:
                v = self.arr[r]
                if v < res:
                    res = v
                r -= 1
            l >>= 1
            r >>= 1
        return res


def solve():
    n_line = input().strip()
    if not n_line:
        n_line = input().strip()
    n = int(n_line)

    p_list = list(map(int, input().split()))

    p = [x - 1 for x in p_list]

    loc = [0] * n
    for i, val in enumerate(p):
        loc[val] = i

    seg = SegTreeMin(loc)
    fen = Fenwick(n)

    for i in range(n):
        fen.add(i, 1)

    ans = [-1] * n
    cur = 1

    for i in range(n):
        if ans[i] >= 0:
            continue

        idx = fen.sum(p[i]) - 1
        if (idx & 1) == 0:

            fen.add(p[i], -1)
            seg.update(p[i], INF)
            ans[i] = cur
            cur += 1
            continue

        j = i
        while True:

            jpos = seg.query(0, p[j] - 1)

            j = jpos

            nxt = fen.sum(p[j]) - 1
            if (nxt & 1) == 0:
                break

        ans[j] = cur
        ans[i] = cur + 1
        cur += 2

        seg.update(p[i], INF)
        seg.update(p[j], INF)
        fen.add(p[i], -1)
        fen.add(p[j], -1)

    out = " ".join(str(x) for x in ans)
    print(out)


def main():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    it = iter(data)
    T = int(next(it))
    out_lines = []
    for _ in range(T):
        n = int(next(it))
        p = [int(next(it)) for _ in range(n)]

        p0 = [x - 1 for x in p]
        loc = [0] * n
        for i, val in enumerate(p0):
            loc[val] = i

        seg = SegTreeMin(loc)
        fen = Fenwick(n)
        for i in range(n):
            fen.add(i, 1)
        ans = [-1] * n
        cur = 1

        for i in range(n):
            if ans[i] >= 0:
                continue
            idx = fen.sum(p0[i]) - 1
            if (idx & 1) == 0:
                fen.add(p0[i], -1)
                seg.update(p0[i], INF)
                ans[i] = cur
                cur += 1
                continue

            j = i
            while True:
                jpos = seg.query(0, p0[j] - 1)
                j = jpos
                nxt = fen.sum(p0[j]) - 1
                if (nxt & 1) == 0:
                    break

            ans[j] = cur
            ans[i] = cur + 1
            cur += 2
            seg.update(p0[i], INF)
            seg.update(p0[j], INF)
            fen.add(p0[i], -1)
            fen.add(p0[j], -1)

        out_lines.append(" ".join(str(x) for x in ans))

    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/