# Problem: CF 1814 E - Chain Chips
# https://codeforces.com/contest/1814/problem/E

"""
Algorithm: Segment Tree with Dynamic Programming
Time Complexity: O((n + q) * log n)
Space Complexity: O(n)

This solution uses a segment tree to efficiently handle updates and queries on edge weights.
Each node in the segment tree maintains DP states representing minimum costs for different
configuration patterns when moving chips along the chain. The key idea is to compute the minimal
cost to redistribute chips such that no chip ends up on its home vertex.

The segment tree supports:
- Point updates: changing edge weights
- Range queries: computing the minimum cost of chip redistribution

DP states for each node:
- state[0]: cost when left subtree has its minimum cost and right subtree's 2nd state
- state[1]: cost when left subtree has its minimum cost and right subtree's 0th state
- state[2]: cost when left subtree has its 2nd state and right subtree's 2nd state
- state[3]: cost when left subtree has its 3rd state and right subtree's 0th state
"""
import os
import sys
from io import BytesIO, IOBase
from itertools import chain

BUFSIZE = 8192


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()

    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()

    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


if sys.version_info[0] < 3:
    sys.stdin = BytesIO(os.read(0, os.fstat(0).st_size))
else:
    sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)

file = sys.stdin
if os.environ.get("USER") == "loic":
    file = open("data.in")

line = lambda: file.readline().split()
ui = lambda: int(line()[0])
mi = lambda: map(int, line())
li = lambda: list(mi())
lsi = lambda: list(map(int, line()[0]))


class SegmentTree:

    class Node:
        def __init__(self, val):
            self.val = val
            self.state = [0] * 4

        def __repr__(self):
            d = self.__dict__
            res = ""
            for k, v in d.items():
                res += str(k) + " : " + str(v) + "\n"
            return res

    def __init__(self, sz):
        self.sz = 1 << (sz - 1).bit_length()
        self.node = [self._neutral() for _ in range(2 * self.sz)]

    def load(self, data):
        for i in range(len(data)):
            self._initialize(i, data[i])

        r = self.sz - 1
        size = 2
        for i in range(self.sz - 1, 0, -1):
            l = r - size + 1
            self._merge(self.node[i], self.node[i << 1], self.node[i << 1 | 1], l, r)
            if l == 0:
                r = self.sz - 1
                size <<= 1
            else:
                r -= size

    def update(self, pos, new_val):
        self._initialize(pos, new_val)

        l = pos
        r = pos
        size = 1
        i = self.sz + pos

        while i > 1:
            if i & 1:
                l -= size
            else:
                r += size
            i >>= 1
            self._merge(self.node[i], self.node[i << 1], self.node[i << 1 | 1], l, r)
            size <<= 1

    def query(self, l, r):
        tl = self.sz + l
        tr = self.sz + r + 1

        ql = []
        qr = []
        size = 1
        while tl < tr:
            if tl & 1:
                ql.append((tl, size))
                tl += 1
            if tr & 1:
                tr -= 1
                qr.append((tr, size))
            tl >>= 1
            tr >>= 1
            size <<= 1

        cur_r = l
        left = self._neutral()
        for i, sz in chain(ql, reversed(qr)):
            cur_r += sz
            res = self._neutral()
            self._merge(res, left, self.node[i], l, cur_r - 1)
            left = res

        return self._res(res)

    def _neutral(self):

        return self.Node(0)

    def _initialize(self, pos, val):
        node = self.node[self.sz + pos]

        node.val = val
        node.state[0] = 0
        node.state[1] = Z
        node.state[2] = Z
        node.state[3] = val
        if pos == 0 or pos == N - 2:
            node.state[0] = Z

    def _merge(self, node, left, right, l, r):

        node.state[0] = min(
            left.state[0] + right.state[2],
            left.state[1] + right.state[2],
            left.state[1] + right.state[0],
        )
        node.state[1] = min(
            left.state[0] + right.state[3],
            left.state[1] + right.state[3],
            left.state[1] + right.state[1],
        )
        node.state[2] = min(
            left.state[2] + right.state[2],
            left.state[3] + right.state[0],
            left.state[3] + right.state[2],
        )
        node.state[3] = min(
            left.state[2] + right.state[3],
            left.state[3] + right.state[1],
            left.state[3] + right.state[3],
        )

        node.val = min(node.state)

    def _res(self, node):

        return node.val

    def __repr__(self):
        return repr(self.node)


def solve():

    res = []

    st = SegmentTree(N - 1)

    for i, val in enumerate(A):
        st.update(i, val)

    for _ in range(Q):
        K, X = mi()
        K -= 1

        st.update(K, X)
        res.append(2 * st.node[1].val)

    return "\n".join(str(v) for v in res)


Z = 10**18

for test in range(1, 1 + 1):
    N = ui()
    A = li()
    Q = ui()

    print(solve())

file.close()


# https://github.com/VaHiX/CodeForces/