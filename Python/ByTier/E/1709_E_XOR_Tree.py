# Problem: CF 1709 E - XOR Tree
# https://codeforces.com/contest/1709/problem/E

"""
Algorithm: XOR Tree
Purpose: Find minimum number of operations to make a tree "good", where no simple path has XOR sum 0.
Approach: 
1. Build a tree from input edges
2. Use DFS to compute prefix XORs from root to each node
3. For each node, maintain a set of XOR values from root to current node
4. When processing nodes in reverse DFS order, check if any XOR value in current node's set can be combined with parent's values to form 0
5. Count nodes that need to be changed (flags)

Time Complexity: O(n * log(max_value)) where n is number of nodes and max_value is up to 2^30
Space Complexity: O(n * log(max_value)) for storing sets
"""
import os
import random
import sys
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


RANDOM = random.getrandbits(32)


class Wrapper(int):
    def __init__(self, x):
        int.__init__(x)

    def __hash__(self):
        return super(Wrapper, self).__hash__() ^ RANDOM


n = II()
nums = LII()
path = [[] for _ in range(n)]
for _ in range(n - 1):
    u, v = GMI()
    path[u].append(v)
    path[v].append(u)

# Compute prefix XORs from root (vertex 0)
pref = nums[:]
stack = [(-1, 0)]
parent = [None] * n
order = []
while stack:
    p, u = stack.pop()
    parent[u] = p
    order.append(u)
    for v in path[u]:
        if v != p:
            pref[v] ^= pref[u]  # XOR prefix up to current node
            stack.append((u, v))

order.reverse()

# Initialize sets for each node
sets_ = [{Wrapper(num)} for num in pref]
flags = [False] * n  # Flag to mark nodes needing change

# Process nodes in reverse DFS order
for i in order:
    if i == 0:
        break
    p = parent[i]
    # If node not yet processed, add its value to set
    if not flags[i]:
        sets_[i].add(Wrapper(pref[i]))
    else:
        sets_[i] = set()

    # Ensure smaller set is merged into larger for efficiency
    if len(sets_[p]) < len(sets_[i]):
        sets_[p], sets_[i] = sets_[i], sets_[p]

    # Check if any combination gives 0 (i.e., x ^ nums[p] exists in parent set)
    for v in sets_[i]:
        if Wrapper(v ^ nums[p]) in sets_[p]:
            flags[p] = True

    # Merge sets
    for v in sets_[i]:
        sets_[p].add(Wrapper(v))

    sets_[i] = None

print(sum(flags))


# https://github.com/VaHiX/CodeForces/