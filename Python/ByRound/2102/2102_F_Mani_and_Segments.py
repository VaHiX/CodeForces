# Problem: CF 2102 F - Mani and Segments
# https://codeforces.com/contest/2102/problem/F

"""
F. Mani and Segments

Purpose:
This code solves the problem of counting the number of "cute" subarrays in a given permutation.
A subarray is called cute if the sum of the lengths of its Longest Increasing Subsequence (LIS)
and Longest Decreasing Subsequence (LDS) equals the length of the array plus one.

Algorithms:
- Segment Trees are used to efficiently query and update ranges for LIS/LDS computations.
- Two passes are made over the array using segment trees to compute left and right boundaries
  for each index that determine valid subarrays with property satisfied.
- Dynamic programming-style updates with segment trees to track minimal and maximal values.

Time Complexity:
O(n * log n) per test case due to operations on segment trees.

Space Complexity:
O(n) for storing auxiliary arrays and the segment trees.

"""

import sys

data = sys.stdin.buffer.read().split()
it = iter(data)


def input():
    return next(it)


INF = 10**9 + 7


class SegmentTree:
    def __init__(self, n, is_max=False):
        self.n = n
        self.size = 1
        while self.size < n:
            self.size <<= 1
        self.seg = [0] * (2 * self.size)
        self.op = max if is_max else min
        self.neutral = -INF if is_max else INF

    def build(self):
        seg = self.seg
        for i in range(self.size):
            seg[self.size + i] = self.neutral
        for i in range(self.size - 1, 0, -1):
            seg[i] = self.op(seg[i << 1], seg[i << 1 | 1])

    def upd(self, ind, k):
        seg, op = self.seg, self.op
        i = ind + self.size
        seg[i] = k
        while i > 1:
            i >>= 1
            seg[i] = op(seg[i << 1], seg[i << 1 | 1])

    def get(self, s, t):
        seg, op = self.seg, self.op
        s += self.size
        t += self.size
        res = self.neutral
        while s < t:
            if s & 1:
                res = op(res, seg[s])
                s += 1
            if t & 1:
                t -= 1
                res = op(res, seg[t])
            s >>= 1
            t >>= 1
        return res


def solve():
    n = int(input())
    arr = [0] + [int(x) for x in (input() for _ in range(n))]  # prefix with 0 to make 1-indexed
    L = [1] * (n + 7)
    R = [n] * (n + 7)
    seg_min = SegmentTree(n, is_max=False)
    seg_min.build()
    for i in range(n - 2, 0, -1):  # traverse from right to left
        seg_min.upd(arr[i + 2] - 1, i + 2)  # update position arr[i+2]-1 with value i+2
        a, b = arr[i], arr[i + 1]
        l, r = (a, b) if a < b else (b, a)
        R[i] = min(R[i], seg_min.get(l - 1, r) - 1)  # compute right boundary based on valid range
    seg_max = SegmentTree(n, is_max=True)
    seg_max.build()
    for i in range(3, n + 1):  # traverse from left to right
        seg_max.upd(arr[i - 2] - 1, i - 2)  # update position with previous element's index
        a, b = arr[i], arr[i - 1]
        l, r = (a, b) if a < b else (b, a)
        L[i] = max(L[i], seg_max.get(l - 1, r) + 1)  # compute left boundary based on valid range
    for i in range(n - 1, 0, -1):
        if R[i + 1] < R[i]:
            R[i] = R[i + 1]  # propagate minimal values
    for i in range(2, n + 1):
        if L[i - 1] > L[i]:
            L[i] = L[i - 1]  # propagate maximum values
    ans = R[1]
    for i in range(2, n + 1):
        # Count valid subarrays using derived left and right boundaries:
        ans += R[i - 1] - i + 1
        ans += (i - L[i] + 1) * (R[i] - R[i - 1])
    sys.stdout.write(str(ans) + "\n")


t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/