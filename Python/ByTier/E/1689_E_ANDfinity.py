# Problem: CF 1689 E - ANDfinity
# https://codeforces.com/contest/1689/problem/E

"""
Algorithm: ANDfinity Problem Solution
Approach:
1. First, we handle all zeros in the array by incrementing them to 1 (1 operation per zero).
2. Then, we check if the graph formed by bitwise AND operation is already connected.
3. If not connected, we try to make it connected by:
   - Incrementing each element by 1 and checking connectivity
   - Decrementing each element by 1 (if > 0) and checking connectivity
4. If still not connected, we use a greedy approach:
   - Find elements with the highest lowest set bit
   - Increment one and decrement the other to create connectivity

Time Complexity: O(n^2 * log(max_value)) where n is the number of elements
Space Complexity: O(n) for Union-Find structure and auxiliary arrays

This is a graph connectivity problem with bitwise AND operations.
The key insight is that two nodes are connected if their bitwise AND is > 0.
We use Union-Find to efficiently check connectivity and try minimal operations.
"""

import os
import sys
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


class UnionFind:
    def __init__(self, n):
        self.n = n
        self.parents = [-1] * n
        self.group = n

    def find(self, x):
        if self.parents[x] < 0:
            return x
        else:
            self.parents[x] = self.find(self.parents[x])  # Path compression
            return self.parents[x]

    def union(self, x, y):
        x = self.find(x)
        y = self.find(y)

        if x == y:
            return
        self.group -= 1
        if self.parents[x] > self.parents[y]:
            x, y = y, x

        self.parents[x] += self.parents[y]
        self.parents[y] = x

    def size(self, x):
        return -self.parents[self.find(x)]

    def same(self, x, y):
        return self.find(x) == self.find(y)

    def members(self, x):
        root = self.find(x)
        return [i for i in range(self.n) if self.find(i) == root]

    def roots(self):
        return [i for i, x in enumerate(self.parents) if x < 0]

    def group_count(self):
        return self.group

    def all_group_members(self):
        dic = {r: [] for r in self.roots()}
        for i in range(self.n):
            dic[self.find(i)].append(i)
        return dic

    def __str__(self):
        return "\n".join("{}: {}".format(r, self.members(r)) for r in self.roots())


def solve():
    int(input())
    A = list(map(int, input().split()))
    ans = 0
    for i, a in enumerate(A):
        if a == 0:
            A[i] = 1
            ans += 1

    def is_connected():
        # Union-Find for checking connectivity using bit operations
        UF = UnionFind(30)  # 30 bits max for numbers < 2^30
        bits = 0  # Track which bits are set in the current array
        cnt = 0   # Count unique bit groups
        for a in A:
            ind = -1  # Index of the first bit set in current number
            for i in range(30):
                if a >> i & 1:  # Check if i-th bit is set
                    if ind == -1:
                        ind = i
                    else:
                        UF.union(i, ind)  # Union bits i and ind
                    if not bits >> i & 1:  # If bit i is not already seen
                        bits |= 1 << i  # Mark bit i as seen
                        cnt += 1
        # Return whether all bits are connected to the first one
        return cnt == UF.size(ind)

    if is_connected():
        print(ans)
        print(*A)
        return

    # Try to add one operation to make it connected (increment each element by 1)
    for i, a in enumerate(A):
        A[i] += 1
        if is_connected():
            print(ans + 1)
            print(*A)
            return
        A[i] = a  # Revert
        if a != 1:  # Only decrement if original value > 0
            A[i] -= 1
            if is_connected():
                print(ans + 1)
                print(*A)
                return
            A[i] = a  # Revert

    # If still not connected, use more complex approach
    # Find elements with highest lowest set bit to optimize operations
    lst = []
    ma = 0  # Max lowest bit set in any element
    for i, a in enumerate(A):
        b = a & -a  # Get lowest set bit (two's complement trick)
        if b > ma:
            lst = [i]
            ma = b
        elif b == ma and len(lst) == 1:
            lst.append(i)

    i, j = lst
    A[i] += 1   # Increment one
    A[j] -= 1   # Decrement the other
    print(ans + 2)
    print(*A)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/