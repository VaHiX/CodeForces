# Problem: CF 1730 E - Maximums and Minimums
# https://codeforces.com/contest/1730/problem/E

"""
Algorithm: Maximums and Minimums
Purpose: Count the number of subarrays where the maximum element is divisible by the minimum element.
Techniques: 
- Monotonic stack for finding nearest smaller/larger elements
- Prime factorization for efficient divisibility checks
- Coordinate compression and preprocessing

Time Complexity: O(n * sqrt(max_value) + n * log n) where n is the array size
Space Complexity: O(n + max_value) for storing arrays and prime table

The solution uses:
1. Monotonic stacks to compute boundaries for elements
2. Prime factorization to check divisibility efficiently
3. Preprocessing to avoid recomputation
"""

standard_input, packages, output_together = 1, 1, 1
dfs, hashing, read_from_file = 1, 0, 0
de = 1

if 1:

    if standard_input:
        import os
        import sys

        input = lambda: sys.stdin.readline().strip()

        inf = float("inf")

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
                yield p, 0
                x //= p
                yield p, 1
                while x % p == 0:
                    x //= p
                    yield p, 1
        else:
            while x > 1:
                p = self.max_div[x]
                cnt = 0
                while x % p == 0:
                    x //= p
                    cnt += 1
                yield p, cnt

    def get_factors(self, x: int):
        factors = [1]
        for p, b in self.prime_factorization(x):
            n = len(factors)
            for j in range(1, b + 1):
                for idx in range(len(factors) - n, len(factors)):
                    factors.append(factors[idx] * p)
        return factors


pt = PrimeTable(10**6)


def main():
    n = II()
    nums = LII()

    left_larger = [-1] * n
    right_larger = [n] * n
    stack = []
    for i in range(n):
        while stack and nums[stack[-1]] < nums[i]:
            right_larger[stack.pop()] = i
        if stack:
            left_larger[i] = stack[-1]
        stack.append(i)

    left_smaller = [-1] * n
    stack = []
    for i in range(n):
        while stack and nums[stack[-1]] >= nums[i]:
            stack.pop()
        if stack:
            left_smaller[i] = stack[-1]
        stack.append(i)

    right_smaller = [n] * n
    stack = []
    for i in range(n - 1, -1, -1):
        while stack and nums[stack[-1]] >= nums[i]:
            stack.pop()
        if stack:
            right_smaller[i] = stack[-1]
        stack.append(i)

    pos = [-1] * (10**6 + 1)
    last_vis = [-1] * n
    for i in range(n):
        last_vis[i] = pos[nums[i]]
        pos[nums[i]] = i

    rpos = [n] * (10**6 + 1)
    ans = 0
    for i in range(n - 1, -1, -1):
        rpos[nums[i]] = i

        for v in pt.get_factors(nums[i]):
            if pos[v] == rpos[v] == -1:
                continue
            f1 = f2 = 0
            if pos[v] > -1 and pos[v] > left_larger[i] and right_smaller[pos[v]] > i:
                f1 = 1
                ans += (pos[v] - max(left_smaller[pos[v]], left_larger[i])) * (
                    min(right_smaller[pos[v]], right_larger[i]) - i
                )

            if rpos[v] < n and rpos[v] < right_larger[i] and left_smaller[rpos[v]] < i:
                f2 = 1
                ans += (i - max(left_smaller[rpos[v]], left_larger[i])) * (
                    min(right_smaller[rpos[v]], right_larger[i]) - rpos[v]
                )

            if f1 and f2:
                ans -= (pos[v] - max(left_smaller[pos[v]], left_larger[i])) * (
                    min(right_smaller[rpos[v]], right_larger[i]) - rpos[v]
                )

        pos[nums[i]] = last_vis[i]

    print(ans)
    return


t = II()
for _ in range(t):
    main()


# https://github.com/VaHiX/CodeForces/