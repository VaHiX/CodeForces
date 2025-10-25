# Problem: CF 1902 E - Collapsing Strings
# https://codeforces.com/contest/1902/problem/E

"""
Problem: E. Collapsing Strings
Algorithm: Trie-based optimization with prefix/suffix matching
Time Complexity: O(sum of string lengths)
Space Complexity: O(sum of string lengths)

This solution uses a trie data structure to efficiently compute the sum of 
collapse operations across all pairs of strings. The key insight is that for 
each pair (s_i, s_j), the collapse operation C(s_i, s_j) reduces the total length 
when the last character of s_i matches the first character of s_j. 

We build a trie of all strings and then for each string, we reverse it and 
traverse the trie to count overlaps. The total sum is initially calculated as 
2 * n * L (where L is total length), and then we subtract the redundant counts 
from overlapping prefixes/suffixes.
"""

import os
import sys

ONLINE_JUDGE = not bool(os.environ.get("AURELIONY"))
if not ONLINE_JUDGE:
    import timeit

    import psutil

    process = psutil.Process(os.getpid())
    start = timeit.default_timer()
import operator
import threading
from array import array
from bisect import *
from collections import *
from copy import *
from functools import *
from heapq import *
from io import BytesIO, IOBase
from itertools import *
from math import *
from random import *
from string import *
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


choose = lambda n, r: reduce(operator.mul, range(n - r + 1, n + 1), 1) // factorial(r)


class DSU:
    def __init__(self, sz):
        self.parent = list(range(sz))
        self.sz = [1] * sz

    def find(self, x):
        if self.parent[x] == x:
            return x
        self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def link(self, a, b):
        a = self.find(a)
        b = self.find(b)
        if a != b:
            self.parent[a] = b
            self.sz[b] += self.sz[a]

    def union(self, a, b):
        a = self.find(a)
        b = self.find(b)
        if a != b:
            if self.sz[a] < self.sz[b]:
                self.parent[a] = b
                self.sz[b] += self.sz[a]
            else:
                self.parent[b] = a
                self.sz[a] += self.sz[b]

    def is_connected(self, a, b):
        return self.find(a) == self.find(b)

    def size(self, a):
        return self.sz[self.find(a)]


def sieve(maxprime):
    if maxprime == 1:
        return [0, 0]
    prime = array("b", [True]) * (maxprime + 1)
    prime[0] = False
    prime[1] = False
    p = 2
    prime[p] = True
    while p * p <= maxprime:
        if prime[p]:
            for e in range(p + p, maxprime + 1, p):
                prime[e] = False
        p += 1
    return prime


def segmented_sieve(l, r):
    n = int(sqrt(int(r + 1))) + 1
    prime = sieve(n)
    isPrime = array("b", [True]) * (r - l + 1)
    if l == 0:
        isPrime[0] = False
        isPrime[1] = False
    if l == 1:
        isPrime[0] = False
    for i in range(len(prime)):
        if not prime[i]:
            continue
        for j in range(max(i * i, (l + i - 1) // i * i), r + 1, i):
            isPrime[j - l] = False
    return isPrime


TIME_LIMIT = 1
MEMORY_LIMIT = 256
FAST_INPUT = FAST_OUTPUT = 1
MOD = 1000000007


def solve():
    n = gi()
    T = {0: 0}  # Trie root
    arr = [""] * n  # Array to store strings
    L = 0  # Total length of all strings
    for i in range(n):
        arr[i] = gs()
        L += len(arr[i])
        curr = T
        curr[0] += 1
        for c in arr[i]:
            if c not in curr:
                curr[c] = {0: 0}  # Initialize new node
            curr = curr[c]
            curr[0] += 1  # Increment count for this prefix
    ans = 2 * n * L  # Base answer: Each pair contributes sum of their lengths (assuming no collapse)
    for s in arr:
        s = s[::-1]  # Reverse the string
        curr = T
        for c in s:
            if c not in curr:
                break  # No further match in trie
            curr = curr[c]
            ans -= 2 * curr[0]  # Subtract overlapping lengths from answer
    print(ans)


def main(t=1):
    for i in range(t):
        solve()


def debug(state=0):
    if ONLINE_JUDGE:
        return
    end = timeit.default_timer()
    memory_usage = process.memory_info().rss / 1048576
    if end - start > TIME_LIMIT or memory_usage > MEMORY_LIMIT:
        if FAST_OUTPUT:
            sys.stdout.buffer.buffer.truncate(0)
            sys.stdout.buffer.buffer.seek(0)
        if end - start > TIME_LIMIT:
            print("TLE")
        if memory_usage > MEMORY_LIMIT:
            print("MLE")
        print(f"TIME: {round(end-start,2)}s")
        print(f"MEMORY: {round(memory_usage)}MB")
        sys.stdout.flush()
        exit(0)
    if state == 1:
        sys.stdout.flush()
        print(f"TIME: {round(end-start,2)}s")
        print(f"MEMORY: {round(memory_usage)}MB")


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._file = file
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.buffer_size = 8192
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, self.buffer_size))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()

    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, self.buffer_size))
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


if FAST_INPUT:
    sys.stdin = IOWrapper(sys.stdin)
if FAST_OUTPUT:
    sys.stdout = IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")
INF = 0x3F3F3F3F
INF64 = 0x3F3F3F3F3F3F3F3F
EPS = sys.float_info.epsilon


def gs():
    return input()


def gi():
    return int(input())


def gis():
    return list(map(int, input().split()))


def gf():
    return float(input())


def gfs():
    return list(map(float, input().split()))


def impossible():
    print(-1), exit(0)


def printarr(arr):
    print(*arr)


if __name__ == "__main__":
    threading.Thread(target=main).start()


# https://github.com/VaHiX/CodeForces/