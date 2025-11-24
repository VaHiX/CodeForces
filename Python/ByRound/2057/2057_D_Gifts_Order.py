# Problem: CF 2057 D - Gifts Order
# https://codeforces.com/contest/2057/problem/D

"""
Segment Tree-based solution for maximizing convenience of sweater selection.

The problem asks to find the maximum value of (max(a[l:r+1]) - min(a[l:r+1]) - (r - l)) 
over all subarrays [l, r]. This can be transformed by defining b[i] = a[i] - i, then
the expression becomes max(b[r] - b[l]) - (r - l) = (max(b[r] - b[l]) - (r - l)).

To optimize this, we use two segment trees:
- One for b[i] = a[i] - i 
- One for b[i] = a[n-1-i] - i (reversed)
This allows us to compute maximum convenience efficiently.

Time complexity: O((n + q) * log n)
Space complexity: O(n)
"""

import sys

input = sys.stdin.readline


def ril():
    return map(int, input().split())


class SegmentTree:
    def __init__(self, data):
        """initialize the segment tree with data"""
        self._len = len(data)
        self._size = _size = 1 << (self._len - 1).bit_length()

        self.min = [1e10] * (2 * _size)
        self.min[_size : _size + self._len] = data
        self.max = [-1e10] * (2 * _size)
        self.max[_size : _size + self._len] = data
        self.ans = [0] * (2 * _size)
        for i in reversed(range(_size)):

            self.min[i] = min(self.min[i + i], self.min[i + i + 1])
            self.max[i] = max(self.max[i + i], self.max[i + i + 1])
            self.ans[i] = max(
                self.ans[i],
                self.ans[i + i],
                self.ans[i + i + 1],
                self.max[i + i + 1] - self.min[i + i],
            )

    def __setitem__(self, idx, value):
        idx += self._size
        self.min[idx] = self.max[idx] = value
        idx >>= 1
        while idx:
            self.min[idx] = min(self.min[idx + idx], self.min[idx + idx + 1])
            self.max[idx] = max(self.max[idx + idx], self.max[idx + idx + 1])
            self.ans[idx] = max(
                self.ans[idx + idx],
                self.ans[idx + idx + 1],
                self.max[idx + idx + 1] - self.min[idx + idx],
            )
            idx >>= 1

    def __len__(self):
        return self._len

    def __repr__(self):
        return "SegmentTree({0})".format(self.data)


def main():
    t = int(input())

    rv = []
    for _ in range(t):
        n, q = ril()
        a = list(ril())
        # Transform array: b[i] = a[i] - i to simplify the calculation
        b1 = [a[i] - i for i in range(n)]
        b2 = [a[n - 1 - i] - i for i in range(n)]
        ST1 = SegmentTree(b1)
        ST2 = SegmentTree(b2)
        # The maximum convenience is stored in the root of both segment trees
        rv.append(max(ST1.ans[1], ST2.ans[1]))

        for _ in range(q):
            p, x = ril()
            
            # Update both segment trees with new value
            # The index in segment tree is 0-based, so we subtract 1 from p
            ST1[p - 1] = x - (p - 1)
            ST2[n - 1 - (p - 1)] = x - (n - 1 - (p - 1))
            rv.append(max(ST1.ans[1], ST2.ans[1]))

    print("\n".join(map(str, rv)))


main()


# https://github.com/VaHiX/CodeForces/