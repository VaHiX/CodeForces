# Problem: CF 1762 F - Good Pairs 
# https://codeforces.com/contest/1762/problem/F

"""
Segment Tree-based solution for counting "good pairs" in an array.
Algorithms: 
    - Segment Tree for range queries and updates
    - Two passes: one forward, one backward to calculate valid extensions
Time Complexity: O(n log MAXA) per test case where MAXA = 100050
Space Complexity: O(MAXA + n) for segment trees and auxiliary arrays
"""

class SegmentTree:
    def __init__(self, data, default=0, func=max):
        """initialize the segment tree with data"""
        self._default = default
        self._func = func
        self._len = len(data)
        self._size = _size = 1 << (self._len - 1).bit_length()

        self.data = [default] * (2 * _size)
        self.data[_size : _size + self._len] = data
        for i in reversed(range(_size)):
            self.data[i] = func(self.data[i + i], self.data[i + i + 1])

    def __setitem__(self, idx, value):
        idx += self._size
        self.data[idx] = value
        idx >>= 1
        while idx:
            self.data[idx] = self._func(self.data[2 * idx], self.data[2 * idx + 1])
            idx >>= 1

    def __len__(self):
        return self._len

    def query(self, start, stop):
        """func of data[start, stop)"""
        start += self._size
        stop += self._size

        res_left = res_right = self._default
        while start < stop:
            if start & 1:
                res_left = self._func(res_left, self.data[start])
                start += 1
            if stop & 1:
                stop -= 1
                res_right = self._func(self.data[stop], res_right)
            start >>= 1
            stop >>= 1

        return self._func(res_left, res_right)

    def __repr__(self):
        return "SegmentTree({0})".format(self.data)


import sys

input = sys.stdin.readline

out = []

INF = 10**9
MAXA = 100050

from operator import add

seen = SegmentTree([INF] * MAXA, default=INF, func=min)
ct = SegmentTree([0] * 500050, func=add)

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))

    nhigh = [n] * n
    nlow = [n] * n

    # Process array from right to left to find bounds for valid extensions
    for i in range(n - 1, -1, -1):
        nhigh[i] = min(n, seen.query(a[i], min(MAXA, a[i] + k + 1)))
        nlow[i] = min(n, seen.query(max(0, a[i] - k), a[i] + 1))

        seen[a[i]] = i

    topct = [0] * (n + 1)
    botct = [0] * (n + 1)
    # Process indices sorted by their values to compute extensions
    for i in sorted(range(n), key=lambda x: a[x]):
        topct[i] = 1 + ct.query(i + 1, nhigh[i])
        botct[i] = nlow[i] - i - ct.query(i + 1, nlow[i])

        ct[i] = 1

    # Propagate counts forward
    for i in range(n - 1, -1, -1):
        topct[i] += topct[nhigh[i]]
        botct[i] += botct[nlow[i]]

    # Calculate total result
    res = sum(topct) + sum(botct)
    res -= (n * (n + 1)) // 2

    out.append(res)

    # Reset data structures for next test case
    for i in range(n):
        seen[a[i]] = INF
        ct[i] = 0


print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/