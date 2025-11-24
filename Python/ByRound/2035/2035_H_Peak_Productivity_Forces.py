# Problem: CF 2035 H - Peak Productivity Forces
# https://codeforces.com/contest/2035/problem/H

"""
Algorithm: Peak Productivity Forces
Purpose: Transform permutation `a` to permutation `b` using at most 2n operations.
Each operation chooses an index i and performs two cyclic shifts:
- Shift a[0:i-1] by 1 to the right
- Shift a[i+1:n] by 1 to the right
- Position i is not shifted

Time Complexity: O(n^2) for each test case in worst case, but with practical optimizations
Space Complexity: O(n) for storing mappings and auxiliary data structures

Techniques:
- Mapping permutations to positions
- LinkedList simulation for efficient node movement
- Greedy approach to minimize operations
"""

import os
import random
import sys
from collections import defaultdict
from io import BytesIO, IOBase

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


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")
sys.setrecursionlimit(10000)

mag = random.getrandbits(20)

lsum = lambda l, r: (l + r) * (r - l + 1) // 2


class D:
    def __init__(self, type=int):
        self.d = defaultdict(type)
        self.mag = random.getrandbits(20)

    def __setitem__(self, key, value):
        self.d[key + self.mag] = value

    def __getitem__(self, key):
        return self.d[key + self.mag]

    def __delitem__(self, key):
        del self.d[key + self.mag]

    def __contains__(self, key):
        return key + self.mag in self.d

    def __iter__(self):
        self.keys = iter(self.d.keys())
        return self

    def __next__(self):
        return next(self.keys) - self.mag

    def __len__(self):
        return len(self.d)


ii = lambda: int(input())
mii = lambda: map(int, input().split())
fii = lambda: map(float, input().split())
lmii = lambda: list(map(int, input().split()))
i2c = lambda n: chr(ord("a") + n)
c2i = lambda c: ord(c) - ord("a")


mod = 10**9 + 7


class Node:
    def __init__(self, v=0, mark=0, pref=None, next=None):
        self.v = v
        self.mark = mark
        self.pref = pref
        self.next = next


def move(l, i):
    if i < len(l) - 2:
        tmp = l[-1]
        for j in range(len(l) - 1, i + 1, -1):
            l[j] = l[j - 1]
        l[i + 1] = tmp
    if i > 1:
        tmp = l[i - 1]
        for j in range(i - 1, 0, -1):
            l[j] = l[j - 1]
        l[0] = tmp
    return l


def solve():
    n = ii()
    l1 = lmii()
    l2 = lmii()

    if n == 1:
        print(0)
        print("")
        return
    elif n == 2:
        if l1[0] == l2[0]:
            print(0)
            print("")
        else:
            print(-1)
        return

    # Map the values in l2 to their indices (position mapping)
    map2 = [0] * (n + 1)
    for i, k in enumerate(l2):
        map2[k] = i
    l = [map2[k] for k in l1]  # Transform l1 according to l2 mapping
    res = []  # Store the operations

    # Create a linked list for managing elements
    L = []
    for i in range(n):
        L.append(Node())
    tail = Node()
    tail.mark = -1
    L.append(tail)
    for i in range(n):
        k = l[i]
        L[k].v = i
        L[k].mark = k
    for i in range(1, n + 1):
        p = L[l[i - 1]]
        c = tail if i == n else L[l[i]]
        p.next = c
        c.pref = p
    head = Node()
    head.next = L[l[0]]
    L[l[0]].pref = head

    def delete(node):
        pre, nxt = node.pref, node.next
        pre.next = nxt
        nxt.pref = pre
        node.next = None
        node.pref = None

    def insert(node, left):
        nxt = left.next
        left.next = node
        node.pref = left
        nxt.pref = node
        node.next = nxt

    # Adjust nodes to align correctly
    def move_node(ci, i):
        ci.v -= 1
        if i > 0:
            pre = ci.pref
            delete(pre)
            insert(pre, head)
            pre.v -= i
        if i < n - 1:
            right = tail.pref
            delete(right)
            insert(right, ci)
            right.v -= n - 1 - i

    # Show current order
    def show():
        r = []
        p = head
        while p.next:
            p = p.next
            r.append(p.mark)

        return r[:-1]

    # Adjust for initial case
    if tail.pref.mark == n - 1:
        res.append(0)
        move_node(head.next, 0)
    l_ = show()
    for i in range(n):
        k = l_[i]
        L[k].v = i
    cur = n - 1
    # Process to move to correct positions
    while cur > 0:
        cur_node = L[cur]
        i = cur_node.v + (n - 1 - cur)
        if i < n - 1:
            move_node(cur_node.next, i + 1)
            res.append(i + 1)
            cur -= 1
        else:
            cur_node_1 = L[cur - 1]
            j = cur_node_1.v + (n - 1 - cur)
            if j < n - 3:
                move_node(cur_node_1.next, j + 1)
                res.append(j + 1)
                cur -= 1
                i = cur_node.v + (n - 1 - cur)
                move_node(cur_node.next, i + 1)
                res.append(i + 1)
                cur -= 1
            else:
                move_node(cur_node_1.next, j + 1)
                res.append(j + 1)
                cur -= 1
                move_node(head.next, 0)
                res.append(0)
                cur -= 1

    if cur == 0:
        res.append(0)
        move_node(head.next, 0)

    # Adjust final sequence
    if head.next.mark == 0:
        for i in range(n - 1):
            if i == 0 or tail.pref.mark < head.next.next.mark:
                res.append(0)
                move_node(head.next, 0)
            else:
                res.append(1)
                move_node(head.next.next, 1)
    elif head.next.mark == 1:
        res.append(1)
        move_node(head.next.next, 1)
        for i in range(n - 3):
            if i == 0 or tail.pref.mark < head.next.next.mark:
                res.append(0)
                move_node(head.next, 0)
            else:
                res.append(1)
                move_node(head.next.next, 1)
        res.append(n - 1)
        move_node(tail.pref, n - 1)

    # Adjust indices to 1-based indexing
    res = [k + 1 for k in res]
    print(len(res))
    print(*res)


for _ in range(ii()):
    solve()


# https://github.com/VaHiX/CodeForces/