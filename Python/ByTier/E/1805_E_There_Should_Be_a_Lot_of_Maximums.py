# Problem: CF 1805 E - There Should Be a Lot of Maximums
# https://codeforces.com/contest/1805/problem/E

"""
Problem: E. There Should Be a Lot of Maximums
Algorithm: Tree DFS, Counter, Two Pointers, Preprocessing
Time Complexity: O(n log n)
Space Complexity: O(n)

This solution computes the MAD (Maximum Double) for each edge in a tree.
MAD is the maximum value that appears at least twice in a subtree.
The approach:
1. Preprocess all values to find the guaranteed maximum MAD and values appearing exactly twice.
2. Find the path between the two occurrences of the maximum value that appears exactly twice.
3. For each edge on this path, compute the maximum MAD in the two subtrees formed when that edge is removed.
4. Use prefix/suffix maximum arrays to efficiently calculate left and right maximums.
"""

import os
import random
import sys
from collections import Counter
from io import BytesIO, IOBase


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


BUFSIZE = 4096


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

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

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()


sys.stdin = IOWrapper(sys.stdin)
sys.stdout = IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")


def I():
    return input()


def II():
    return int(input())


def MII():
    return map(int, input().split())


def LI():
    return list(input().split())


def LII():
    return list(map(int, input().split()))


def GMI():
    return map(lambda x: int(x) - 1, input().split())


def LGMI():
    return list(map(lambda x: int(x) - 1, input().split()))


inf = float("inf")

from types import GeneratorType


def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to

    return wrappedfunc


RANDOM = random.getrandbits(32)


class Wrapper(int):
    def __init__(self, x):
        int.__init__(x)

    def __hash__(self):
        return super(Wrapper, self).__hash__() ^ RANDOM


n = II()
path = [[] for _ in range(n)]
for idx in range(n - 1):
    u, v = GMI()
    path[u].append((v, idx))
    path[v].append((u, idx))

vals = LII()
cnt = Counter(sorted(vals))

guaranteed_maxi = 0
twice = []
for v in cnt:
    if cnt[v] == 2:
        twice.append(v)
    elif cnt[v] > 2:
        guaranteed_maxi = max(guaranteed_maxi, v)

if len(twice) == 0:
    print(*[guaranteed_maxi] * (n - 1), sep="\n")
    exit()

twice.sort()
l, r = -1, -1
for i in range(n):
    if vals[i] == twice[-1]:
        if l == -1:
            l = i
        else:
            r = i
            break

ans = [max(guaranteed_maxi, twice[-1])] * (n - 1)

parent = [None] * n
stack = [(l, -1)]
while stack:
    u, p = stack.pop()
    for v, i in path[u]:
        if v != p:
            stack.append((v, u))
            parent[v] = [u, i]

in_path = [0] * n
maxi_path = [(r, -1)]
cur = (r, -1)
while cur[0] != l:
    in_path[cur[0]] = 1
    cur = parent[cur[0]]
    maxi_path.append(cur)
in_path[l] = 1

M = len(maxi_path)
side_value = [[] for _ in range(M)]
for i in range(M):
    rt = maxi_path[i][0]
    stack = [(rt, -1)]
    while stack:
        u, p = stack.pop()
        if cnt[vals[u]] == 2:
            side_value[i].append(vals[u])
        for v, _ in path[u]:

            if v != p and in_path[v] == 0:
                stack.append((v, u))

left_maxi = [0] * M
cnt_left = Counter()
for i in range(M):
    left_maxi[i] = left_maxi[i - 1]
    for v in side_value[i]:
        cnt_left[Wrapper(v)] += 1
        if cnt_left[Wrapper(v)] == 2:
            left_maxi[i] = max(left_maxi[i], v)

right_maxi = [0] * M
cnt_right = Counter()
for i in range(M - 1, -1, -1):
    if i != M - 1:
        right_maxi[i] = right_maxi[i + 1]
    for v in side_value[i]:
        cnt_right[Wrapper(v)] += 1
        if cnt_right[Wrapper(v)] == 2:
            right_maxi[i] = max(right_maxi[i], v)

for i in range(1, M):
    ans[maxi_path[i][1]] = max(left_maxi[i - 1], right_maxi[i], guaranteed_maxi)

print(*ans, sep="\n")


# https://github.com/VaHiX/CodeForces/