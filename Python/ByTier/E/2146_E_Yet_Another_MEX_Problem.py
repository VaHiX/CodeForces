# Problem: CF 2146 E - Yet Another MEX Problem
# https://codeforces.com/contest/2146/problem/E

"""
Code Purpose:
This solution efficiently computes the maximum weight of all subarrays ending at each position in the input array.

The algorithm uses a Lazy Segment Tree to maintain the count of elements seen so far, enabling fast updates and queries. For each element in the array:
1. It increments the count of that element in the segment tree
2. It resets the count of that element to zero
3. It queries the maximum value in the segment tree to determine the current maximum weight

Algorithms/Techniques:
- Lazy Segment Tree for efficient range updates and queries
- MEX calculation via tracking element counts

Time Complexity: O(n log n)
Space Complexity: O(n)
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
ii = lambda: int(input())
mii = lambda: map(int, input().split())
lii = lambda: list(mii())


class LazySegmentTree:
    __slots__ = (
        "n",
        "height",
        "size",
        "idval",
        "idlazy",
        "op",
        "apply",
        "compose",
        "tree",
        "lazy",
    )

    def __init__(self, nums, idval, idlazy, op, apply, compose):
        self.n = len(nums)
        self.height = (self.n - 1).bit_length()
        self.size = 1 << self.height
        self.idval = idval
        self.idlazy = idlazy
        self.op = op
        self.apply = apply
        self.compose = compose

        self.tree = [idval for _ in range(2 * self.size)]
        self.tree[self.size : self.size + self.n] = nums
        for i in range(self.size - 1, 0, -1):
            self.pushup(i)
        self.lazy = [idlazy for _ in range(self.size)]

    def pushup(self, rt):
        self.tree[rt] = self.op(self.tree[rt * 2], self.tree[rt * 2 + 1])

    def pushdown(self, rt):
        if self.lazy[rt] == self.idlazy:
            return
        self.modify(rt * 2, self.lazy[rt])
        self.modify(rt * 2 + 1, self.lazy[rt])
        self.lazy[rt] = self.idlazy

    def set(self, idx, val):
        idx += self.size
        for i in range(self.height, 0, -1):
            self.pushdown(idx >> i)
        self.tree[idx] = val
        for i in range(1, self.height + 1):
            self.pushup(idx >> i)

    def update(self, left, right, val):
        if left > right:
            return
        left += self.size
        right += self.size

        for i in range(self.height, 0, -1):
            if left >> i << i != left:
                self.pushdown(left >> i)
            if (right + 1) >> i << i != right + 1:
                self.pushdown(right >> i)

        l, r = left, right
        while left <= right:
            if left & 1:
                self.modify(left, val)
                left += 1
            if not right & 1:
                self.modify(right, val)
                right -= 1
            left >>= 1
            right >>= 1

        left, right = l, r
        for i in range(1, self.height + 1):
            if left >> i << i != left:
                self.pushup(left >> i)
            if (right + 1) >> i << i != right + 1:
                self.pushup(right >> i)

    def modify(self, rt, val):
        self.tree[rt] = self.apply(val, self.tree[rt])
        if rt < self.size:
            self.lazy[rt] = self.compose(val, self.lazy[rt])

    def get(self, idx):
        idx += self.size
        for i in range(self.height, 0, -1):
            self.pushdown(idx >> i)
        return self.tree[idx]

    def getall(self):
        for idx in range(1, self.size):
            self.pushdown(idx)
        return self.tree[self.size : self.size + self.n]

    def query(self, left, right):
        if left > right:
            return self.idval
        left += self.size
        right += self.size

        for i in range(self.height, 0, -1):
            if left >> i << i != left:
                self.pushdown(left >> i)
            if (right + 1) >> i << i != right + 1:
                self.pushdown(right >> i)

        lres, rres = self.idval, self.idval
        while left <= right:
            if left & 1:
                lres = self.op(lres, self.tree[left])
                left += 1
            if not right & 1:
                rres = self.op(self.tree[right], rres)
                right -= 1
            left >>= 1
            right >>= 1

        return self.op(lres, rres)

    def all(self):
        return self.tree[1]


fmax = lambda a, b: a if a > b else b


def solve():
    n = ii()
    arr = lii()
    # Initialize segment tree with zeros
    seg = LazySegmentTree([0] * (n + 1), 0, 0, fmax, int.__add__, int.__add__)
    ans = []
    # Process each element in the input array
    for x in arr:
        # Increment the count of element x
        seg.update(0, x, 1)
        # Reset count of element x to zero (as it will be considered in current subarray)
        seg.set(x, 0)
        # Query maximum in the segment tree to find current max weight
        ans.append(seg.all())
    return ans


for _ in range(ii()):
    print(*solve())


# https://github.com/VaHiX/CodeForces/