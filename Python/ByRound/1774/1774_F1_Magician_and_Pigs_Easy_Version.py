# Problem: CF 1774 F1 - Magician and Pigs (Easy Version)
# https://codeforces.com/contest/1774/problem/F1

"""
Algorithm: Simulation with Damage Propagation and Counter Optimization
Time Complexity: O(n * max_damage) where max_damage <= 2*10^5
Space Complexity: O(n)

This solution simulates a series of operations on pigs, tracking their health points.
It uses a counter to track how many pigs have each health value, and efficiently
manages damage propagation during "Repeat" operations by doubling the damage and
updating the counter.

The key insight is that when we repeat operations, we effectively duplicate all 
previous operations, and the damage applied to pigs doubles. Instead of reapplying
each operation, we precompute the effect using doubling and inverse operations.
"""

import os
import sys
from collections import Counter
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


q = II()
tot_damage = 0
mod = 998244353
multi = 1
inv = (mod + 1) // 2
ts = 1
cnt = Counter()
for _ in range(q):
    tmp = LII()
    if tmp[0] == 1:
        # Create a pig with health tmp[1] + total damage applied so far
        cnt[tmp[1] + tot_damage] += ts
    elif tmp[0] == 2:
        # Apply damage to all living pigs
        tot_damage += tmp[1]
    elif tot_damage <= 2 * 10**5:
        # Handle repeat operation
        if tot_damage == 0:
            # When no damage exists, double the multiplier and halve the tracking state
            multi = multi * 2 % mod
            ts = ts * inv % mod
        else:
            # For damage > 0, propagate damage by duplicating health values
            for i in range(tot_damage + 2 * 10**5, tot_damage, -1):
                if i in cnt:
                    cnt[i + tot_damage] += cnt[i]
            tot_damage *= 2
ans = 0
# Count all alive pigs (health > total damage)
for key in cnt:
    if key > tot_damage:
        ans += cnt[key]
print(ans * multi % mod)


# https://github.com/VaHiX/CodeForces/