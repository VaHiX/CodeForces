# Problem: CF 1778 F - Maximizing Root
# https://codeforces.com/contest/1778/problem/F

"""
Algorithm: Tree Dynamic Programming with GCD optimization
Time Complexity: O(n * d * log(max(a_i)) * k) where d is the average number of divisors
Space Complexity: O(n * d) where d is the average number of divisors

This solution uses a DFS-based tree DP approach where for each node, we maintain
a dictionary mapping GCD values to the minimum operations needed to achieve that GCD
in its subtree. We propagate these values up the tree and finally determine the
maximum possible value of the root node after at most k operations.
"""

import math
import os
import sys
from io import BytesIO, IOBase

BUFSIZE = 4096
inf = float("inf")


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


@bootstrap
def dfs(u, p=-1):
    ans = {nums[0]: 0}  # Initialize with root's value and 0 operations
    for v in path[u]:
        if v != p:
            yield dfs(v, u)  # Recursively process child
            new_ans = {}
            # Combine results from child with current answers
            for x in ans:
                for y in res[v]:
                    note = math.gcd(x, y)
                    if note not in new_ans or new_ans[note] > ans[x] + res[v][y]:
                        new_ans[note] = ans[x] + res[v][y]
            ans = new_ans
            res[v] = None
    # Update answers for current node based on its value
    new_ans = {1: 0}
    for x in ans:
        times = math.gcd(x, nums[u])  # Compute GCD with current node's value
        if times not in new_ans or new_ans[times] > ans[x]:
            new_ans[times] = ans[x]
        if u:  # Not root node
            val = math.gcd(times * times, nums[0])  # Special case for root
            if val not in new_ans or new_ans[val] > ans[x] + 1:
                new_ans[val] = ans[x] + 1
    res[u] = new_ans  # Store computed values for this node
    yield


t = II()
for test_case in range(t):
    n, k = MII()
    nums = LII()
    path = [[] for _ in range(n)]
    for _ in range(n - 1):
        u, v = GMI()
        path[u].append(v)
        path[v].append(u)
    res = [None] * n
    dfs(0)
    tmp = res[0]
    ans = 1
    # Find maximum possible GCD that can be achieved with at most k operations
    for x in tmp:
        if tmp[x] < k and x > ans:
            ans = x
    print(ans * nums[0])  # Multiply by root value to get final result


# https://github.com/VaHiX/CodeForces/