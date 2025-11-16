# Problem: CF 1978 F - Large Graph
# https://codeforces.com/contest/1978/problem/F

"""
Purpose: This code solves the problem of counting connected components in a graph constructed from a cyclically shifted matrix.
The graph has n^2 vertices, each corresponding to an element in the matrix. Two vertices are connected if:
1. Their Manhattan distance is at most k.
2. Their values have a GCD greater than 1.

Algorithms/Techniques:
- Union-Find (Disjoint Set Union) for efficiently merging connected components.
- Prime factorization to determine GCD conditions.
- Optimization to avoid checking all pairs by grouping based on prime factors.

Time Complexity: O(n * sqrt(max(a)) + t * n * log(n)) where t is number of test cases.
Space Complexity: O(n + max(a)) for storing primes, Union-Find structure, and auxiliary arrays.
"""

standard_input, packages, output_together = 1, 1, 0
dfs, hashing, read_from_file = 0, 0, 0
de = 1

if 1:

    if standard_input:
        import os
        import sys

        input = lambda: sys.stdin.readline().strip()

        import math

        inf = math.inf

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

        def LFI():
            return list(map(float, input().split()))

        def GMI():
            return map(lambda x: int(x) - 1, input().split())

        def LGMI():
            return list(map(lambda x: int(x) - 1, input().split()))

    if packages:
        import os
        import random
        from io import BytesIO, IOBase


        BUFSIZE = 4096

    if output_together:

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

        sys.stdout = IOWrapper(sys.stdout)

    if dfs:
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

    if hashing:
        RANDOM = random.getrandbits(20)

        class Wrapper(int):
            def __init__(self, x):
                int.__init__(x)

            def __hash__(self):
                return super(Wrapper, self).__hash__() ^ RANDOM

    if read_from_file:
        file = open("input.txt", "r").readline().strip()[1:-1]
        fin = open(file, "r")
        input = lambda: fin.readline().strip()
        output_file = open("output.txt", "w")

        def fprint(*args, **kwargs):
            print(*args, **kwargs, file=output_file)

    if de:

        def debug(*args, **kwargs):
            print("\033[92m", end="")
            print(*args, **kwargs)
            print("\033[0m", end="")


class PrimeTable:

    def __init__(self, n: int) -> None:
        self.n = n
        self.primes = []
        self.max_div = list(range(n + 1))
        self.max_div[1] = 1
        self.phi = list(range(n + 1))

        for i in range(2, n + 1):
            if self.max_div[i] == i:
                self.primes.append(i)
                for j in range(i, n + 1, i):
                    self.max_div[j] = i
                    self.phi[j] = self.phi[j] // i * (i - 1)

    def is_prime(self, x: int):
        if x < 2:
            return False
        if x <= self.n:
            return self.max_div[x] == x
        for p in self.primes:
            if p * p > x:
                break
            if x % p == 0:
                return False
        return True

    def prime_factorization(self, x: int):
        if x > self.n:
            for p in self.primes:
                if p * p > x:
                    break
                if x <= self.n:
                    break
                if x % p == 0:
                    cnt = 0
                    while x % p == 0:
                        cnt += 1
                        x //= p
                    yield p, cnt
        while 1 < x and x <= self.n:
            p, cnt = self.max_div[x], 0
            while x % p == 0:
                cnt += 1
                x //= p
            yield p, cnt
        if x >= self.n and x > 1:
            yield x, 1

    def get_factors(self, x: int):
        factors = [1]
        for p, b in self.prime_factorization(x):
            n = len(factors)
            for j in range(1, b + 1):
                for d in factors[:n]:
                    factors.append(d * (p**j))
        return factors


class UnionFind:
    def __init__(self, n, size=None):
        self.parent_or_size = [-1] * n if size is None else [-x for x in size]

    def find(self, a):
        a = self.parent_or_size[a] if self.parent_or_size[a] >= 0 else a
        acopy = a
        while self.parent_or_size[a] >= 0:
            a = self.parent_or_size[a]
        while acopy != a:
            self.parent_or_size[acopy], acopy = a, self.parent_or_size[acopy]
        return a

    def merge(self, a, b):
        pa, pb = self.find(a), self.find(b)
        if pa == pb:
            return False
        if self.parent_or_size[pa] > self.parent_or_size[pb]:
            pa, pb = pb, pa
        self.parent_or_size[pa] += self.parent_or_size[pb]
        self.parent_or_size[pb] = pa
        return True

    def getSize(self, a):
        return -self.parent_or_size[self.find(a)]


pt = PrimeTable(10**6)

t = II()
outs = []

prev = [-1] * (10**6 + 1)
used = [-1] * (10**6 + 1)

for tmstamp in range(t):
    n, dist = MII()
    nums = LII()

    primes = []

    ans = n * 2 - 1
    union = UnionFind(n * 2)

    for i in range(1, 2 * n):
        for p, _ in pt.prime_factorization(nums[i % n]):
            if used[p] < tmstamp:
                used[p] = tmstamp
                primes.append(p)
            elif i - prev[p] <= dist:
                # Check if merging reduces components
                ans -= union.merge(prev[p], i)
            prev[p] = i

    if nums[0] == 1:
        ans += 1
    for i in range(n):
        if nums[i] == 1:
            ans += n - 2
    outs.append(ans)

print("\n".join(map(str, outs)))


# https://github.com/VaHiX/CodeForces/