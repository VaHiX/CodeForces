# Contest 2057, Problem D: Gifts Order
# URL: https://codeforces.com/contest/2057/problem/D

import sys

input = sys.stdin.readline


def ril():  # read int line
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
            # self.data[i] = func(self.data[i + i], self.data[i + i + 1])
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
        b1 = [a[i] - i for i in range(n)]
        b2 = [a[n - 1 - i] - i for i in range(n)]
        ST1 = SegmentTree(b1)
        ST2 = SegmentTree(b2)
        rv.append(max(ST1.ans[1], ST2.ans[1]))
        # print(rv[-1])
        for _ in range(q):
            p, x = ril()
            # b1[p-1] = x - (p-1)
            # b2[n-1-(p-1)] = x - (n-1-(p-1))
            # ST1[p-1] = (b1[p-1], b1[p-1], 0)
            ST1[p - 1] = x - (p - 1)
            ST2[n - 1 - (p - 1)] = x - (n - 1 - (p - 1))
            rv.append(max(ST1.ans[1], ST2.ans[1]))
            # print(rv[-1])

    print("\n".join(map(str, rv)))


main()
